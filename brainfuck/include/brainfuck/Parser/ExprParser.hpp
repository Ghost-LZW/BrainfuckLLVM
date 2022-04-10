/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : ExprParser.hpp
#   Last Modified : 2022-04-10 22:59
#   Describe      :
#
# ====================================================*/

#ifndef BRAINFUCK_PARSER_EXPRPARSER_H_
#define BRAINFUCK_PARSER_EXPRPARSER_H_

#include "brainfuck/AST/ExprAST.h"
#include "brainfuck/Token/TokenStream.hpp"

#include <memory>

namespace brainfuck {

template <typename InputStream> class ExprParser {
public:
  void Parse() {
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

private:
  std::unique_ptr<ExprAST> HandleUnaryExpr(Token token) {
    std::fprintf(stderr, "handle token\n");
    return nullptr;
  }
  std::unique_ptr<ExprAST> HandleJumpExpr(Token token) {
    std::fprintf(stderr, "parse a jump expr\n");
    return nullptr;
  }

private:
  TokenStream<InputStream> token_stream_;
};

} // namespace brainfuck

#endif // BRAINFUCK_PARSER_EXPRPARSER_H_
