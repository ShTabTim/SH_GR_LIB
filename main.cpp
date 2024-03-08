#include <Windows.h>

#include <renderable.hpp>
#include <chrono>
#include <cwchar>
#include <valarray>
#include "painting/paintives.hpp"

LRESULT CALLBACK win_proc(HWND hwin, UINT uimsg, WPARAM wparam, LPARAM lparam) {
    static std::chrono::system_clock::time_point new_time = std::chrono::system_clock::now();
    static std::chrono::system_clock::time_point old_time = new_time;
    renderable* pRenderable = (renderable*)GetWindowLongPtr(hwin, GWLP_USERDATA);
    switch (uimsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_PAINT: {
            new_time = std::chrono::system_clock::now();
            double dt = std::chrono::duration_cast<std::chrono::nanoseconds>(new_time - old_time).count()*0.000000001;
            old_time = new_time;
            pRenderable->draw();

            LPWSTR s = (LPWSTR) malloc(30 * sizeof(wchar_t));
            swprintf_s(s, 64, L"%4.2f fps\0", 1.0/dt);

            SetWindowTextW(hwin, s);
            free(s);
        }   break;
        case WM_SIZE:
            pRenderable->width = LOWORD(lparam);
            pRenderable->height = HIWORD(lparam);
            break;
        default:
            return DefWindowProcW(hwin, uimsg, wparam, lparam);
    }
    return 0;
}

uint8_t3 simple_picture[] = {
        {0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F},{0x0F, 0x0F, 0x0F},{0x0F, 0x0F, 0x0F},{0x0F, 0x0F, 0x0F},{0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F},{0xFF, 0xFF, 0xFF},
        {0x0F, 0x0F, 0x0F},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0x00, 0x00},{0x00, 0x00, 0x00},{0x00, 0x00, 0x00},{0x00, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F},
        {0x0F, 0x0F, 0x0F},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F},
        {0x0F, 0x0F, 0x0F},{0x00, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF},{0x00, 0x00, 0x00},{0x00, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF},{0x00, 0x00, 0x00},{0x0F, 0x0F, 0x0F},
        {0x0F, 0x0F, 0x0F},{0x00, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F},
        {0xFF, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F},{0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F},{0x0F, 0x0F, 0x0F},{0x0F, 0x0F, 0x0F},{0x0F, 0x0F, 0x0F},{0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF},
};

drawable spt(simple_picture, 8, 8);

void rend(renderable* rd) {
    paintives::sprite(rd, &spt, 0, 0, rd->drawable::width-1, rd->drawable::height-1);

    for (uint32_t u(10); u--;) {
        paintives::rect(rd, (rand() % rd->drawable::width), (rand() % rd->drawable::height), (rand() % rd->drawable::width), (rand() % rd->drawable::height), {(uint8_t)rand(), (uint8_t)rand(), (uint8_t)rand()});
        paintives::line(rd, (rand() % rd->drawable::width), (rand() % rd->drawable::height), (rand() % rd->drawable::width), (rand() % rd->drawable::height), {(uint8_t)rand(), (uint8_t)rand(), (uint8_t)rand()});
        rd->set_pixel(rand()%rd->drawable::width, rand()%rd->drawable::height, rand());
        paintives::circ(rd, 70, 70, rand()%100, {0xFF, (uint8_t)rand(), 0xAA});
    }

    paintives::sprite(rd, &spt, 80, 80, 87, 94);
}

int WinMain(HINSTANCE hinst, HINSTANCE prev_hinst, LPSTR cmd_line, int show_cmd) {
    renderable r;

    r.init(512, 512, rend, 128, 128);

    WNDCLASSEXW wcexw;
    ZeroMemory(&wcexw, sizeof(WNDCLASSEXW));

    wcexw.cbSize = sizeof(WNDCLASSEXW);
    wcexw.style = CS_OWNDC;
    wcexw.lpfnWndProc = win_proc;
    wcexw.hInstance = hinst;
    wcexw.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcexw.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcexw.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcexw.lpszClassName = L"GraphicWindowClass";
    wcexw.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


    if (!RegisterClassExW(&wcexw)) {
        MessageBoxW(NULL, L"Register class failed!", L"Oh, no!", MB_ERR_INVALID_CHARS);
        PostQuitMessage(0);
    }

    HWND win = CreateWindowExW(0,
            wcexw.lpszClassName,
            L"GraphicWindow",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            r.width, r.height,
            NULL, NULL, hinst, NULL);

    if (!win) {
        MessageBoxW(NULL, L"hwnd failed!", L"Oh, no!", MB_ERR_INVALID_CHARS);
        PostQuitMessage(0);
    }

    SetWindowLongPtr(win, GWLP_USERDATA, (LONG_PTR)&r);

    r.hdc = GetDC(win);

    RECT wRect, cRect;

    GetWindowRect(win, &wRect);
    GetClientRect(win, &cRect);

    wRect.right = wRect.right - wRect.left + r.width - cRect.right;
    wRect.bottom = wRect.bottom - wRect.top + r.height - cRect.bottom;

    MoveWindow(win, wRect.left, wRect.top, wRect.right, wRect.bottom, false);
    ShowWindow(win, show_cmd);

	MSG msg;
	do {
		if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		RedrawWindow(win, NULL, NULL, RDW_INTERNALPAINT);
	} while (msg.message != WM_QUIT);

    r.finit();

	return msg.wParam;
}