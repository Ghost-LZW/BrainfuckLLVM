/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : Token.h
#   Last Modified : 2022-04-10 20:04
#   Describe      :
#
# ====================================================*/

#ifndef BRAINFUCK_TOKEN_TOKEN_H_
#define BRAINFUCK_TOKEN_TOKEN_H_

namespace brainfuck {

enum class Token {
  TK_EOF,
  TK_UNKNOW,
  TK_LEFT,
  TK_RIGHT,
  TK_ADD,
  TK_MINUS,
  TK_OUTPUT,
  TK_INPUT,
  TK_JIFORWARD,
  TK_JIBACK
};

}

#endif // BRAINFUCK_TOKEN_TOKEN_H_
