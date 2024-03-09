#include "meta_renderable.hpp"

void meta_renderable::init(uint32_t _width, uint32_t _height, void (*_rend)(meta_renderable*), uint32_t _drawable_width, uint32_t _drawable_height) {
    drawable3::init(_drawable_width, _drawable_height);

    width = _width;
    height = _height;
    rend = _rend;
}

void meta_renderable::draw() {
    rend(this);
}