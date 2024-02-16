#include "ZephyrUI/lib/Win32/w32_window.h"
#include "ZephyrUI/zWindow.h"

#include <string>
#include <windows.h>

std::string g_ClassName;


void killWindow(bool byUser, HWND hwnd)
{
    if(byUser)
    {
        // Tell the WindowManager to remove it from exisiting windows
        zephyr::WindowManager::RemoveWindowFromMap(g_ClassName);
    }

    DestroyWindow(hwnd);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
        {
            killWindow(true, hwnd);
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }

        default:
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

namespace zephyr
{
    namespace lib
    {
        HWND hwnd;

        void w32_CreateWindow(zephyr::zWindowConfig wcfg)
        {
            g_ClassName = wcfg.className;

            // Convert strings to wide strings
            std::wstring WclassName(wcfg.className.begin(), wcfg.className.end());
            std::wstring WdisplayTitle(wcfg.displayTitle.begin(), wcfg.displayTitle.end());

            WclassName.push_back(L'\0');
            WdisplayTitle.push_back(L'\0');

            // Define WindowClass
            WNDCLASSW WindowClass = {0};
            WindowClass.lpfnWndProc = WindowProcedure;
            WindowClass.hInstance = GetModuleHandle(NULL);
            WindowClass.lpszClassName = WclassName.c_str();
            RegisterClassW(&WindowClass);

            // Define the window
            DWORD WindowStyle = WS_OVERLAPPEDWINDOW;

            if(wcfg.disableResize)
            {
                WindowStyle &= ~WS_THICKFRAME;
                WindowStyle &= ~WS_MAXIMIZEBOX;
            }

            if(wcfg.disableMinimizeToggle)
                WindowStyle &= ~WS_MINIMIZEBOX;
            if(wcfg.disableToolBar)
                WindowStyle &= ~WS_SYSMENU;

            // Display Window
            hwnd = CreateWindowW(WclassName.c_str(), WdisplayTitle.c_str(), WindowStyle, 0, 0, wcfg.displayWidth, wcfg.displayHeight, NULL, NULL, GetModuleHandle(NULL), NULL);

            ShowWindow(hwnd, SW_SHOWDEFAULT);
            UpdateWindow(hwnd);

            MSG wMsg;
            while(GetMessage(&wMsg, NULL, 0, 0))
            {
                TranslateMessage(&wMsg);
                DispatchMessage(&wMsg);
            }
        }

        void w32_CloseWindow()
        {
            killWindow(false, hwnd);
        }
    }
}