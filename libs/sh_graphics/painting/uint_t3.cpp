#include "uint_t3.hpp"

uint32_t3 uint32_t3::operator+ (uint32_t3 o) const {
    return {b + o.b, g + o.g, r + o.r};
}

uint32_t uint8_t3::uint8_t3_to_uint32_t(uint8_t3 c) {
    return c.r*0x10000 + c.g*0x100 + c.b;
}

uint32_t3 uint8_t3::uint8_t3_to_uint32_t3(uint8_t3 c) {
    return {(uint32_t)c.b, (uint32_t)c.g, (uint32_t)c.r};
}

uint8_t3 uint8_t3::uint32_t_to_uint8_t3(uint32_t c) {
    return {(uint8_t)c, (uint8_t)(c >> 8), (uint8_t)(c >> 16)};
}