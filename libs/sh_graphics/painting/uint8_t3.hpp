#ifndef __UINT8_T3_HPP__
#define __UINT8_T3_HPP__

#include <cinttypes>

typedef struct uint8_t3 {
    uint8_t r, g, b;
    static uint32_t uint8_t3_to_uint32_t(uint8_t3 c);
    static uint8_t3 uint32_t_to_uint8_t3(uint32_t c);
} uint8_t3;

#endif//__UINT8_T3_HPP__