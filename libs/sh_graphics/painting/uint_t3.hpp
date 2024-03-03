#ifndef __UINT8_T3_HPP__
#define __UINT8_T3_HPP__

#include <cinttypes>

typedef struct uint32_t3 {
    uint32_t b, g, r;
    uint32_t3 operator+ (uint32_t3 o) const;
} uint32_t3;

typedef struct uint8_t3 {
    uint8_t b, g, r;
    static uint32_t uint8_t3_to_uint32_t(uint8_t3 c);
    static uint32_t3 uint8_t3_to_uint32_t3(uint8_t3 c);
    static uint8_t3 uint32_t_to_uint8_t3(uint32_t c);
} uint8_t3;


#endif//__UINT8_T3_HPP__