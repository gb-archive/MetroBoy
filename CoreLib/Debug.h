#pragma once
#include "CoreLib/Types.h"

#include <stdio.h>
#include <stdarg.h>
#include <string>

struct StringDumper : public Dumper {
  std::string s;

  void add_char(char c) override {
    s.push_back(c);
  }

  void operator()(const char* format, ...) override {
    char source_buf[1024];
    va_list args;
    va_start (args, format);
    vsnprintf (source_buf, 1024 ,format, args);
    va_end (args);
    s.append(source_buf);
  }
  void print() { printf("%s", s.c_str()); }
  void clear() { s.clear(); }
};

