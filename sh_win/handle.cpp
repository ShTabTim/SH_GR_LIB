#include "handle.h"
#include <stdlib.h>

handle::col3::col3(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
handle::col3::col3(uint32_t hex) : r((hex & 0x00FF0000)>>16), g((hex & 0x0000FF00)>>8), b(hex & 0x000000FF) {}

void handle::init(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;
	handle = new col3[width * height];
}

inline void handle::draw_in_handle(uint32_t id, uint32_t argb) {
	handle[id] = col3(argb);
}

inline void handle::draw(int32_t x, int32_t y, uint32_t argb) {
	if (x < 0 || x >= width || y < 0 || y >= height) return;
	handle[x+y*width] = col3(argb);
}

void handle::line(int32_t cx, int32_t cy, int32_t dx, int32_t dy, uint32_t hex) {
#define __max__(a00, b00) (((a00) > (b00)) ? (a00) : (b00))
#define __sign__(a00) (((a00)>0)-((a00)<0))
#define __abs__(a00) (((a00)>0)?(a00):(-a00))

	//x's defs
	int32_t dir_x = __sign__(dx);
	uint32_t del_x = __abs__(dx);
	uint32_t erx = 0;
	int32_t x = 0;

	//y's defs
	int32_t dir_y = __sign__(dy);
	uint32_t del_y = __abs__(dy);
	uint32_t ery = 0;
	int32_t y = 0;

	//max variation
	uint32_t max_del = __max__(del_x, del_y);

	while (x != dx && y != dy) {
		draw(cx + x, cy + y, hex);

		__asm {
//x movement
			mov eax, erx
			add eax, del_x

			cmp eax, max_del
			jb erx_less_or_equal_max_del

				sub eax, max_del
				mov ebx, x
				add ebx, dir_x
				mov x, ebx

			erx_less_or_equal_max_del :
			mov erx, eax
		
//y movement
			mov eax, ery
			add eax, del_y

			cmp eax, max_del
			jb ery_less_or_equal_max_del

				sub eax, max_del
				mov ebx, y
				add ebx, dir_y
				mov y, ebx

			ery_less_or_equal_max_del :
			mov ery, eax
		}
	}
#undef __max__
#undef __sign__
#undef __abs__
}

void handle::ring(int32_t cx, int32_t cy, uint32_t r, uint32_t hex) {
	if (!r) {
		draw(cx, cy, hex);
		return;
	}
	uint32_t x(0), y(r);
	while (x <= y) {
		//draws 8 parts of the ring
		draw(cx + x, cy + y, hex);
		draw(cx + x, cy - y, hex);
		draw(cx - x, cy + y, hex);
		draw(cx - x, cy - y, hex);
		draw(cx + y, cy + x, hex);
		draw(cx + y, cy - x, hex);
		draw(cx - y, cy + x, hex);
		draw(cx - y, cy - x, hex);
		
		x++;
		//O(x^6) power series approximation of sqrt(r^2 - x^2)
		y = r - (x*x*(4*r*r + x*x))/(r*r*r*8);
	}
}
