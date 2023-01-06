#pragma once


// TODO: Template this even but find away to limit the types to certain primatives
//       ( float, double ) for normalization, and ( uint_8, uint_16, uint_32, uint_64 )
//        for different bit bits per channel, but no classes or structs allowed
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