#include "llvm/Transforms/Utils/LVIExt.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Analysis/LazyValueInfo.h"
#include "llvm/Pass.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Analysis/ModuleSummaryAnalysis.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/Support/Alignment.h"
#include "llvm/Transforms/Utils/ModuleUtils.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/raw_os_ostream.h"

#include <iostream>
#include <random>

using namespace llvm;

#define DEBUG_TYPE "lviext"

STATISTIC(CloneCnt, "The # of clone functions");

//-----------------------------------------------------------------------------
// LVIExt Implementation
//-----------------------------------------------------------------------------
bool runOnBasicBlock(BasicBlock &BB, llvm::LazyValueAnalysis::Result &, FunctionAnalysisManager &fam) {
  bool Changed = false;
  
  // Loop over all instructions in the block. Replacing instructions requires
  // iterators, hence a for-range loop wouldn't be suitable
  for (auto Inst = BB.begin(), IE = BB.end(); Inst != IE; ++Inst) {
    // Skip non-binary (e.g. unary or compare) instructions
    auto *callOp = dyn_cast<CallInst>(Inst);
    if (!callOp)
      continue;

    if (!callOp->getType()->isIntegerTy() || callOp->getCalledFunction()->getName().str().rfind("xivccf", 0) == 0)
      continue;
    bool canTry = false;
    for (unsigned int i = 0; i < callOp->getCalledFunction()->arg_size(); ++i) {
      if (callOp->getArgOperand(i)->getType()->isIntegerTy()) canTry = true;
    }
    if (!canTry) continue;
    Changed = true;
    
    auto func = callOp->getCalledFunction();
    llvm::ValueToValueMapTy Vmap{};
    
    auto clone = llvm::CloneFunction(func, Vmap);
    clone->setName("xivccf." + callOp->getCalledFunction()->getName().str() + ".xivccf." + clone->getName());
    // std::cout << "NAME OF FUNCTION IS " << clone->getName().str() << std::endl;
    // now insert any known values into this !!
    // actually first, lets just check that this cloning works period
    
    auto newcall = cast<CallInst>(callOp->clone());
    newcall->setCalledFunction(clone);
    
    // now go and update the function arguments (update as in add in the assumes)
    auto badblock = llvm::BasicBlock::Create(clone->getContext(), "badBlock", clone, 0);
    IRBuilder<> Builder(badblock);
    Builder.CreateUnreachable();
    auto testblock = llvm::BasicBlock::Create(clone->getContext(), "testBlock", clone, 0);
    Builder.SetInsertPoint(testblock);
    AssumptionCache ac = AssumptionCache(*BB.getParent());
    LazyValueInfo lz{&ac, &BB.getParent()->getParent()->getDataLayout()};

    std::vector<Value*> toAnd;
    for (unsigned int i = 0; i < clone->arg_size(); ++i) {
        // get the i-th argument
        if (!callOp->getArgOperand(i)->getType()->isIntegerTy()) continue;
        // LazyValueInfo &lz <LazyValueInfo>();
        llvm::ConstantRange range = lz.getConstantRange(callOp->getArgOperand(i), &*Inst, false);
        // llvm::ConstantRange range = lz

        // std::cout << (int) range.getLower().getLimitedValue() << std::endl;
        // std::cout << (int) range.getUpper().getLimitedValue() << std::endl;
        auto low = Builder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SGE, clone->getArg(i), llvm::ConstantInt::get(Builder.getInt32Ty(), range.getLower()));
        // Builder.CreateAssumption(low);
        auto high = Builder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SLE, clone->getArg(i), llvm::ConstantInt::get(Builder.getInt32Ty(), range.getUpper()));
        // Builder.CreateAssumption(high);
        auto andins = Builder.CreateAnd(low, high);
        toAnd.push_back(andins);
    }
    while (toAnd.size() > 1) {
        toAnd[0] = Builder.CreateAnd(toAnd[0], toAnd.back());
        toAnd.pop_back();
    }
    Builder.CreateCondBr(toAnd[0], &clone->getEntryBlock(), badblock);
    testblock->moveBefore(&clone->getEntryBlock());
    
    ReplaceInstWithInst(&BB, Inst, newcall);
  }
  return Changed;
}
bool runOnFunction(llvm::Function &F, llvm::LazyValueAnalysis::Result &lz, FunctionAnalysisManager &fam) {
  bool ret = false;
  for (auto &BB : F) ret |= runOnBasicBlock(BB, lz, fam);
  return ret;
}
bool LVIExt::runOnModule(Module &M, llvm::ModuleAnalysisManager &mam) {
  bool ret = false;
  FunctionAnalysisManager &fam =
        mam.getResult<FunctionAnalysisManagerModuleProxy>(M).getManager();

  std::vector<llvm::Function*> funcs{};
  for (auto &F : M) {
    funcs.push_back(&F);
  }
  
  for (unsigned int i = 0; i < funcs.size(); ++i) {
    auto &lz = fam.getResult<LazyValueAnalysis>(*funcs[i]);
    ret |= runOnFunction(*funcs[i], lz, fam);
  }
  return ret;
}

PreservedAnalyses LVIExt::run(llvm::Module &M,
                                       llvm::ModuleAnalysisManager &mam) {
  // LazyValueInfoWrapperPass lz{};
  // mam.registerPass(LazyValueInfoWrapperPass{});
//   auto &lz = mam.getResult<LazyValueAnalysis>(M);             
  bool Changed =  runOnModule(M, mam);

  return (Changed ? llvm::PreservedAnalyses::none()
                  : llvm::PreservedAnalyses::all());
}


//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getLVIExtPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "lviext", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "lviext") {
                    MPM.addPass(LVIExt());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLVIExtPluginInfo();
}
