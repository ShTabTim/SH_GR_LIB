#include "winapi_renderable.hpp"

void winapi_renderable::init(uint32_t _renderable_width, uint32_t _renderable_height, void (*_rend)(meta_renderable*), uint32_t _drawable_width, uint32_t _drawable_height) {
    meta_renderable::init(_renderable_width, _renderable_height, _rend, _drawable_width, _drawable_height);

    buf_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    buf_info.bmiHeader.biPlanes = 1;
    buf_info.bmiHeader.biBitCount = 24;
    buf_info.bmiHeader.biCompression = BI_RGB;
}

void winapi_renderable::set_hdc(HDC _hdc) {
    hdc = _hdc;
}

void winapi_renderable::draw() {
    meta_renderable::draw();
    buf_info.bmiHeader.biWidth = drawable::width;
    buf_info.bmiHeader.biHeight = drawable::height;
    StretchDIBits(hdc, 0, 0, meta_renderable::width, meta_renderable::height, 0, 0, drawable::width, drawable::height, drawable::data, &buf_info, DIB_RGB_COLORS, SRCCOPY);
}

void winapi_renderable::finit() {
    drawable ::finit();
    ReleaseDC(WindowFromDC(hdc), hdc);
}