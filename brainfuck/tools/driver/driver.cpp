/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : driver.cpp
#   Last Modified : 2022-04-28 17:07
#   Describe      :
#
# ====================================================*/

#include <string>

#include "brainfuck/Driver/Driver.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CommandLine.h"

using namespace brainfuck::driver;

int main(int Argc, const char **Argv) {
  llvm::cl::OptionCategory CompilerCategory(
      "Compiler Options", "Options for controlling the compilation process.");
  llvm::cl::HideUnrelatedOptions(CompilerCategory);

  llvm::cl::opt<std::string> OutputFilename(
      "o", llvm::cl::desc("Specify output filename"),
      llvm::cl::value_desc("filename"));
  llvm::cl::opt<std::string> IROutputFilename(
      "ir", llvm::cl::desc("Enable and Specify ir output filename"),
      llvm::cl::value_desc("ir filename"));
  llvm::cl::opt<std::string> InputFilename(llvm::cl::Positional,
                                           llvm::cl::desc("<input file>"));

  llvm::cl::ParseCommandLineOptions(Argc, Argv, "Brainfuck\n");

  Driver driver;

  if (!InputFilename.empty())
    driver.SetInputfile(InputFilename);
  if (!OutputFilename.empty())
    driver.SetObjectName(OutputFilename, IROutputFilename);

  driver.Run();
}
