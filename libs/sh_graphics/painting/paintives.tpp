#ifndef __PAINTIVES_TPP__
#define __PAINTIVES_TPP__

#include <cstdlib>

namespace paintives {
    template<typename color> void clear(drawable<color>* dr, color p) {
        for (uint32_t k(dr->width*dr->height); k--;)
            dr->data[k] = p;
    }

    template<typename color1, typename color2> void line(drawable<color1>* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, color2 p) {
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
                dr->mix_pixel(x0, y0, p);

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

    template<typename color1, typename color2> void fast_rect(drawable<color1>* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, color2 p) {
        if(x0 > x1 || y0 > y1 || y1 >= dr->height || y0 < 0 ||  x1 >= dr->width || x0 < 0) return;
        uint32_t y;
        for (;x0 <= x1;x0++)
            for (y = y0; y<=y1; y++)
                dr->mix_pixel(x0, y, p);
    }

    template<typename color1, typename color2> void rect(drawable<color1>* dr, int32_t x0, int32_t y0, int32_t x1, int32_t y1, color2 p) {
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
                dr->mix_pixel(x0, y, p);
    }

    template<typename color1, typename color2> void circ(drawable<color1>* dr, int32_t x0, int32_t y0, uint32_t r, color2 p) {
        int32_t x = 0;
        int32_t y = r;
        int32_t delta = 3 - 2*r;
        while (y >= x) {
            dr->stupid_mix_pixel(x0 + x, y0 + y, p);
            dr->stupid_mix_pixel(x0 + x, y0 - y, p);
            dr->stupid_mix_pixel(x0 - x, y0 + y, p);
            dr->stupid_mix_pixel(x0 - x, y0 - y, p);
            dr->stupid_mix_pixel(x0 + y, y0 + x, p);
            dr->stupid_mix_pixel(x0 + y, y0 - x, p);
            dr->stupid_mix_pixel(x0 - y, y0 + x, p);
            dr->stupid_mix_pixel(x0 - y, y0 - x, p);
            delta += (delta < 0) ? (4*x+6):(4*(x-(y--))+10);
            x++;
        }
    }

    ///TODO normal algorithm for min
    template<typename color1, typename color2> void sprite(drawable<color1>* dr, drawable<color2>* sprite, int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
        {
            int32_t p;
            if (x1 < x0) {
                p = x0;
                x0 = x1;
                x1 = p;
            }
            if (x1 < 0 || x0 >= (int32_t)dr->width) return;
            if (y1 < y0) {
                p = y1;
                y1 = y0;
                y0 = p;
            }
            if (y1 < 0 || y0 >= (int32_t)dr->height) return;
        }

        uint32_t del_x = x1-x0+1;
        uint32_t del_y = y1-y0+1;

        if (sprite->width <del_x) {
            if (sprite->height < del_y) {
                uint32_t sx = 0;
                uint32_t ersx = 0;
                uint32_t sy0 = 0;
                uint32_t ersy0 = 0;

                for (;x0 < 0; x0++) {
                    ersx += sprite->width;
                    if (ersx >= del_x) {
                        ersx -= del_x;
                        sx++;
                    }
                }
                for (; y0 < 0; y0++) {
                    ersy0 += sprite->height;
                    if (ersy0 >= del_y) {
                        ersy0 -= del_y;
                        sy0++;
                    }
                }

                x1 = __min(x1, dr->width-1);
                y1 = __min(y1, dr->height-1);

                for (;x0<= x1; x0++) {

                    for (uint32_t sy = sy0, ersy = ersy0, y = y0; y <= y1; y++) {
                        dr->mix_pixel(x0, y, sprite->get_pixel(sx, sy));

                        ersy += sprite->height;
                        if (ersy >= del_y) {
                            ersy -= del_y;
                            sy++;
                        }
                    }

                    ersx += sprite->width;
                    if (ersx >= del_x) {
                        ersx -= del_x;
                        sx++;
                    }
                }

            } else {
                uint32_t sx = 0;
                uint32_t ersx = 0;

                uint32_t dsy = (y1 == y0) ? 0 : sprite->height/(y1-y0);

                for(; x0 < 0; x0++) {
                    ersx += sprite->width;
                    if (ersx >= del_x) {
                        ersx -= del_x;
                        sx++;
                    }
                }
                uint32_t y, p = __max(y0, 0);

                x1 = __min(x1, dr->width-1);
                y1 = __min(y1, dr->height-1);

                for(; x0 <= x1; x0++) {
                    for (y = p; y < y1; y++)
                        dr->mix_pixel(x0, y, sprite->get_pixel(sx, (y-y0)*dsy));

                    ersx += sprite->width;
                    if (ersx >= del_x) {
                        ersx -= del_x;
                        sx++;
                    }
                }
            }
        } else {
            if (sprite->height < del_y) {
                uint32_t sy = 0;
                uint32_t ersy = 0;

                uint32_t dsx = (x1 == x0) ? 0 : sprite->width/(x1-x0);

                for(; y0 < 0; y0++) {
                    ersy += sprite->height;
                    if (ersy >= del_y) {
                        ersy -= del_y;
                        sy++;
                    }
                }
                uint32_t x, p = __max(x0, 0);

                x1 = __min(x1, dr->width-1);
                y1 = __min(y1, dr->height-1);

                for(; y0 <= y1; y0++) {
                    for (x = p; x < x1; x++)
                        dr->mix_pixel(x, y0, sprite->get_pixel((x-x0)*dsx, sy));

                    ersy += sprite->height;
                    if (ersy >= del_y) {
                        ersy -= del_y;
                        sy++;
                    }
                }
            } else {
                uint32_t dsx = (x1 == x0) ? 0 : sprite->width/(x1-x0), dsy = (y1 == y0) ? 0 : sprite->height/(y1-y0);

                uint32_t x(__max(x0, 0)), y, p = __max(y0, 0);

                x1 = __min(x1, dr->width-1);
                y1 = __min(y1, dr->height-1);

                for (;x <= x1;x++)
                    for (y = p; y<=y1; y++)
                        dr->mix_pixel(x, y, sprite->get_pixel((x-x0)*dsx, (y-y0)*dsy));
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

#endif//__PAINTIVES_TPP__