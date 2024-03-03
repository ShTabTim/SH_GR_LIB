#ifndef __PAINTIVES_HPP__
#define __PAINTIVES_HPP__

#include <cinttypes>

#include "drawable.hpp"
#include "uint_t3.hpp"

namespace paintives {
	void clear(drawable* dr, uint8_t3 p);
	void line(drawable* dr, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t3 p);
    void fast_rect(drawable* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t3 p);
    void rect(drawable* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t3 p);
    void sprite(drawable* dr, drawable* sprite, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
}

#endif//__PAINTIVES_HPP__