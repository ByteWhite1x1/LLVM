
/*

At the top of each pass file (.cpp): 

#include "FuncList.h"

Example for Flattening.cpp:

PreservedAnalyses FlatteningPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {

	// Add this line:
    if (!shouldObfuscateFunction(F))
    return PreservedAnalyses::all();

-mllvm -func-list=functionsToBeVirtualized.txt

*/

#pragma once

#include "llvm/Support/CommandLine.h"
#include "llvm/IR/Function.h"
#include <string>

extern llvm::cl::opt<std::string> FuncListFile;

bool ShouldObfuscateFunction(const llvm::Function& F);
