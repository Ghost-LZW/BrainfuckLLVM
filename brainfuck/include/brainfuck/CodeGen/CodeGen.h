/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : CodeGen.h
#   Last Modified : 2022-04-28 15:06
#   Describe      :
#
# ====================================================*/

#ifndef BRAINFUCK_CODEGEN_CODEGEN_H_
#define BRAINFUCK_CODEGEN_CODEGEN_H_

#include <string> // for string
namespace llvm {
class Module;
}

namespace brainfuck {

class ObjectGenerator {
public:
  ObjectGenerator(llvm::Module *mod, std::string filename,
                  std::string objectname)
      : mod_(mod), filename_(filename), objectname_(objectname) {}

  int CodeGen();

private:
  llvm::Module *mod_;
  std::string filename_;
  std::string objectname_;

  const std::string LD_CMD = "cc -g -o ";
};

} // namespace brainfuck

#endif // BRAINFUCK_CODEGEN_CODEGEN_H_
