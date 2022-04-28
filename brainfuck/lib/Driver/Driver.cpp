/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : Driver.cpp
#   Last Modified : 2022-04-28 17:07
#   Describe      :
#
# ====================================================*/

#include "brainfuck/Driver/Driver.h"

#include <fstream>
#include <iostream>

#include "brainfuck/CodeGen/CodeGen.h"
#include "brainfuck/Parser/ExprParser.hpp"

namespace llvm {
class Module;
}

using namespace brainfuck::driver;

struct StdinStream {
  template <typename T> StdinStream &operator>>(T &x) {
    std::cin >> x;
    return *this;
  }
  operator bool() const { return std::cin.operator bool(); }
};

void Driver::Run() {
  llvm::Module *mod;
  if (inputfile_.empty()) {
    ExprParser<StdinStream> parse;
    mod = parse.Parse();
  } else {
    static std::ifstream fs(inputfile_);
    struct FileStream {
      FileStream &operator>>(char &x) {
        fs >> x;
        return *this;
      }
      operator bool() const { return fs.operator bool(); }
    };

    ExprParser<FileStream> parse;
    parse.SetVerbose(false);
    mod = parse.Parse();
  }
  ObjectGenerator og(mod, filename_, objectname_);

  og.CodeGen();
}
