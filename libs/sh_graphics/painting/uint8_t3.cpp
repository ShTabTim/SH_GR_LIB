#include "uint8_t3.hpp"

uint32_t uint8_t3::uint8_t3_to_uint32_t(uint8_t3 c) {
    return c.r + c.b*0x100 + c.g*0x10000;
}

uint8_t3 uint8_t3::uint32_t_to_uint8_t3(uint32_t c) {
    return {(uint8_t)c, (uint8_t)(c >> 8), (uint8_t)(c >> 16)};
}