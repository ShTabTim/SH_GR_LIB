#ifndef __PAINTIVES_HPP__
#define __PAINTIVES_HPP__

#include <cinttypes>
#include "drawable.hpp"

namespace paintives {
	template<typename color1, typename color2> extern void clear(drawable<color1>* dr, color2 p);
    template<typename color1, typename color2> void line(drawable<color1>* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, color2 p);
    template<typename color1, typename color2> void fast_rect(drawable<color1>* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, color2 p);
    template<typename color1, typename color2> void rect(drawable<color1>* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, color2 p);
    template<typename color1, typename color2> void circ(drawable<color1>* dr, int32_t x0, int32_t y0, uint32_t r, color2 p);
    template<typename color1, typename color2> void sprite(drawable<color1>* dr, drawable<color2>* sprite, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
}

#include "paintives.tpp"

#endif//__PAINTIVES_HPP__