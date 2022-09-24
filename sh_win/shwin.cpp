#include "shwin.h"

LRESULT CALLBACK win_proc(HWND hwin, UINT uimsg, WPARAM wparam, LPARAM lparam) {
	shwin* wnd = (shwin*)GetWindowLongPtr(hwin, GWLP_USERDATA);
	if (wnd)
		return wnd->msg_proc(hwin, uimsg, wparam, lparam);
	else
		return DefWindowProc(hwin, uimsg, wparam, lparam);
	return 0;
}

void ref(HWND win, uint32_t width, uint32_t height) {
	RECT wRect, cRect;

	GetWindowRect(win, &wRect);
	GetClientRect(win, &cRect);

	wRect.right += width - cRect.right - wRect.left;
	wRect.bottom += height - cRect.bottom - wRect.top;

	MoveWindow(win, wRect.left, wRect.top, wRect.right, wRect.bottom, false);
}

LRESULT CALLBACK shwin::msg_proc(HWND hwin, UINT uimsg, WPARAM wparam, LPARAM lparam) {
	switch (uimsg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		rend(this);
		break;
	default:
		return DefWindowProc(hwin, uimsg, wparam, lparam);
		break;
	}
	return 0;
}

void shwin::init(HINSTANCE hinst, std::wstring name, void (*rend)(shwin*), uint32_t width, uint32_t height) {
	win_name = name;

	this->rend = rend;

	this->width = width;
	this->height = height;

	wc.style = CS_OWNDC;
	wc.lpfnWndProc = win_proc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hinst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = win_name.c_str() + 1;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, L"Register class failed!", L"Oh, no!", MB_ERR_INVALID_CHARS);
		PostQuitMessage(0);
	}

	win = CreateWindow(
		wc.lpszClassName,
		win_name.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL, NULL, hinst, NULL);

	if (!win) {
		MessageBox(NULL, L"hwnd failed!", L"Oh, no!", MB_ERR_INVALID_CHARS);
		PostQuitMessage(0);
	}

	SetWindowLongPtr(win, GWLP_USERDATA, (LONG_PTR)this);

	hdc = GetDC(win);
}

void shwin::init_draw_area(uint32_t width, uint32_t height) {
	buf_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	buf_info.bmiHeader.biPlanes = 1;
	buf_info.bmiHeader.biBitCount = 24;
	buf_info.bmiHeader.biCompression = BI_RGB;
	buf_info.bmiHeader.biWidth = width;
	buf_info.bmiHeader.biHeight = height;
}

void shwin::show_window(int cmd_show) {
	ref(win, width, height);
	ShowWindow(win, cmd_show);
	UpdateWindow(win);
}