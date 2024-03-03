#ifndef __RENDERABLE_HPP__
#define __RENDERABLE_HPP__

#include <cinttypes>
#include <Windows.h>

#include "painting/drawable.hpp"

typedef struct renderable : public drawable {
    HDC hdc;
    uint32_t width;
    uint32_t height;
    BITMAPINFO buf_info;
    void (*rend)(renderable*);
    void init(uint32_t width, uint32_t height, void (*rend)(renderable*));
    void draw();
    void finit();
} renderable;

#endif//__RENDERABLE_HPP__