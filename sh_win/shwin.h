#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>

 typedef struct shwin {
	std::wstring win_name;
	HWND win;
	WNDCLASS wc;
	HDC hdc;
	BITMAPINFO buf_info;
	uint32_t width, height;
	void (*rend)(shwin*);

	LRESULT CALLBACK msg_proc(HWND hwin, UINT uimsg, WPARAM wparam, LPARAM lparam);
	void init(HINSTANCE hinst, std::wstring name, void (*rend)(shwin*), uint32_t width, uint32_t height);
	void init_draw_area(uint32_t width, uint32_t height);
	void show_window(int cmd_show);
} shwin;