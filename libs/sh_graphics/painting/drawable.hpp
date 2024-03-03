#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__

#include <cinttypes>

#include "uint8_t3.hpp"

typedef struct drawable {
    uint8_t3* data = 0; // 3*(ind = y*width+x)+c
    uint32_t width = 0;
    uint32_t height = 0;
    void init(uint32_t width, uint32_t height);
    void resize(uint32_t width, uint32_t height);
    void complex_resize(uint32_t width, uint32_t height);
    void set_pixel(uint32_t x, uint32_t y, uint32_t p);
    void set_pixel(uint32_t x, uint32_t y, uint8_t3 p);
    uint8_t3& pixel(uint32_t x, uint32_t y);
    uint8_t3& pixel(uint32_t index);
    void finit();
} drawable;

#endif//__DRAWABLE_HPP__