#ifndef LLVM_ANALYSIS_FUNCTIONRetSUMMARYINFO_H
#define LLVM_ANALYSIS_FUNCTIONRetSUMMARYINFO_H

#include "llvm/Analysis/LazyValueInfo.h"
#include "llvm/Analysis/ValueLattice.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"

namespace llvm {

class FunctionRetSummary {
    bool fullRange=false;
    u_int32_t retWidth=32;

    struct Node {
      uint32_t lOp,rOp;

      enum PredType {
        LESS,
        EQUAL,
        NOTEQUAL
      };

      ConstantRange subtreeRange;
      Node *lc=nullptr,*rc=nullptr;
      Node(uint32_t width) : subtreeRange(ConstantRange(width,true)) {}
    } root = Node(retWidth);

    void buildSummary(Function* F, FunctionAnalysisManager& FAM);
    public:

    bool isFullRange() { return fullRange; }
    ValueLatticeElement evaluateOn(SmallVector<ConstantRange>* predicateBundle);
    FunctionRetSummary(Function *F, FunctionAnalysisManager& FAM) : retWidth(F->getReturnType()->getIntegerBitWidth()) { buildSummary(F, FAM); }
    ~FunctionRetSummary()=delete;
};

class FunctionRetSummaryInfo {
    const Module *M;
    FunctionAnalysisManager& FAM;
    DenseMap<Function*,FunctionRetSummary*> Cache;

    FunctionRetSummary* getSummary(Function *F);
    FunctionRetSummary* buildSummaryForFunction(Function *F);
    SmallVector<ConstantRange>* buildPredicateBundle(CallBase *CB, LazyValueInfo *LVI);

    public:
    
    ValueLatticeElement summarizeCall(CallBase *CB, LazyValueInfo *LVI);
    FunctionRetSummaryInfo(Module &M, ModuleAnalysisManager &MAM) : M(&M), FAM(MAM.getResult<FunctionAnalysisManagerModuleProxy>(M).getManager()) {};
};

class FunctionRetSummaryAnalysis : public AnalysisInfoMixin<FunctionRetSummaryAnalysis> {
public:
  typedef FunctionRetSummaryInfo Result;
  Result run(Module &M, ModuleAnalysisManager &MAM);

private:
  static AnalysisKey Key;
  friend struct AnalysisInfoMixin<FunctionRetSummaryAnalysis>;
};

}

#endif