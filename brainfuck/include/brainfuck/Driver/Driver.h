/* ====================================================
#   Copyright (C) 2022  All rights reserved.
#
#   Author        : lanzongwei
#   Email         : lanzongwei541@gmail.com
#   File Name     : Driver.h
#   Last Modified : 2022-04-28 16:03
#   Describe      :
#
# ====================================================*/

#ifndef BRAINFUCK_DRIVER_DRIVER_H_
#define BRAINFUCK_DRIVER_DRIVER_H_

#include <string>

namespace brainfuck {
namespace driver {

class Driver {
public:
  void Run();
  void SetFilename(const std::string &filename) { filename_ = filename; }
  void SetObjectName(const std::string &objectname) {
    objectname_ = objectname;
  }
  void SetInputfile(const std::string &inputfile) { inputfile_ = inputfile; }

private:
  std::string filename_ = "a.o";
  std::string objectname_ = "a.out";
  std::string inputfile_;
};

} // namespace driver
} // namespace brainfuck

#endif // BRAINFUCK_DRIVER_DRIVER_H_
