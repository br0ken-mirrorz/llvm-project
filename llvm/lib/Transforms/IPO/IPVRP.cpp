// #include "llvm/Transforms/IPO/IPVRP.h"

// #include "llvm/Analysis/AssumptionCache.h"
// #include "llvm/Analysis/LazyValueInfo.h"
// #include "llvm/Analysis/FunctionSummaryInfo.h"
// #include "llvm/Analysis/ValueLattice.h"
// #include "llvm/IR/Dominators.h"
// #include "llvm/IR/User.h"
// #include "llvm/IR/Value.h"
// #include "llvm/Transforms/Utils/PredicateInfo.h"

// using namespace llvm;

// PreservedAnalyses IPVRPPass::run(Function &F, FunctionAnalysisManager &AM) {
//     LazyValueInfo *LVI = &AM.getResult<LazyValueAnalysis>(F);
//     DominatorTree *DT = &AM.getResult<DominatorTreeAnalysis>(F);
//     AssumptionCache *AC = &AM.getResult<AssumptionAnalysis>(F);
//     std::unique_ptr<PredicateInfo> PI = std::make_unique<PredicateInfo>(F, *DT, *AC, BumpPtrAllocatorImpl<>());

//     bool changed = RunImpl(F,AM,LVI,AC,DT,std::move(PI));

//     if (!changed) return PreservedAnalyses::all();
//     // handle invaldating preserved analyses here
// }

// bool RunImpl(Function &F, FunctionAnalysisManager &AM, LazyValueInfo *LVI, 
//     AssumptionCache *AC, DominatorTree *DT, std::unique_ptr<PredicateInfo> PI) {
//     bool changed=false;

//     for (auto& BB : F)
//         for (auto& I : BB)
//             if (auto *CB = dyn_cast<CallBase*>(I)) {
//                 if (auto Callee = CB->getCalledFunction()) {
//                     Function& CalleeRef = (Function&) Callee;
//                     DenseMap<StringRef,ConstantRange> predicateBundle;
//                     for (auto& arg : CB->args()) {
//                         if (arg->getType()->isIntegerTy()) {
//                             auto PB = PI->getPredicateInfoFor(arg);
//                             PB->getConstraint();
//                             // uhhh
//                         }

//                     }
//                     // get predicate bundle
//                     // check pred bundle not empty
//                     const auto &MAMProxy =
//                         AM.getResult<ModuleAnalysisManagerFunctionProxy>(F);
//                     FunctionSummaryInfo *FS = MAMProxy.getCachedResult<FunctionSummaryAnalysis>(*CB->getParent()->getParent()->getParent());
//                     ValueLatticeElement RetRange = FS->getSummaryFor(Callee, predicateBundle);
//                     if (!RetRange.getConstantRange().isFullSet()) {
//                         CB->addRangeRetAttr(RetRange.getConstantRange());
//                         changed=true;
//                     }
//                 }
//             }
//     return changed;
// }
