#ifndef __PIXMAP_HPP__
#define __PIXMAP_HPP__

#include <cinttypes>

typedef struct pixmap {
    void* data;
    uint32_t& width;
    uint32_t& height;
    uint8_t& bit_per_pixel; // 1, 4, 8 or 24
} pixmap;

#endif //__PIXMAP_HPP__
