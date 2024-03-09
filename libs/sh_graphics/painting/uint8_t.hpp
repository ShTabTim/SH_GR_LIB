#ifndef __UINT8_T_HPP__
#define __UINT8_T_HPP__

#include <cinttypes>

struct uint8_t3;
struct uint8_t4;

typedef struct uint8_t3 {
    uint8_t b, g, r;
    uint8_t3 operator&(uint8_t3 cfrom) const;
    uint8_t3 operator&(uint8_t4 cfrom) const;
} uint8_t3;

typedef struct uint8_t4 {
    uint8_t b, g, r, a;
    static uint8_t4 uint8_t3_to_uint8_t4(uint8_t3 c);
    uint8_t4 operator&(uint8_t3 cfrom) const;
    uint8_t4 operator&(uint8_t4 cfrom) const;
} uint8_t4;


#endif//__UINT8_T_HPP__