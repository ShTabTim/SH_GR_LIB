#ifndef __META_RENDERABLE_HPP__
#define __META_RENDERABLE_HPP__

#include <cinttypes>
#include "../painting/drawable.hpp"

typedef struct meta_renderable : public drawable3 {
    uint32_t width;
    uint32_t height;
    void (*rend)(meta_renderable*);
    virtual void init(uint32_t width, uint32_t height, void (*rend)(meta_renderable*), uint32_t drawable_width, uint32_t drawable_height);
    virtual void draw();
} meta_renderable;

#endif//__META_RENDERABLE_HPP__