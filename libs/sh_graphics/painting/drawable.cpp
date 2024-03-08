#include <cstdlib>
#include "drawable.hpp"

drawable::drawable(uint8_t3* _data, uint32_t _width, uint32_t _height) {
    data = _data;
    width = _width;
    height = _height;
}

void drawable::init(uint32_t _width, uint32_t _height) {
    width = _width;
    height = _height;
    if(data)free(data);
    data = (uint8_t3*) malloc(width * height * sizeof(uint8_t3));
}

void drawable::resize(uint32_t _width, uint32_t _height) {
    width = _width;
    height = _height;
    data = (uint8_t3*) realloc(data, width * height * sizeof(uint8_t3));
}

void drawable::complex_resize(uint32_t _width, uint32_t _height) {
    if(_width == width) {
        height = _height;
        data = (uint8_t3*) realloc(data, width * height * sizeof(uint8_t3));
    } else if (width > _width) {
        height = __min(height, _height);
        for(uint32_t y = 1; y < height; y++)
            for(uint32_t x = 0; x < _width; x++) {
                data[y*_width+x] = data[y*width+x];
            }
        width = _width;
        height = _height;
        data = (uint8_t3*) realloc(data, width * height * sizeof(uint8_t3));
    } else {
        data = (uint8_t3*) realloc(data, _width * _height * sizeof(uint8_t3));
        height = __min(height, _height);
        for(uint32_t y = height-1; y > 0 ; y--)
            for(uint32_t x = _width;x--;) {
                data[y*_width+x] = data[y*width+x];
            }
        width = _width;
        height = _height;
    }
}

uint8_t3 drawable::get_pixel(uint32_t x, uint32_t y) {
    return data[y*width+x];
}

uint8_t3 drawable::get_pixel(uint32_t index) {
    return data[index];
}

void drawable::set_pixel(uint32_t x, uint32_t y, uint32_t p) {
    *(uint32_t*)(data+(y*width+x)) = (*(uint32_t*)(data+(y*width+x))&0xFF000000)|(p&0xFFFFFF);
}

void drawable::set_pixel(uint32_t x, uint32_t y, uint8_t3 p) {
    data[y*width+x] = p;
}

void drawable::stupid_set_pixel(uint32_t x, uint32_t y, uint8_t3 p) {
    if(x < width && y < height)
        data[y*width+x] = p;
}

void drawable::tor_set_pixel(int32_t x, int32_t y, uint8_t3 p) {
    data[(y >= 0 ? y%height : height + y%height)*width+(x >= 0 ? x%width : width + x%width)] = p;
}

uint8_t3& drawable::pixel(uint32_t x, uint32_t y) {
    return data[y*width+x];
}

uint8_t3& drawable::pixel(uint32_t index) {
    return data[index];
}

void drawable::finit() {
    if(data)free(data);
    data = 0;
}