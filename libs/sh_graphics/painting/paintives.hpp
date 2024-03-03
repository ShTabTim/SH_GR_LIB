#ifndef __PAINTIVES_HPP__
#define __PAINTIVES_HPP__

#include <cinttypes>

#include "drawable.hpp"
#include "uint8_t3.hpp"

namespace paintives {
	void clear(drawable* dr, uint8_t3 p);
	void line(drawable* dr, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t3 p);
	void rect(drawable* dr, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t3 p);
}

#endif//__PAINTIVES_HPP__