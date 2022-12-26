#pragma once

using ColorComponent = unsigned short;

class Color{
    ColorComponent r = 0;
    ColorComponent g = 0;
    ColorComponent b = 0;
    ColorComponent a = 255;
public:
    Color() {  }
    Color(ColorComponent r, ColorComponent g, ColorComponent b, ColorComponent a) { this->r = r; this->g = g; this->b = b; this->a = a; }
    Color(const Color &c) { this->r = c.r; this->g = c.g; this->b = c.b; this->a = c.a; }
};