#include <Windows.h>
#include <ctime>

#include "sh_win/handle.h"
#include "sh_win/shwin.h"

handle hd;
shwin wnd;

float comp_fps() {
	static clock_t old_time = 0, new_time, dt;
	new_time = clock();
	dt = new_time - old_time;
	old_time = new_time;
	return CLOCKS_PER_SEC * 1.0f / dt;
}

void rend(shwin* wnd) {
	hd.ring(rand()%hd.width, rand()%hd.height, rand()%64, 0xFF000000+0x00FFFF00&(rand()));
	hd.line(hd.width * 0.5f, hd.height * 0.5f, rand() % hd.width - hd.width * 0.5f, rand() % hd.height - hd.height * 0.5f, 0xFF000000 + 0x00FFFF00 & rand());

	StretchDIBits(wnd->hdc, 0, 0, wnd->width, wnd->height, 0, 0, hd.width, hd.height, hd.handle, &wnd->buf_info, DIB_RGB_COLORS, SRCCOPY);

	std::wstring s = L"Speed: " + std::to_wstring(comp_fps()) + L" fps";
	TextOut(wnd->hdc, 0, 0, s.c_str(), s.length());
}

int WinMain(HINSTANCE hinst, HINSTANCE prev_hinst, LPSTR cmd_line, int show_cmd) {

	hd.init(480, 320);
	wnd.init(hinst, L"Graphics test", rend, 480, 320);
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