/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : ExprParser.cpp
#   Last Modified : 2022-04-10 20:35
#   Describe      :
#
# ====================================================*/

#include "brainfuck/Parser/ExprParser.h"

#include <cstdio>
#include <cstdlib>

namespace brainfuck {

template <typename InputStream> void ExprParser<InputStream>::Parse() {
  Token token;
  while (std::fprintf(stderr, "ready>"), token_stream_ >> token) {
    switch (token) {
    case Token::TK_EOF:
      return;
    case Token::TK_UNKNOW:
      std::fprintf(stderr, "unknow token receive"), std::abort();
    case Token::TK_JIFORWARD:
    case Token::TK_JIBACK: {
      HandleJumpExpr(token);
      break;
    }
    default:
      HandleUnaryExpr(token);
    }
  }
}

template <typename InputStream>
std::unique_ptr<ExprAST> ExprParser<InputStream>::HandleUnaryExpr(Token token) {
  std::fprintf(stderr, "handle token");
  return nullptr;
}

template <typename InputStream>
std::unique_ptr<ExprAST> ExprParser<InputStream>::HandleJumpExpr(Token token) {
  std::fprintf(stderr, "parse a jump expr");
  return nullptr;
}

} // namespace brainfuck
