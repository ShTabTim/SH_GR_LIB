#include <Windows.h>

#include <chrono>
#include <cwchar>

#include <renderables/meta_renderable.hpp>
#include <renderables/winapi_renderable.hpp>
#include <painting/paintives.hpp>
#include <valarray>

LRESULT CALLBACK win_proc(HWND hwin, UINT uimsg, WPARAM wparam, LPARAM lparam) {
    static std::chrono::system_clock::time_point new_time = std::chrono::system_clock::now();
    static std::chrono::system_clock::time_point old_time = new_time;
    meta_renderable* pRenderable = (meta_renderable*)GetWindowLongPtr(hwin, GWLP_USERDATA);
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
            pRenderable->meta_renderable::width = LOWORD(lparam);
            pRenderable->meta_renderable::height = HIWORD(lparam);
            break;
        default:
            return DefWindowProcW(hwin, uimsg, wparam, lparam);
    }
    return 0;
}

uint8_t4 simple_picture[] = {
        {0xFF, 0xFF, 0xFF, 0x00},{0xFF, 0xFF, 0xFF, 0x00},{0x0F, 0x0F, 0x0F, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},{0xFF, 0xFF, 0xFF, 0x00},{0xFF, 0xFF, 0xFF, 0x00},
        {0xFF, 0xFF, 0xFF, 0x00},{0x0F, 0x0F, 0x0F, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},{0xFF, 0xFF, 0xFF, 0x00},
        {0x0F, 0x0F, 0x0F, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0x00, 0x00, 0x8F},{0x00, 0x00, 0x00, 0x8F},{0x00, 0x00, 0x00, 0x8F},{0x00, 0xFF, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},
        {0x0F, 0x0F, 0x0F, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},
        {0x0F, 0x0F, 0x0F, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF},{0x00, 0x00, 0x00, 0x8F},{0x00, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF},{0x00, 0x00, 0x00, 0x8F},{0x0F, 0x0F, 0x0F, 0xFF},
        {0x0F, 0x0F, 0x0F, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},
        {0xFF, 0xFF, 0xFF, 0x00},{0x0F, 0x0F, 0x0F, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x00, 0xFF, 0xFF, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},{0xFF, 0xFF, 0xFF, 0x00},
        {0xFF, 0xFF, 0xFF, 0x00},{0xFF, 0xFF, 0xFF, 0x00},{0x0F, 0x0F, 0x0F, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},{0x0F, 0x0F, 0x0F, 0xFF},{0xFF, 0xFF, 0xFF, 0x00},{0xFF, 0xFF, 0xFF, 0x00},
};

drawable4 spt(simple_picture, 8, 8);

void rend(meta_renderable* rd) {
    paintives::clear(rd, (uint8_t3){0xFF, 0x0F, 0x0F});
    paintives::sprite(rd, &spt, 20, 20, rd->drawable::width-21, rd->drawable::height-21);

    for (uint32_t u(10); u--;) {
        paintives::rect(rd, (rand() % rd->drawable::width), (rand() % rd->drawable::height), (rand() % rd->drawable::width), (rand() % rd->drawable::height), (uint8_t3){(uint8_t)rand(), (uint8_t)rand(), (uint8_t)rand()});
        paintives::line(rd, (rand() % rd->drawable::width), (rand() % rd->drawable::height), (rand() % rd->drawable::width), (rand() % rd->drawable::height), (uint8_t3){(uint8_t)rand(), (uint8_t)rand(), (uint8_t)rand()});
        rd->set_pixel(rand()%rd->drawable::width, rand()%rd->drawable::height, (uint8_t3){(uint8_t)rand(), (uint8_t)rand(), (uint8_t)rand()});
        paintives::circ(rd, rd->drawable::width>>1, rd->drawable::height>>1, rand()%((rd->drawable::height+rd->drawable::width)>>1), (uint8_t3){0xFF, (uint8_t)rand(), 0xAA});
    }

    //for(uint32_t p(40);p--;)
    //    paintives::sprite(rd, &spt, (rand() % rd->drawable::width), (rand() % rd->drawable::height), (rand() % rd->drawable::width), (rand() % rd->drawable::height));
    static float t = 0;
    t += 0.02f;
    paintives::sprite(rd, &spt, 40 + 60*sin(2*t), 30 + 60*sin(1+2*t), 320+50*sin(t), 320+50*cos(t));
}

int WinMain(HINSTANCE hinst, HINSTANCE prev_hinst, LPSTR cmd_line, int show_cmd) {
    winapi_renderable r;

    r.init(512, 512, rend, 512, 512);

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
            r.meta_renderable::width, r.meta_renderable::height,
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