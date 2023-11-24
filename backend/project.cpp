#include "project.h"
#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/LangOptions.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <clang/Parse/ParseAST.h>
#include <clang/Sema/Sema.h>
#include <llvm/TargetParser/Host.h>
#include <list>
#include <vector>
#include <memory>

using namespace cdocs::backend;
using namespace llvm;
using namespace clang;

class FindNamedClassVisitor : public RecursiveASTVisitor<FindNamedClassVisitor>
{
public:
    explicit FindNamedClassVisitor(ASTContext* Context)
        : Context(Context)
    {
    }

    bool VisitDecl(Decl* d)
    {
        d->dump();
        return true;
    }

private:
    ASTContext* Context;
};

class FindNamedClassConsumer : public clang::ASTConsumer
{
public:
    explicit FindNamedClassConsumer(ASTContext* Context)
        : Visitor(Context)
    {
    }

    void HandleTranslationUnit(clang::ASTContext& Context) override
    {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }

private:
    FindNamedClassVisitor Visitor;
};

class FindNamedClassAction : public clang::ASTFrontendAction
{
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(CompilerInstance& Compiler, StringRef InFile) override
    {
        return std::make_unique<FindNamedClassConsumer>(&Compiler.getASTContext());
    }
};

Project::Project(const std::string& strDirectory)
{
    /*ArrayRef paths(strDirectory);
    std::vector<std::unique_ptr<ASTUnit>> asts;
    tool.buildASTs(asts);
    for (auto& unit : asts)
    {
        if (unit)
        {
            unit->getASTFileName();
        }
    }*/
    std::unique_ptr<CompilerInstance> Clang = std::make_unique<CompilerInstance>();
    Clang->createDiagnostics(nullptr, false);
    {
        std::shared_ptr<clang::TargetOptions> TO = Clang->getInvocation().TargetOpts;
        TO->Triple = llvm::sys::getDefaultTargetTriple();
        TargetInfo* target = TargetInfo::CreateTargetInfo(Clang->getDiagnostics(), TO);
        Clang->setTarget(target);
    }
    auto& TO = Clang->getTargetOpts();
    llvm::Triple T(TO.Triple);
    PreprocessorOptions& PO = Clang->getPreprocessorOpts();
    LangOptions::setLangDefaults(Clang->getLangOpts(), Language::CXX, T, PO.Includes);
    Clang->createFileManager();
    Clang->createSourceManager(Clang->getFileManager());
    HeaderSearchOptions& HSO = Clang->getHeaderSearchOpts();
    HSO.ResourceDir = strDirectory;
    Clang->createPreprocessor(TU_Complete);
    Preprocessor& PP = Clang->getPreprocessor();
    LangOptions& LO = Clang->getLangOpts();
    PP.getBuiltinInfo().initializeBuiltins(PP.getIdentifierTable(), LO);
    const FileEntry* file = Clang->getFileManager().getFile("E:/Github/cdocs/testing/function.h").get();
    auto& SM = Clang->getSourceManager();
    SM.setMainFileID(SM.createFileID(file, SourceLocation(), SrcMgr::C_User));
    Clang->createASTContext();
    FindNamedClassConsumer consumer(Clang->getASTContextPtr().get());
    std::unique_ptr<Sema> sema = std::make_unique<Sema>(PP, Clang->getASTContext(), consumer);
    Clang->getDiagnosticClient().BeginSourceFile(LO, &PP);
    ParseAST(*sema, false, true);
    Clang->getDiagnosticClient().EndSourceFile();
}

cdocs::backend::Project::Project(int argc, const char* argv[]) {}

Project::~Project() {}

int32_t Project::Build(BuildProgress&& bp)
{
    return 0;
}
