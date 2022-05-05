/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : CodeGen.cpp
#   Last Modified : 2022-04-28 17:05
#   Describe      :
#
# ====================================================*/

#include "brainfuck/CodeGen/CodeGen.h"

#include <cstdlib>
#include <system_error> // for error_code

#include "llvm/ADT/Optional.h"         // for Optional
#include "llvm/ADT/StringRef.h"        // for StringRef
#include "llvm/IR/LegacyPassManager.h" // for PassManager
#include "llvm/IR/Module.h"            // for Module
#include "llvm/IR/Verifier.h"          // for Module
#include "llvm/MC/TargetRegistry.h"    // for Target, TargetRegistry
#include "llvm/Support/CodeGen.h"      // for Model, CGFT_ObjectFile
#include "llvm/Support/FileSystem.h"   // for OF_None
#include "llvm/Support/Host.h"         // for getDefaultTargetTriple
#include "llvm/Support/TargetSelect.h" // for InitializeAllAsmParsers
#include "llvm/Support/raw_ostream.h"  // for errs, raw_fd_ostream, raw_o...
#include "llvm/Target/TargetMachine.h" // for TargetMachine
#include "llvm/Target/TargetOptions.h" // for TargetOptions

namespace brainfuck {

int ObjectGenerator::CodeGen() {
  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmParsers();
  llvm::InitializeAllAsmPrinters();

  // llvm::verifyModule(*mod_);

  std::string Error;
  auto TargetTriple = llvm::sys::getDefaultTargetTriple();
  auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

  if (!Target) {
    llvm::errs() << Error;
    return -1;
  }

  auto CPU = "generic";
  auto Features = "";

  llvm::TargetOptions opt;
  auto RM = llvm::Optional<llvm::Reloc::Model>();
  auto TargetMachine =
      Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

  mod_->setDataLayout(TargetMachine->createDataLayout());
  mod_->setTargetTriple(TargetTriple);

  std::error_code EC;
  llvm::raw_fd_ostream dest(filename_, EC, llvm::sys::fs::OF_None);

  if (EC) {
    llvm::errs() << "Could not open file: " << EC.message();
    return 1;
  }

  llvm::legacy::PassManager pass;
  auto FileType = llvm::CGFT_ObjectFile;

  if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
    llvm::errs() << "TargetMachine can't emit a file of this type";
    return 1;
  }

  if (filename_ != "a.o") {
    std::error_code allec;
    llvm::raw_fd_ostream ll("a.ll", allec, llvm::sys::fs::OF_None);
    mod_->print(ll, nullptr);
  }

  pass.run(*mod_);
  dest.flush();

  system((LD_CMD + objectname_ + ' ' + filename_).c_str());

  return 0;
}

} // namespace brainfuck
