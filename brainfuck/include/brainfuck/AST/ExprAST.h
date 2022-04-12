/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : ExprAST.h
#   Last Modified : 2022-04-27 21:04
#   Describe      :
#
# ====================================================*/

#ifndef BRAINFUCK_AST_EXPRAST_H_
#define BRAINFUCK_AST_EXPRAST_H_

#include "brainfuck/Token/Token.h"    // for Token
#include "llvm/ADT/StringRef.h"       // for StringRef
#include "llvm/IR/DerivedTypes.h"     // for FunctionCallee, IntegerType
#include "llvm/IR/IRBuilder.h"        // for IRBuilder
#include "llvm/IR/LLVMContext.h"      // for LLVMContext
#include "llvm/IR/Module.h"           // for Module
#include "llvm/Support/raw_ostream.h" // for errs, raw_fd_ostream
namespace llvm {
class BasicBlock;
}
namespace llvm {
class Function;
}
namespace llvm {
class Value;
}

namespace brainfuck {

class BaseAST {
public:
  virtual ~BaseAST() = default;

  static void Initialize(int alloc_size = 40000);
  static void Print() { module_.print(llvm::errs(), nullptr); }

protected:
  static inline llvm::LLVMContext context_;
  static inline llvm::IRBuilder<> builder_{context_};
  static inline llvm::Module module_{"top", context_};
  static inline llvm::Function *main_;
  static inline llvm::Value *data_;
  static inline llvm::Value *ptr_;
};

class ExprAST : public BaseAST {
public:
  virtual ~ExprAST() = default;
  virtual llvm::Value *CodeGen() = 0;
};

class MoveExprAST : public ExprAST {
public:
  MoveExprAST(int diff) : diff_(diff) {}
  llvm::Value *CodeGen() override;

private:
  int diff_;
};

class UnaryExprAST : public ExprAST {
public:
  UnaryExprAST(Token op) : op_(op) {}
  llvm::Value *CodeGen() override;

private:
  Token op_;
};

class OutputExprAST : public ExprAST {
public:
  llvm::Value *CodeGen() override;

private:
  static inline llvm::FunctionCallee putchar_ = module_.getOrInsertFunction(
      "putchar", builder_.getInt32Ty(), builder_.getInt32Ty());
};

class InputExprAST : public ExprAST {
public:
  llvm::Value *CodeGen() override;

private:
  static inline llvm::FunctionCallee getchar_ =
      module_.getOrInsertFunction("getchar", builder_.getInt32Ty());
};

class WhileAST : public BaseAST {
public:
  llvm::Value *CodeGen();

private:
  llvm::BasicBlock *cond_block_{nullptr};
  llvm::BasicBlock *body_block_{nullptr};
  llvm::BasicBlock *end_block_{nullptr};
};

} // namespace brainfuck

#endif // BRAINFUCK_AST_EXPRAST_H_
