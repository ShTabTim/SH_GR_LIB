#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__

#include <cinttypes>
#include "uint8_t.hpp"
#include <cstdlib>

template<typename color>
class drawable {
public:
    color* data; // ind = y*width+x
    uint32_t width;
    uint32_t height;
    drawable(color* data = 0, uint32_t width = 0, uint32_t height = 0);
    virtual void init(uint32_t width, uint32_t height);
    void resize(uint32_t width, uint32_t height);
    void complex_resize(uint32_t width, uint32_t height);
    color get_pixel(uint32_t x, uint32_t y);
    color get_pixel(uint32_t index) ;
    void set_pixel(uint32_t x, uint32_t y, color p);
    template<typename ocolor>
    void mix_pixel(uint32_t x, uint32_t y, ocolor p);
    void stupid_set_pixel(uint32_t x, uint32_t y, color p);
    template<typename ocolor>
    void stupid_mix_pixel(uint32_t x, uint32_t y, ocolor p);
    void tor_set_pixel(int32_t x, int32_t y, color p);
    template<typename ocolor>
    void tor_mix_pixel(uint32_t x, uint32_t y, ocolor p);
    color& pixel(uint32_t x, uint32_t y);
    color& pixel(uint32_t index);
    virtual void finit();
};

#include "drawable.tpp"

typedef drawable<uint8_t3> drawable3;
typedef drawable<uint8_t4> drawable4;

#endif//__DRAWABLE_HPP__
