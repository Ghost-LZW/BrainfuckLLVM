/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : ExprAST.h
#   Last Modified : 2022-04-10 23:19
#   Describe      :
#
# ====================================================*/

#ifndef BRAINFUCK_AST_EXPRAST_H_
#define BRAINFUCK_AST_EXPRAST_H_

#include "brainfuck/Token/Token.h"

namespace brainfuck {

class ExprAST {
public:
  virtual ~ExprAST() = default;
  // virtual llvm::Value *CodeGen() = 0;
};

class UnaryExprAST : public ExprAST {
public:
  UnaryExprAST(/*Token op*/) /*: op_(op)*/ {}

private:
  //    Token op_;
};

class JumpExprAST : public ExprAST {
public:
  JumpExprAST() {}

private:
  //    int jump_pos;
};

} // namespace brainfuck

#endif // BRAINFUCK_AST_EXPRAST_H_
