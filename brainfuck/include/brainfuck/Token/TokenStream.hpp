/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : TokenStream.hpp
#   Last Modified : 2022-04-10 23:19
#   Describe      :
#
# ====================================================*/

#ifndef BRAINFUCK_TOKEN_TOKENSTREAM_H_
#define BRAINFUCK_TOKEN_TOKENSTREAM_H_

#include <iostream>
#include <unordered_map>

#include "brainfuck/Token/Token.h"

namespace brainfuck {

template <typename InputStream> class TokenStream {
public:
  explicit operator bool() const { return reader_.operator bool(); }

  TokenStream &operator>>(Token &token) {
    if (!reader_) {
      token = Token::TK_EOF;
      return *this;
    }
    char tk;
    reader_ >> tk;
    if (char2token_.find(tk) == char2token_.end())
      token = Token::TK_UNKNOW;
    else
      token = char2token_[tk];
    return *this;
  }

private:
  InputStream reader_;
  inline static std::unordered_map<char, Token> char2token_{
      {'<', Token::TK_LEFT},      {'>', Token::TK_RIGHT},
      {'+', Token::TK_ADD},       {'-', Token::TK_MINUS},
      {'.', Token::TK_OUTPUT},    {',', Token::TK_INPUT},
      {'[', Token::TK_JIFORWARD}, {']', Token::TK_JIBACK}};
};

} // namespace brainfuck

#endif // BRAINFUCK_TOKEN_TOKENSTREAM_H_
