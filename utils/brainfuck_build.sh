#!/bin/bash
# ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : brainfuck_build.sh
#   Last Modified : 2022-04-10 23:10
#   Describe      : 
#
# ====================================================

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE=include-what-you-use -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang $@
