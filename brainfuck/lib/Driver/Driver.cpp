/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : Driver.cpp
#   Last Modified : 2022-04-10 23:19
#   Describe      :
#
# ====================================================*/

#include "brainfuck/Driver/Driver.h"

#include <iostream>

#include "brainfuck/Parser/ExprParser.hpp"

using namespace brainfuck::driver;

struct StdinStream {
  template <typename T> StdinStream operator>>(T &x) {
    std::cin >> x;
    return *this;
  }
  operator bool() const { return std::cin.operator bool(); }
};

void Driver::Run() {
  ExprParser<StdinStream> parse;
  parse.Parse();
  std::cout << std::boolalpha << std::cin.operator bool() << std::endl;
}
