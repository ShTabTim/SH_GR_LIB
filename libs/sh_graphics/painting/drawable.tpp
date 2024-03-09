#ifndef __DRAWABLE_TPP__
#define __DRAWABLE_TPP__

template<typename color>
drawable<color>::drawable(color* _data, uint32_t _width, uint32_t _height) {
    width = _width;
    height = _height;
    data = _data;
}

template<typename color>
void drawable<color>::init(uint32_t _width, uint32_t _height) {
    width = _width;
    height = _height;
    if(data)free(data);
    data = (color*) malloc(width * height * sizeof(color));
}

template<typename color>
void drawable<color>::resize(uint32_t _width, uint32_t _height) {
    width = _width;
    height = _height;
    data = (color*) realloc(data, width * height * sizeof(color));
}
template<typename color>
void drawable<color>::complex_resize(uint32_t _width, uint32_t _height) {
    if(_width == width) {
        height = _height;
        data = (color*) realloc(data, width * height * sizeof(color));
    } else if (width > _width) {
        height = __min(height, _height);
        for(uint32_t y = 1; y < height; y++)
            for(uint32_t x = 0; x < _width; x++) {
                data[y*_width+x] = data[y*width+x];
            }
        width = _width;
        height = _height;
        data = (color*) realloc(data, width * height * sizeof(color));
    } else {
        data = (color*) realloc(data, _width * _height * sizeof(color));
        height = __min(height, _height);
        for(uint32_t y = height-1; y > 0 ; y--)
            for(uint32_t x = _width;x--;) {
                data[y*_width+x] = data[y*width+x];
            }
        width = _width;
        height = _height;
    }
}

template<typename color>
color drawable<color>::get_pixel(uint32_t x, uint32_t y) {
    return data[y*width+x];
}

template<typename color>
color drawable<color>::get_pixel(uint32_t index) {
    return data[index];
}

template<typename color>
void drawable<color>::set_pixel(uint32_t x, uint32_t y, color p) {
    data[y*width+x] = p;
}

template<typename color>
template<typename ocolor>
void drawable<color>::mix_pixel(uint32_t x, uint32_t y, ocolor p) {
    data[y*width+x] = data[y*width+x]&p;
}

template<typename color>
void drawable<color>::stupid_set_pixel(uint32_t x, uint32_t y, color p) {
    if(x < width && y < height)
        data[y*width+x] = p;
}

template<typename color>
template<typename ocolor>
void drawable<color>::stupid_mix_pixel(uint32_t x, uint32_t y, ocolor p) {
    if(x < width && y < height)
        data[y*width+x] = data[y*width+x]&p;
}

template<typename color>
void drawable<color>::tor_set_pixel(int32_t x, int32_t y, color p) {
    data[(y >= 0 ? y%height : height + y%height)*width+(x >= 0 ? x%width : width + x%width)] = p;
}

template<typename color>
template<typename ocolor>
void drawable<color>::tor_mix_pixel(uint32_t x, uint32_t y, ocolor p) {
    uint32_t ind = (y >= 0 ? y%height : height + y%height)*width+(x >= 0 ? x%width : width + x%width);
    data[ind] = data[ind]&p;
}

template<typename color>
color& drawable<color>::pixel(uint32_t x, uint32_t y) {
    return data[y*width+x];
}

template<typename color>
color& drawable<color>::pixel(uint32_t index) {
    return data[index];
}

template<typename color>
void drawable<color>::finit() {
    if(data)free(data);
    data = 0;
}

#endif//__DRAWABLE_TPP__