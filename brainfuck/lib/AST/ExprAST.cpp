/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : ExprAST.cpp
#   Last Modified : 2022-04-28 14:47
#   Describe      :
#
# ====================================================*/

#include "brainfuck/AST/ExprAST.h"

#include <cassert> // for assert

#include "llvm/IR/BasicBlock.h"   // for BasicBlock
#include "llvm/IR/Constants.h"    // for ConstantInt
#include "llvm/IR/Function.h"     // for Function
#include "llvm/IR/GlobalValue.h"  // for GlobalValue::ExternalLinkage
#include "llvm/IR/Instructions.h" // for LoadInst, CallInst, AllocaInst
#include "llvm/IR/Type.h"         // for Type

namespace brainfuck {

void BaseAST::Initialize(int alloc_size) {
  main_ = llvm::Function::Create(
      llvm::FunctionType::get(llvm::Type::getInt32Ty(context_), false),
      llvm::Function::ExternalLinkage, "main", &module_);
  builder_.SetInsertPoint(llvm::BasicBlock::Create(context_, "entry", main_));
  data_ = builder_.CreateAlloca(builder_.getInt8PtrTy(), nullptr, "data");
  ptr_ = builder_.CreateAlloca(builder_.getInt8PtrTy(), nullptr, "ptr");
  auto calloc = module_.getOrInsertFunction(
      "calloc", llvm::FunctionType::get(
                    llvm::Type::getInt8PtrTy(context_),
                    {builder_.getInt64Ty(), builder_.getInt64Ty()}, false));
  llvm::Value *data = builder_.CreateCall(
      calloc, {builder_.getInt64(alloc_size), builder_.getInt64(1)});
  builder_.CreateStore(data, data_);
  builder_.CreateStore(data, ptr_);
}

void BaseAST::Finalize() {
  auto free = module_.getOrInsertFunction("free", builder_.getVoidTy(),
                                          builder_.getInt8PtrTy());
  builder_.CreateCall(free,
                      {builder_.CreateLoad(builder_.getInt8PtrTy(), data_)});

  builder_.CreateRet(builder_.getInt32(0));
}

llvm::Value *MoveExprAST::CodeGen() {
  builder_.CreateStore(builder_.CreateInBoundsGEP(
                           builder_.getInt8Ty(),
                           builder_.CreateLoad(builder_.getInt8PtrTy(), ptr_),
                           builder_.getInt32(diff_)),
                       ptr_);
  return ptr_;
}

llvm::Value *UnaryExprAST::CodeGen() {
  int diff = 0;
  switch (op_) {
  case Token::TK_ADD:
    diff = 1;
    break;
  case Token::TK_MINUS:
    diff = -1;
    break;
  default:
    assert(false && "unsupport unary opration");
  }
  llvm::Value *val = builder_.CreateLoad(builder_.getInt8PtrTy(), ptr_);
  builder_.CreateStore(
      builder_.CreateAdd(builder_.CreateLoad(builder_.getInt8Ty(), val),
                         builder_.getInt8(diff)),
      val);
  return val;
}

llvm::Value *OutputExprAST::CodeGen() {
  llvm::Value *val = builder_.CreateLoad(builder_.getInt8PtrTy(), ptr_);
  return builder_.CreateCall(
      putchar_,
      builder_.CreateSExt(builder_.CreateLoad(builder_.getInt8Ty(), val),
                          builder_.getInt32Ty()));
}

llvm::Value *InputExprAST::CodeGen() {
  llvm::Value *val = builder_.CreateLoad(builder_.getInt8PtrTy(), ptr_);
  builder_.CreateStore(
      builder_.CreateTrunc(builder_.CreateCall(getchar_), builder_.getInt8Ty()),
      val);
  return val;
}

llvm::Value *WhileAST::CodeGen() {
  if (!cond_block_) {
    cond_block_ = llvm::BasicBlock::Create(context_, "while_cond", main_);
    body_block_ = llvm::BasicBlock::Create(context_, "while_body", main_);
    end_block_ = llvm::BasicBlock::Create(context_, "while_end", main_);

    builder_.CreateBr(cond_block_);
    builder_.SetInsertPoint(cond_block_);

    llvm::Value *val = builder_.CreateLoad(builder_.getInt8PtrTy(), ptr_);
    builder_.CreateCondBr(
        builder_.CreateICmpNE(builder_.CreateLoad(builder_.getInt8Ty(), val),
                              builder_.getInt8(0)),
        body_block_, end_block_);

    builder_.SetInsertPoint(body_block_);
    return val;
  }

  builder_.CreateBr(cond_block_);
  builder_.SetInsertPoint(end_block_);
  return nullptr;
}

} // namespace brainfuck
