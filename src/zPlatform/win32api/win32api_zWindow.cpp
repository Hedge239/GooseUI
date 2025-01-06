#include "ZephyrUI/zPlatform/win32api/win32api_zWindow.h"

using namespace zUI;
using namespace zPlatform;
using namespace Win32API;

Win32API_Window::Win32API_Window(const std::string& title, int width, int height)
{
    _hInstance = GetModuleHandle(nullptr);

    // RegisterWindowClass
    WNDCLASSW WindowClass = {0};
    WindowClass.lpfnWndProc = Win32API_Window::WindowProc;
    WindowClass.hInstance = _hInstance;
    WindowClass.lpszClassName = L"zWindow_Win32API";
    RegisterClassW(&WindowClass);

    _hwnd = CreateWindowW(
        L"zWindow_Win32API",
        (LPCWSTR)title.c_str(),
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        width,
        height,
        NULL,
        NULL,
        _hInstance,
        this
    );
}

Win32API_Window::~Win32API_Window() {if(_hwnd){DestroyWindow(_hwnd);}}


// Window Settings
void Win32API_Window::setTitle(const std::string& title) {}
void Win32API_Window::setSize(int width, int height) {}

// Returns
HWND Win32API_Window::getHwnd() {return _hwnd;}
int Win32API_Window::getPosX() {return 0;}
int Win32API_Window::getPosY() {return 0;}
int Win32API_Window::getWidth() {return 0;}
int Win32API_Window::getHeight() {return 0;}

// Window Management
void Win32API_Window::show() 
{
    ShowWindow(_hwnd, SW_SHOW); 
    UpdateWindow(_hwnd);
}

void Win32API_Window::hide() {}
void Win32API_Window::destroy() {}
void Win32API_Window::draw() {}

void Win32API_Window::HandelEvents()
{
    MSG msg;
    //while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        //TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK Win32API_Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
        {
            PostQuitMessage(0);
            return 0;
        }
        default:
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
}