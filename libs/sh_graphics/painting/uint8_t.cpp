#include "uint8_t.hpp"

uint8_t4 uint8_t4::uint8_t3_to_uint8_t4(uint8_t3 c) {
    return {c.b, c.g, c.r, 0xFF};
}

uint8_t3 uint8_t3::operator&(uint8_t3 c) const {
    return c;
}

uint8_t3 uint8_t3::operator&(uint8_t4 c) const {
    return {
    (uint8_t)(((uint32_t)c.a*(uint32_t)c.b+(0xFF-(uint32_t)c.a)*(uint32_t)b)/0xFF),
    (uint8_t)(((uint32_t)c.a*(uint32_t)c.g+(0xFF-(uint32_t)c.a)*(uint32_t)g)/0xFF),
    (uint8_t)(((uint32_t)c.a*(uint32_t)c.r+(0xFF-(uint32_t)c.a)*(uint32_t)r)/0xFF)
    };
}

uint8_t4 uint8_t4::operator&(uint8_t3 c) const {
    return uint8_t3_to_uint8_t4(c);
}

uint8_t4 uint8_t4::operator&(uint8_t4 c) const {
    if(a == 0 && c.a == 0) return {0, 0, 0, 0};
    uint32_t n = (0xFF-(uint32_t)c.a)*(uint32_t)a;
    uint32_t m = 0xFF*(uint32_t)c.a + n;
    return {
    (uint8_t)((0xFF*(uint32_t)c.a*(uint32_t)c.b + n*(uint32_t)b)/m),
    (uint8_t)((0xFF*(uint32_t)c.a*(uint32_t)c.g + n*(uint32_t)g)/m),
    (uint8_t)((0xFF*(uint32_t)c.a*(uint32_t)c.r + n*(uint32_t)r)/m),
    (uint8_t)(m/0xFF)
    };
}
