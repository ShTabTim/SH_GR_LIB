#ifndef __WINAPI_RENDERABLE_HPP__
#define __WINAPI_RENDERABLE_HPP__

#include "meta_renderable.hpp"
#include <Windows.h>

typedef struct winapi_renderable : public meta_renderable {
    HDC hdc;
    BITMAPINFO buf_info;
    void init(uint32_t renderable_width, uint32_t renderable_height, void (*rend)(meta_renderable*), uint32_t drawable_width, uint32_t drawable_height) override;
    void set_hdc(HDC hdc);
    void draw() override;
    void finit() override;
} winapi_renderable;


#endif//__WINAPI_RENDERABLE_HPP__
