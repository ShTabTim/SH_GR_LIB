#include "renderable.hpp"

void renderable::init(uint32_t _width, uint32_t _height, void (*_rend)(renderable*)) {
    drawable::init(480, 320);

    width = _width;
    height = _height;
    rend = _rend;

    buf_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    buf_info.bmiHeader.biPlanes = 1;
    buf_info.bmiHeader.biBitCount = 24;
    buf_info.bmiHeader.biCompression = BI_RGB;
    buf_info.bmiHeader.biWidth = drawable::width;
    buf_info.bmiHeader.biHeight = drawable::height;
}

void renderable::draw() {
    rend(this);
    buf_info.bmiHeader.biWidth = drawable::width;
    buf_info.bmiHeader.biHeight = drawable::height;
    StretchDIBits(hdc, 0, 0, width, height, 0, 0, drawable::width, drawable::height, drawable::data, &buf_info, DIB_RGB_COLORS, SRCCOPY);
}

void renderable::finit() {
    ReleaseDC(WindowFromDC(hdc), hdc);
    drawable ::finit();
}