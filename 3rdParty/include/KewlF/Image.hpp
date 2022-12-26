#pragma once

#include "String.hpp"

class Image {
private:


public:
    Image() = default;
    Image(String &filename);
    ~Image();

};