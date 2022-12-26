#pragma once

#include <stdexcept>
#include <memory>

#include "String.hpp"
#include "StackTrace.hpp"

class Exception : public std::logic_error {
  public:
    explicit Exception(const String& arg) : std::logic_error(arg) {}

    virtual const String getMsg();
    SharedStringPointer getStackTrace();

  private:
    StackTrace &st = StackTrace::getInstance();
};
