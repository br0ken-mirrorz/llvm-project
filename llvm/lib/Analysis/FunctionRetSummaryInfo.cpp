#include "llvm/Analysis/FunctionRetSummaryInfo.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

ValueLatticeElement FunctionRetSummary::evaluateOn(SmallVector<ConstantRange>* predicateBundle) {
    bool hasRefinedRange=false;
    for (auto& CR : *predicateBundle) 
        if (!CR.isFullSet()) {
            hasRefinedRange = true;
            break;
        }
    if (!hasRefinedRange) return ValueLatticeElement::getOverdefined(); // or range metadata?

    // TODO: evaluate
}

void FunctionRetSummary::buildSummary(Function* F, FunctionAnalysisManager& FAM) {
    LazyValueInfo *LVI = &FAM.getResult<LazyValueAnalysis>(*F);
    auto dfs = [&](auto&& self, BasicBlock* BB, Node* current) -> void {
        auto Inst = BB->getTerminator(); 
        if (ReturnInst *Ret = dyn_cast<ReturnInst>(Inst)) {
            Value *v = Ret->getReturnValue();
            current->subtreeRange = LVI->getConstantRange(v, Inst, true); // not sure if this should be at use or not          
        } else if (BranchInst *Branch = dyn_cast<BranchInst>(Inst)) {
            if (!Branch->isConditional()) self(self,Branch->getSuccessor(0), current);

            // TODO: get condition and add to node

        } else if (auto Call = dyn_cast<CallInst>(Inst)) {
            // TODO: idk skip it?
        }
    };
}

FunctionRetSummary* FunctionRetSummaryInfo::getSummary(Function *F) {
    if (Cache.contains(F)) return Cache[F];
    return Cache[F] = new FunctionRetSummary(F, FAM);
}

SmallVector<ConstantRange>* FunctionRetSummaryInfo::buildPredicateBundle(CallBase *CB, LazyValueInfo *LVI) {
    auto predicateBundle = new SmallVector<ConstantRange>();
    for (auto& arg : CB->args()) 
        if (arg->getType()->isIntegerTy()) 
            predicateBundle->push_back(LVI->getConstantRangeAtUse(arg, true));
    
    return predicateBundle;
}

ValueLatticeElement FunctionRetSummaryInfo::summarizeCall(CallBase *CB, LazyValueInfo *LVI) {
    if (auto *F = CB->getCalledFunction()) {
        FunctionRetSummary* FS = getSummary(F);

        if (FS->isFullRange()) return ValueLatticeElement::getOverdefined(); // or range metadata?

        return FS->evaluateOn(buildPredicateBundle(CB, LVI));
    }
}

FunctionRetSummaryInfo FunctionRetSummaryAnalysis::run(Module &M, ModuleAnalysisManager &MAM) {
    return FunctionRetSummaryInfo(M, MAM);
}