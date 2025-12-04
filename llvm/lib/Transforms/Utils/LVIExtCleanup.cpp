#include "llvm/Transforms/Utils/LVIExtCleanup.h"
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

#define DEBUG_TYPE "lviextcleanup"

STATISTIC(CloneCnt, "The # of clone functions");

//-----------------------------------------------------------------------------
// LVIExtCleanup Implementation
//-----------------------------------------------------------------------------
bool runOnBasicBlock(llvm::Module &M, BasicBlock &BB, FunctionAnalysisManager &fam) {
  bool Changed = false;
  
  // Loop over all instructions in the block. Replacing instructions requires
  // iterators, hence a for-range loop wouldn't be suitable
  for (auto Inst = BB.begin(), IE = BB.end(); Inst != IE; ++Inst) {
    auto *callOp = dyn_cast<CallInst>(Inst);
    if (!callOp)
      continue;
    if (callOp->getCalledFunction() == nullptr) continue;
    if (callOp->getCalledFunction()->getName().str().rfind("xivccf.", 0) == 0) {
        callOp->setCalledFunction(M.getOrInsertFunction(
            callOp->getCalledFunction()->getName().str().substr(7, callOp->getCalledFunction()->getName().str().rfind(".xivccf") - 7), callOp->getCalledFunction()->getFunctionType()));
        Changed = true;
    }
  }
  return Changed;
}
bool runOnFunction(llvm::Module &M, llvm::Function &F, FunctionAnalysisManager &fam) {
  bool ret = false;
  for (auto &BB : F) ret |= runOnBasicBlock(M, BB, fam);
  return ret;
}
bool LVIExtCleanup::runOnModule(Module &M, llvm::ModuleAnalysisManager &mam) {
  bool ret = false;
  FunctionAnalysisManager &fam =
        mam.getResult<FunctionAnalysisManagerModuleProxy>(M).getManager();

  std::vector<llvm::Function*> funcs{};
  for (auto &F : M) {
    funcs.push_back(&F);
  }
  
  for (unsigned int i = 0; i < funcs.size(); ++i) {
    ret |= runOnFunction(M, *funcs[i], fam);
  }

  for (unsigned int i = 0; i < funcs.size(); ++i) {
    if (funcs[i]->getName().str().rfind("xivccf.", 0) == 0) {
        // delete this function!
        // funcs[i]->deleteBody();
        funcs[i]->eraseFromParent();
        ret = true;
        // funcs[i]->replaceAllUsesWith(&M.getOrInsertFunction(funcs[i]->getName().str().substr(7), funcs[i]->getType()));
    }
  }
  return ret;
}

PreservedAnalyses LVIExtCleanup::run(llvm::Module &M,
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
llvm::PassPluginLibraryInfo getLVIExtCleanupPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "lviextcleanup", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "lviextcleanup") {
                    MPM.addPass(LVIExtCleanup());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLVIExtCleanupPluginInfo();
}
