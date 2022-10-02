#include <Windows.h>
#include <ctime>

#include "sh_win/handle.h"
#include "sh_win/shwin.h"

handle hd;
shwin wnd;

unsigned long comp_mspf() {
	static unsigned long old_time = clock()-15, new_time = clock(), dt = 15;
	new_time = clock();
	dt += new_time - old_time;
	dt >>= 1;
	old_time = new_time;
	return dt;
}

void rend(shwin* wnd) {
	hd.clear(0xFF00000F);
	for (uint32_t u(64); u--;) {
		hd.circ(rand() % hd.width, rand() % hd.height, 64 + rand() % 64, 0xFF000000 + 0x00FFFF00 & (rand()));
		hd.rect(rand() % hd.width, rand() % hd.height, 64 + rand() % 64, 64 + rand() % 64, 0xFF000000 + 0x00FFFF00 & (rand()));
		uint32_t x = rand() % hd.width;
		uint32_t y = rand() % hd.height;
		hd.rect2p(x, y, x + rand() % 128, y + rand() % 128, 0xFF000000 + 0x00FFFF00 & (rand()));
		hd.ring(rand() % hd.width, rand() % hd.height, 64 + rand() % 64, 0xFF000000 + 0x00FFFF00 & (rand()));
		hd.line(hd.width >> 1, hd.height >> 1, (rand() % hd.width) - (hd.width >> 1), (rand() % hd.height) - (hd.height >> 1), 0xFF000000 + 0x00FFFF00 & rand());
		hd.line2p(hd.width >> 1, hd.height >> 1, (rand() % hd.width), (rand() % hd.height), 0xFF000000 + 0x00FFFF00 & rand());
	}
	StretchDIBits(wnd->hdc, 0, 0, wnd->width, wnd->height, 0, 0, hd.width, hd.height, hd.handle, &wnd->buf_info, DIB_RGB_COLORS, SRCCOPY);

	uint32_t dt = comp_mspf();
	std::wstring s = L" ms to frame: " + std::to_wstring(dt) + L" mspf, speed: " + std::to_wstring(1000.0f/dt) + L" fps ";
	TextOut(wnd->hdc, 0, 0, s.c_str(), s.length());
}

int WinMain(HINSTANCE hinst, HINSTANCE prev_hinst, LPSTR cmd_line, int show_cmd) {

	hd.init(3*480, 3*320);
	wnd.init(hinst, L"Graphics test", rend, 3*480, 3*320);
	wnd.init_draw_area(hd.width, hd.height);
	wnd.show_window(show_cmd);

	MSG msg;
	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		RedrawWindow(wnd.win, NULL, NULL, RDW_INTERNALPAINT);
	} while (msg.message != WM_QUIT);

	return msg.wParam;
}