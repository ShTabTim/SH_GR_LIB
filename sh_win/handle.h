#pragma once
#include <cstdint>

typedef struct handle {
	inline void draw_in_handle(uint32_t id, uint32_t argb);

	typedef struct col3 {
		uint8_t b, g, r;
		col3(uint32_t hex = 0);
		col3(uint8_t r, uint8_t g, uint8_t b);
	}col3;
	uint32_t width, height;
	col3* handle;

	void init(uint32_t width, uint32_t height);

	inline void draw(int32_t x, int32_t y, uint32_t argb);

	void line(int32_t cx, int32_t cy, int32_t dx, int32_t dy, uint32_t hex);
	void ring(int32_t cx, int32_t cy, uint32_t r, uint32_t hex);
} handle;