#include "FuncList.h"
#include "llvm/Demangle/Demangle.h"
#include "llvm/Support/raw_ostream.h"
#include <unordered_set>
#include <fstream>
#include <vector>

llvm::cl::opt<std::string> FuncListFile(
    "func-list",
    llvm::cl::desc("File containing list of functions to obfuscate"),
    llvm::cl::value_desc("filename"),
    llvm::cl::init(""));

static std::vector<std::string> FuncList;
static bool FuncListLoaded = false;

static void LoadFuncList() {
    if (FuncListLoaded)
        return;

    FuncListLoaded = true;

    if (FuncListFile.empty())
        return;

    std::ifstream f(FuncListFile);
    if (!f.is_open())
        return;

    std::string line;
    while (std::getline(f, line)) {
        if (!line.empty())
            FuncList.push_back(line);
    }
}

bool ShouldObfuscateFunction(const llvm::Function& F) {

    LoadFuncList();

    // If no list or empty list -> obfuscate everything
    if (FuncListFile.empty() || FuncList.empty())
        return true;

    std::string FuncName = F.getName().str();    
	
    // Debug output (optional)
    llvm::errs() << "[func-list] checking: " << FuncName << "\n";    

    for (auto &Entry : FuncList)
    {

        if (FuncName.find(Entry) != std::string::npos)
        {
        llvm::errs() << "  -> MATCHED entry: " << Entry << "\n";
        return true;
        }
        
    }

    llvm::errs() << "  -> NOT matched\n";		
    return false;
}
