#include "GooseUI/platform/win32/widgets/win32_window.h"


namespace goose::platform::gWin32 // INTERNAL
{
    LRESULT CALLBACK gWin32_window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
}

namespace goose::platform::gWin32 // EXTERNAL
{
    gWin32_window::gWin32_window(const std::string& title, goose::core::enumerations::windowPos posistion, int width, int height)
    {
        _hInstance = GetModuleHandle(nullptr);

        // Register WindowClass
        WNDCLASSW WindowClass = {0};
        WindowClass.lpfnWndProc = gWin32_window::WindowProc;
        WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        WindowClass.hInstance = _hInstance;
        WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        WindowClass.lpszClassName = L"GooseUI_Window";
        RegisterClassW(&WindowClass);

        // Calculate posistion
        RECT screenSpace;
        GetClientRect(GetDesktopWindow(), &screenSpace);

        int posX, posY;
        int screenWidth, screenHeight;
        screenWidth = screenSpace.right;
        screenHeight = screenSpace.bottom;

        switch(posistion)
        {
            case goose::core::enumerations::SCREEN_TOP:
                posX = (screenWidth - width) / 2;
                break;
            case goose::core::enumerations::SCREEN_BOTTOM:
                posX = (screenWidth - width) / 2;
                posY = screenHeight - height;
                break;
            case goose::core::enumerations::SCREEN_LEFT:
                posY = (screenHeight - height) / 2;
                break;
            case goose::core::enumerations::SCREEN_RIGHT:
                posX = screenWidth - width;
                posY = (screenHeight - height) / 2;
                break;
            case goose::core::enumerations::SCREEN_TOP_LEFT:
                break;
            case goose::core::enumerations::SCREEN_TOP_RIGHT:
                posX = screenWidth - width;
                break;
            case goose::core::enumerations::SCREEN_BOTTOM_LEFT:
                posY = screenHeight - height;
                break;
            case goose::core::enumerations::SCREEN_BOTTOM_RIGHT:
                posX = screenWidth - width;
                posY = screenHeight - height;
                break;
            case goose::core::enumerations::SCREEN_CENTER:
                posX = (screenWidth - width) / 2;
                posY = (screenHeight - height) / 2;
                break;

            default:
                break;
        }

        // Convert title to wString
        std::wstring windowTitle;
        if(title.empty())
        {
            windowTitle = L"";
        }else 
        {
            int wstring_length = MultiByteToWideChar(CP_UTF8, 0, title.c_str(), title.length(), NULL, 0);
            std::wstring t_wideStringTo(wstring_length, L' ');
            MultiByteToWideChar(CP_UTF8, 0, title.c_str(), title.length(), &t_wideStringTo[0], wstring_length);

            windowTitle = t_wideStringTo;
        }

        // Create Window
        _hwnd = CreateWindowW(
            L"GooseUI_Window",
            windowTitle.c_str(),
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

    gWin32_window::~gWin32_window() { if(_hwnd){ DestroyWindow(_hwnd); } }

    // WINDOW SETTINGS - Requires full window redraws
    void gWin32_window::setHeader(const std::string& title, bool isVisible, bool hasButtons, bool hasMinimize, bool hasMaximise)
    {
        if(!title.empty()) { SetWindowTextA(_hwnd, title.c_str()); }

        LONG_PTR WindowStyle = GetWindowLongPtr(_hwnd, GWL_STYLE);
        if(isVisible) { WindowStyle |= WS_CAPTION; } else { WindowStyle &= ~WS_CAPTION; }
        if(hasButtons) { WindowStyle |= WS_SYSMENU; } else { WindowStyle &= ~WS_SYSMENU; }
        if(hasMinimize) { WindowStyle |= WS_MINIMIZEBOX; } else { WindowStyle &= ~WS_MINIMIZEBOX; }
        if(hasMaximise) { WindowStyle |= WS_MAXIMIZEBOX; } else { WindowStyle &= ~WS_MAXIMIZEBOX; }

        SetWindowLongPtr(_hwnd, GWL_STYLE, WindowStyle);
        SetWindowPos(_hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }

    void gWin32_window::setSize(int width, int height)
    {
        RECT currentRect;
        RECT rect =  {0, 0, width, height};

        bool hasMenu = GetMenu(_hwnd) != nullptr;
        DWORD WindowStyle = GetWindowLong(_hwnd, GWL_STYLE);
        
        AdjustWindowRect(&rect, WindowStyle, hasMenu);
        GetWindowRect(_hwnd, &currentRect);

        SetWindowPos(_hwnd, nullptr, currentRect.left, currentRect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOACTIVATE);
    }

    void gWin32_window::isResizeable(bool isResizeable)
    {
        // Disables Maximise button while at it, might change later
        LONG_PTR WindowStyle = GetWindowLongPtr(_hwnd, GWL_STYLE);
        if(isResizeable) { WindowStyle |= WS_THICKFRAME; WindowStyle |= WS_MAXIMIZEBOX; } else { WindowStyle &= ~WS_THICKFRAME; WindowStyle &= ~WS_MAXIMIZEBOX; }
        
        SetWindowLongPtr(_hwnd, GWL_STYLE, WindowStyle);
        SetWindowPos(_hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }

    void gWin32_window::isAllwaysOnTop(bool isOnTop)
    {
        if(isOnTop) { SetWindowPos(_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE); } 
        else { SetWindowPos(_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE); }
    }

    // WINDOW MANAGEMENT
    void gWin32_window::maximize() { ShowWindow(_hwnd, SW_MAXIMIZE); UpdateWindow(_hwnd);}
    void gWin32_window::minimize() { ShowWindow(_hwnd, SW_MINIMIZE); UpdateWindow(_hwnd);}
    void gWin32_window::restoreSize() { ShowWindow(_hwnd, SW_RESTORE); UpdateWindow(_hwnd);}

    void gWin32_window::show() { ShowWindow(_hwnd, SW_SHOW); UpdateWindow(_hwnd); }
    void gWin32_window::hide() { ShowWindow(_hwnd, SW_HIDE); UpdateWindow(_hwnd); }

    void gWin32_window::destroy() { DestroyWindow(_hwnd); }

    void gWin32_window::handelEvents()
    {
        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // RETURNS
    HWND gWin32_window::getHwnd() {return _hwnd;}

    int gWin32_window::getWidth() { RECT rect; GetWindowRect(_hwnd, &rect); return rect.right - rect.left; }
    int gWin32_window::getHeight() { RECT rect; GetWindowRect(_hwnd, &rect); return rect.bottom - rect.top; }
}