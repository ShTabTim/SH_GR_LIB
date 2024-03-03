#include "paintives.hpp"

#include <cstdlib>

namespace paintives {
    void clear(drawable* dr, uint8_t3 p) {
        for (uint32_t k(dr->width*dr->height); k--;)
            dr->data[k] = p;
    }

    void line(drawable* dr, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t3 p) {
        //x's defs
        int8_t dir_x = (x1 > x0) - (x0 > x1);
        uint32_t del_x = (x1 > x0) ? (x1-x0) : (x0-x1);
        uint32_t erx = 0;

        //y's defs
        int8_t dir_y = (y1 > y0) - (y0 > y1);
        uint32_t del_y = (y1 > y0) ? (y1-y0) : (y0-y1);
        uint32_t ery = 0;

        //max variation
        uint32_t max_del = __max(del_x, del_y);

        for(uint32_t k = max_del; (x0!=x1)&&(y0!=y1)&&(k--);) {
            dr->set_pixel(x0, y0, p);

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
    }

    void rect(drawable* dr, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t3 p) {
        if(x0 > x1 || y0 > y1) return;
        for (;x0 <= x1;x0++)
            for (uint32_t y(y0); y<=y1; y++)
                dr->set_pixel(x0, y, p);
    }
}



/*
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
*/