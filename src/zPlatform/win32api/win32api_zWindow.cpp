#include "ZephyrUI/zPlatform/win32api/win32api_zWindow.h"

using namespace zUI;
using namespace zPlatform;
using namespace Win32API;

Win32API_Window::Win32API_Window(const std::string& title, zUI::zCore::zEnumerations::zWindowPos windowPos, int width, int height)
{
    _hInstance = GetModuleHandle(nullptr);

    // Register WindowClass
    WNDCLASSW WindowClass = {0};
    WindowClass.lpfnWndProc = Win32API_Window::WindowProc;
    WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WindowClass.hInstance = _hInstance;
    WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    WindowClass.lpszClassName = L"zWindow_Win32API";
    RegisterClassW(&WindowClass);

    // Calculate zWindowPos
    RECT screenSpace;
    GetClientRect(GetDesktopWindow(), &screenSpace);

    int screenWidth, screenHeight;
    screenWidth = screenSpace.right;
    screenHeight = screenSpace.bottom;

    int posX, posY;
    switch(windowPos)
    {
        case zUI::zCore::zEnumerations::SCREEN_TOP:
            posX = (screenWidth - width) / 2;
            break;
        case zUI::zCore::zEnumerations::SCREEN_BOTTOM:
            posX = (screenWidth - width) / 2;
            posY = screenHeight - height;
            break;
        case zUI::zCore::zEnumerations::SCREEN_LEFT:
            posY = (screenHeight - height) / 2;
            break;
        case zUI::zCore::zEnumerations::SCREEN_RIGHT:
            posX = screenWidth - width;
            posY = (screenHeight - height) / 2;
        case zUI::zCore::zEnumerations::SCREEN_TOP_LEFT:
            break;
        case zUI::zCore::zEnumerations::SCREEN_TOP_RIGHT:
            posX = screenWidth - width;
            break;
        case zUI::zCore::zEnumerations::SCREEN_BOTTOM_LEFT:
            posY = screenHeight - height;
            break;
        case zUI::zCore::zEnumerations::SCREEN_BOTTOM_RIGHT:
            posX = screenWidth - width;
            posY = screenHeight - height;
            break;
        case zUI::zCore::zEnumerations::SCREEN_CENTER:
            posX = (screenWidth - width) / 2;
            posY = (screenHeight - height) / 2;
            break;

        default:
            break;
    }

    // Convert the ApplicationTitle from string to wstring
    std::wstring ApplicationTitle;

    if(title.empty()) 
    {
        ApplicationTitle = L"";
    }else 
    {
        int wstring_length = MultiByteToWideChar(CP_UTF8, 0, title.c_str(), title.length(), NULL, 0);
        std::wstring t_wideStringTo(wstring_length, L' ');
        MultiByteToWideChar(CP_UTF8, 0, title.c_str(), title.length(), &t_wideStringTo[0], wstring_length);

        ApplicationTitle = t_wideStringTo;
    }

    // Create Window
    _hwnd = CreateWindowW(
        L"zWindow_Win32API",
        ApplicationTitle.c_str(),
        WS_OVERLAPPEDWINDOW,
        posX,
        posY,
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
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
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
        case WM_SIZE: 
        {
            HWND hChild = GetWindow(hwnd, GW_CHILD);
            while (hChild) 
            {
                SendMessage(hChild, WM_SIZE, wParam, lParam);
                hChild = GetNextWindow(hChild, GW_HWNDNEXT);
            }
            
            return 0;
        }

        default:
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
}