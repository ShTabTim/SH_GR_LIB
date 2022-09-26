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

void handle::clear(uint32_t hex) {
	for (uint32_t i(width* height); i--; handle[i] = col3(hex));
}

void handle::line(int32_t cx, int32_t cy, int32_t dx, int32_t dy, uint32_t hex) {
#define __max__(a00, b00) (((a00) > (b00)) ? (a00) : (b00))
#define __sign__(a00) ((a00)?(((a00)>0)?1:-1):0)
#define __abs__(a00) (((a00)<0)?(-a00):(a00))

	//x's defs
	int8_t dir_x = __sign__(dx);
	uint32_t del_x = __abs__(dx);
	uint32_t erx = 0;
	int32_t x = 0;

	//y's defs
	int8_t dir_y = __sign__(dy);
	uint32_t del_y = __abs__(dy);
	uint32_t ery = 0;
	int32_t y = 0;

	//max variation
	uint32_t max_del = __max__(del_x, del_y);

	while (x != dx && y != dy) {
		draw(cx + x, cy + y, hex);

		//x movement
		erx += del_x;
		if (erx >= max_del) {
			erx -= max_del;
			x += dir_x;
		}

		//y movement
		ery += del_y;
		if (ery >= max_del) {
			ery -= max_del;
			y += dir_y;
		}
	}
#undef __max__
#undef __sign__
#undef __abs__
}

void handle::line2p(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t hex) {
#define __max__(a00, b00) (((a00) > (b00)) ? (a00) : (b00))
#define __sign__(a00) ((a00)?(((a00)>0)?1:-1):0)
#define __abs__(a00) (((a00)<0)?(-a00):(a00))


	//x's defs
	x1 -= x0;
	int8_t dir_x = __sign__(x1);
	uint32_t del_x = __abs__(x1);
	x1 += x0;
	uint32_t erx = 0;

	//y's defs
	y1 -= y0;
	int8_t dir_y = __sign__(y1);
	uint32_t del_y = __abs__(y1);
	y1 += y0;
	uint32_t ery = 0;

	//max variation
	uint32_t max_del = __max__(del_x, del_y);

	while (x0 != x1 && y0 != y1) {
		draw(x0, y0, hex);

		//x movement
		erx += del_x;
		if (erx >= max_del) {
			erx -= max_del;
			x0 += dir_x;
		}

		//y movement
		ery += del_y;
		if (ery >= max_del) {
			ery -= max_del;
			y0 += dir_y;
		}
	}
#undef __max__
#undef __sign__
#undef __abs__
}

void handle::ring(int32_t cx, int32_t cy, uint32_t r, uint32_t hex) {
#define __y_from_x__(x00, r00) ((r00) - ((((x00) * (x00) * ((((r00) * (r00))<<2) + (x00) * (x00))) / ((r00) * (r00) * (r00))) >> 3))
	if (!r) {
		draw(cx, cy, hex);
		return;
	}
	uint32_t x(0), y(r);
	while (x < y) {
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
		y = __y_from_x__(x, r);
	}
	if (x != y) return;
	draw(cx + x, cy + x, hex);
	draw(cx + x, cy - x, hex);
	draw(cx - x, cy + x, hex);
	draw(cx - x, cy - x, hex);

#undef __y_from_x__
}

void handle::circ(int32_t cx, int32_t cy, uint32_t r, uint32_t hex) {
#define __y_from_x__(x00, r00) ((r00) - ((((x00) * (x00) * ((((r00) * (r00))<<2) + (x00) * (x00))) / ((r00) * (r00) * (r00))) >> 3))
	draw(cx, cy, hex);
	if (!r)	return;
	for (uint32_t m(1); m <= r; m++) {
		draw(cx, cy + m, hex);
		draw(cx, cy - m, hex);
	}
	uint32_t x(1), y(__y_from_x__(x, r));
	while (x < y) {
		draw(cx + x, cy, hex);
		draw(cx - x, cy, hex);
		draw(cx + y, cy, hex);
		draw(cx - y, cy, hex);
		for (uint32_t m(1); m <= y; m++) {
			draw(cx + x, cy + m, hex);
			draw(cx + x, cy - m, hex);
			draw(cx - x, cy + m, hex);
			draw(cx - x, cy - m, hex);
		}
		for (uint32_t n(1); n <= x; n++) {
			draw(cx + y, cy + n, hex);
			draw(cx + y, cy - n, hex);
			draw(cx - y, cy + n, hex);
			draw(cx - y, cy - n, hex);
		}
		x++;
		//O(x^6) power series approximation of sqrt(r^2 - x^2)
		y = __y_from_x__(x, r);
	}
	if (x != y) return;
	draw(cx + x, cy, hex);
	draw(cx - x, cy, hex);
	for (uint32_t m(1); m <= x; m++) {
		draw(cx + x, cy + m, hex);
		draw(cx + x, cy - m, hex);
		draw(cx - x, cy + m, hex);
		draw(cx - x, cy - m, hex);
	}
#undef __y_from_x__
}

void handle::rect(int32_t cx, int32_t cy, int32_t dx, int32_t dy, uint32_t hex) {
#define __sign__(a00) ((a00)?(((a00)>0)?1:-1):0)
	int8_t dir_x = __sign__(dx);
	int8_t dir_y = __sign__(dy);
	dx += dir_x;
	dy += dir_y;
	for (int32_t x(0); x != dx; x += dir_x)
		for (int32_t y(0); y != dy; y += dir_y)
			draw(cx + x, cy + y, hex);
#undef __sign__
}
void handle::rect2p(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t hex) {
#define __sign__(a00) ((a00)?(((a00)>0)?1:-1):0)
	x1 -= x0;
	int8_t dir_x = __sign__(x1);
	x1 += x0 + dir_x;

	y1 -= y0;
	int8_t dir_y = __sign__(y1);
	y1 += y0 + dir_y;

	for (; x0 != x1; x0 += dir_x)
		for (int32_t y(y0); y != y1; y += dir_y)
			draw(x0, y, hex);
#undef __sign__
}