/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : ExprParser.hpp
#   Last Modified : 2022-04-28 16:03
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
  llvm::Module *Parse() {
    BaseAST::Initialize();
    if (verbose_)
      BaseAST::Print();
    Token token;
    while (error("ready>"), token_stream_ >> token && token != Token::TK_EOF) {
      switch (token) {
      case Token::TK_UNKNOW: {
        error("unknow token receive, ignore");
        break;
      }
      case Token::TK_JIFORWARD:
      case Token::TK_JIBACK: {
        HandleJumpExpr(token);
        break;
      }
      default:
        HandleUnaryExpr(token);
      }
    }
    BaseAST::Finalize();
    return BaseAST::module();
  }

  void SetVerbose(bool verbose) { verbose_ = verbose; }

private:
  void error(const char *msg) {
    if (!verbose_)
      return;
    std::fprintf(stderr, "%s", msg);
  }

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
    if (expr) {
      auto val = expr->CodeGen();
      if (verbose_)
        val->print(llvm::errs()), fprintf(stderr, "\n");
    } else {
      error("[WARN] can't parse expr");
    }

    return;
  }

  void HandleJumpExpr(Token token) {
    static std::stack<WhileAST> wst;
    if (token == Token::TK_JIFORWARD) {
      wst.emplace();
      auto val = wst.top().CodeGen();
      if (verbose_)
        val->print(llvm::errs()), fprintf(stderr, "\n");
      return;
    }

    assert(!wst.empty() && "unmatch ] !");

    wst.top().CodeGen();
    wst.pop();

    return;
  }

private:
  TokenStream<InputStream> token_stream_;

  bool verbose_ = true;
};

} // namespace brainfuck

#endif // BRAINFUCK_PARSER_EXPRPARSER_H_
