//==============================================================================
// FILE:
//    LVIExtCleanup.h
//==============================================================================
// #ifndef LLVM_T_H
// #define LLVM_TUTOR_MBA_ADD_H
#ifndef LLVM_LVIExtCleanup_H
#define LLVM_LVIExtCleanup_H
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"

#include "llvm/Analysis/LazyValueInfo.h"

//------------------------------------------------------------------------------
// New PM interface
//------------------------------------------------------------------------------
struct LVIExtCleanup : public llvm::PassInfoMixin<LVIExtCleanup> {
  llvm::PreservedAnalyses run(llvm::Module &M,
                              llvm::ModuleAnalysisManager &);
  bool runOnModule(llvm::Module &M, llvm::ModuleAnalysisManager &mam) ;
  // Without isRequired returning true, this pass will be skipped for functions
  // decorated with the optnone LLVM attribute. Note that clang -O0 decorates
  // all functions with optnone.
  static bool isRequired() { return true; }
};

#endif
