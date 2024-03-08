#include "paintives.hpp"

#include <cstdlib>

namespace paintives {
    void clear(drawable* dr, uint8_t3 p) {
        for (uint32_t k(dr->width*dr->height); k--;)
            dr->data[k] = p;
    }

    void line(drawable* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t3 p) {
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
            if(x0 >= 0 && y0 >= 0 && x0 < dr->width && y0 < dr->height)
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

    void fast_rect(drawable* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t3 p) {
        if(x0 > x1 || y0 > y1 || y1 >= dr->height || y0 < 0 ||  x1 >= dr->width || x0 < 0) return;
        uint32_t y;
        for (;x0 <= x1;x0++)
            for (y = y0; y<=y1; y++)
                dr->set_pixel(x0, y, p);
    }

    void rect(drawable* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t3 p) {
        int32_t y;
        if (x1 < x0) {
            y = x1;
            x1 = x0;
            x0 = y;
        }
        if (x1 < 0 || x0 >= dr->width) return;
        if (x0 < 0) x0 = 0;
        if (x1 >= dr->width) x1 = dr->width-1;
        if (y1 < y0) {
            y = y1;
            y1 = y0;
            y0 = y;
        }
        if (y1 < 0 || y0 >= dr->height) return;
        if (y0 < 0) y0 = 0;
        if (y1 >= dr->height) y1 = dr->height-1;
        for (;x0 <= x1;x0++)
            for (y = y0; y<=y1; y++)
                dr->set_pixel(x0, y, p);
    }

    void circ(drawable* dr, int32_t x0, int32_t y0, uint32_t r, uint8_t3 p) {
        int32_t x = 0;
        int32_t y = r;
        int32_t delta = 3 - 2*r;
        while (y >= x) {
            dr->stupid_set_pixel(x0 + x, y0 + y, p);
            dr->stupid_set_pixel(x0 + x, y0 - y, p);
            dr->stupid_set_pixel(x0 - x, y0 + y, p);
            dr->stupid_set_pixel(x0 - x, y0 - y, p);
            dr->stupid_set_pixel(x0 + y, y0 + x, p);
            dr->stupid_set_pixel(x0 + y, y0 - x, p);
            dr->stupid_set_pixel(x0 - y, y0 + x, p);
            dr->stupid_set_pixel(x0 - y, y0 - x, p);
            delta += (delta < 0) ? (4*x+6):(4*(x-(y--))+10);
            x++;
        }
    }

    void sprite(drawable* dr, drawable* sprite, int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
        {
            int32_t p;
            if (x1 < x0) {
                p = x0;
                x0 = x1;
                x1 = p;
            }
            if (x1 < 0 || x0 >= dr->width) return;
            if (y1 < y0) {
                p = y1;
                y1 = y0;
                y0 = p;
            }
            if (y1 < 0 || y0 >= dr->height) return;
        }
        if (sprite->width <= x1-x0) {
            if (sprite->height <= y1-y0) {
                uint32_t sx = 0, sy;
                uint32_t del_sx = sprite->width;
                uint32_t ersx = 0;
                uint32_t del_sy = sprite->height;
                uint32_t ersy;

                int32_t x(x0),y;
                for(; x<= x1; x++) {

                    sy = 0;
                    ersy = 0;

                    for(y = y0; y<= y1; y++) {
                        dr->stupid_set_pixel(x, y, sprite->get_pixel(sx, sy));

                        ersy += del_sy;
                        if (ersy >= y1-y0+1) {
                            ersy -= y1-y0+1;
                            sy++;
                        }
                    }

                    ersx += del_sx;
                    if (ersx >= x1-x0+1) {
                        ersx -= x1-x0+1;
                        sx++;
                    }
                }

            } else {
                uint32_t sx = 0;
                uint32_t del_sx = sprite->width;
                uint32_t ersx = 0;

                uint32_t del_y = y1-y0+1;
                uint32_t ery;
                uint32_t sy;
                int32_t y, x = x0;
                uint32_t3 p;
                uint32_t n;
                for(; x <= x1; x++) {
                    p = {0, 0, 0};
                    n = 0;
                    y = y0;
                    ery = 0;
                    sy = 0;
                    for (; sy < sprite->height; sy++) {
                        p = p + uint8_t3::uint8_t3_to_uint32_t3(sprite->get_pixel(sx, sy));
                        n++;
                        ery += del_y;
                        if (ery >= sprite->height) {
                            dr->stupid_set_pixel(x, y, {(uint8_t)(p.b/n), (uint8_t)(p.g/n), (uint8_t)(p.r/n)});
                            p = {0, 0, 0};
                            n = 0;
                            ery -= sprite->height;
                            y++;
                        }
                    }

                    ersx += del_sx;
                    if (ersx >= x1-x0+1) {
                        ersx -= x1-x0+1;
                        sx++;
                    }
                }
            }
        } else {
            if (sprite->height <= y1-y0) {
                uint32_t sy = 0;
                uint32_t del_sy = sprite->height;
                uint32_t ersy = 0;

                uint32_t del_x = x1-x0+1;
                uint32_t erx;
                uint32_t sx;
                int32_t x, y = y0;
                uint32_t3 p;
                uint32_t n;
                for(; y <= y1; y++) {
                    p = {0, 0, 0};
                    n = 0;
                    x = x0;
                    erx = 0;
                    sx = 0;
                    for (; sx < sprite->width; sx++) {
                        p = p + uint8_t3::uint8_t3_to_uint32_t3(sprite->get_pixel(sx, sy));
                        n++;
                        erx += del_x;
                        if (erx >= sprite->width) {
                            dr->stupid_set_pixel(x, y, {(uint8_t)(p.b/n), (uint8_t)(p.g/n), (uint8_t)(p.r/n)});
                            p = {0, 0, 0};
                            n = 0;
                            erx -= sprite->width;
                            x++;
                        }
                    }

                    ersy += del_sy;
                    if (ersy >= y1 - y0 + 1) {
                        ersy -= y1-y0+1;
                        sy++;
                    }
                }

            } else {
                ///TODO normal algorithm
                uint32_t dsx = sprite->width/(x1-x0), dsy = sprite->height/(y1-y0);
                x1 = __min(x1, dr->width-1);
                y1 = __min(y1, dr->height-1);
                uint32_t x(__max(x0, 0)), y, p = __max(y0, 0);

                for (;x <= x1;x++)
                    for (y = p; y<=y1; y++)
                        dr->set_pixel(x, y, sprite->get_pixel((x-x0)*dsx, (y-y0)*dsy));
            }
        }
    }
}



/*
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