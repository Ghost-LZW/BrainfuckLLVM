/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : ExprParser.hpp
#   Last Modified : 2022-04-27 21:09
#   Describe      :
#
# ====================================================*/

#ifndef BRAINFUCK_PARSER_EXPRPARSER_H_
#define BRAINFUCK_PARSER_EXPRPARSER_H_

#include "brainfuck/AST/ExprAST.h"
#include "brainfuck/Token/TokenStream.hpp"

#include <memory>
#include <stack>

namespace brainfuck {

template <typename InputStream> class ExprParser {
public:
  void Parse() {
    BaseAST::Initialize();
    BaseAST::Print();
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
    BaseAST::Print();
  }

private:
  std::unique_ptr<ExprAST> ParseUnaryExpr(Token token) {
    switch (token) {
    case Token::TK_ADD:
    case Token::TK_MINUS:
      return std::make_unique<UnaryExprAST>(token);
    case Token::TK_LEFT:
      return std::make_unique<MoveExprAST>(-1);
    case Token::TK_RIGHT:
      return std::make_unique<MoveExprAST>(1);
    case Token::TK_INPUT:
      return std::make_unique<InputExprAST>();
    case Token::TK_OUTPUT:
      return std::make_unique<OutputExprAST>();
    default:
      assert(false && "no such unary op");
    }

    return nullptr;
  }

  void HandleUnaryExpr(Token token) {
    auto expr = ParseUnaryExpr(token);
    if (expr)
      expr->CodeGen()->print(llvm::errs()), fprintf(stderr, "\n");
    else {
      std::fprintf(stderr, "[WARN] can't parse expr");
    }

    return;
  }

  void HandleJumpExpr(Token token) {
    static std::stack<WhileAST> wst;
    if (token == Token::TK_JIFORWARD) {
      wst.emplace();
      wst.top().CodeGen()->print(llvm::errs());
      fprintf(stderr, "\n");
      return;
    }
    assert(!wst.empty() && "unmatch ] !");
    wst.top().CodeGen();
    fprintf(stderr, "\n");
    wst.pop();

    return;
  }

private:
  TokenStream<InputStream> token_stream_;
};

} // namespace brainfuck

#endif // BRAINFUCK_PARSER_EXPRPARSER_H_
