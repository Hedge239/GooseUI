#include "GooseUI/platform/win32/win32_window.h"

#include "GooseUI/context.h"

#include <algorithm>


namespace GooseUI::platform // Private
{
    LRESULT CALLBACK win32_window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        win32_window* self = reinterpret_cast<win32_window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        
        switch(uMsg)
        {
            case WM_CLOSE:
            {
                PostQuitMessage(0);
                return 0;
            }

            case WM_SIZING:
            {
                if(self) { self->renderWidgets(); }
                return 0;
            }

            default:
                return DefWindowProcW(hwnd, uMsg, wParam, lParam);
        }
    }
    
    void win32_window::_startRenderFrame()
    {
        switch (application::getBackendType()) 
        {
            #if GOOSEUI_HAS_OPENGL
            case application::backendType::OpenGL:
            {
                graphics::gl::glRenderer* glBackend = static_cast<graphics::gl::glRenderer*>(application::getRenderer());
                wglMakeCurrent(GetDC(this->getHwnd()), glBackend->getContext().hglrc);
                break;
            }
            #endif
            
            #if GOOSEUI_ENABLE_VULKAN
            #endif
            
            default:
                printf("GooseUI: Backend Not Initilized! \n");
                break;
        }
        
        RECT rect; GetClientRect(_hwnd, &rect);
        application::getRenderer()->beginFrame(rect.right - rect.left, rect.bottom - rect.top, _bgColor);
    }
    
    void win32_window::_endRenderFrame()
    {
        application::getRenderer()->endFrame();
        
        switch (application::getBackendType()) 
        {
            #if GOOSEUI_HAS_OPENGL
            case application::backendType::OpenGL:
            {
                graphics::gl::glRenderer* glBackend = static_cast<graphics::gl::glRenderer*>(application::getRenderer());
                SwapBuffers(GetDC(this->getHwnd()));
                break;
            }
            #endif
            
            #if GOOSEUI_ENABLE_VULKAN
            #endif
            
            default:
                printf("GooseUI: Backend Not Initilized! \n");
                break;
        }
    }
    
    // Graphic Dependent
    #if GOOSEUI_HAS_OPENGL
    void win32_window::_gl_createContext()
    {
        HDC hdc = GetDC(this->getHwnd());

        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion   = 1;
        pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int pf = ChoosePixelFormat(hdc, &pfd);
        if(pf == 0 || !SetPixelFormat(hdc, pf, &pfd)) { printf("GooseUI: Failed to set pixel format \n"); }

        HGLRC hglrc = wglCreateContext(hdc);
        if(!hglrc || !wglMakeCurrent(hdc, hglrc)) { printf("GooseUI: Failed to create WGL Context \n"); }
    }

    void win32_window::_gl_shareContext()
    {
        HDC hdc = GetDC(this->getHwnd());
        HGLRC hglrc = wglGetCurrentContext();
        graphics::gl::glRenderer* glBackend = static_cast<graphics::gl::glRenderer*>(application::getRenderer());
        
        if(!glBackend->hasContext())
        {
            glBackend->setContext(new graphics::gl::glContext{hglrc, hdc});
        }else 
        {
            wglShareLists(glBackend->getContext().hglrc, hglrc);
        }
    }

    void win32_window::_gl_destoryContext()
    {
        HDC hdc = GetDC(this->getHwnd());
        HGLRC hglrc = wglGetCurrentContext();

        if(hglrc)
        {
            wglMakeCurrent(hdc, nullptr);
            wglDeleteContext(hglrc);
        }

        ReleaseDC(this->getHwnd(), hdc);
    }
    #endif

    #if GOOSEUI_HAS_VULKAN
    #endif
}

namespace GooseUI::platform // Public
{
    win32_window::win32_window(const std::string& title, int width, int height, screenPosistion posistion)
    {
        _hInstance = GetModuleHandle(nullptr);

        // Register Window Class
        WNDCLASSW WindowClass = {0};
        WindowClass.lpfnWndProc = win32_window::WindowProc;
        WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        WindowClass.hInstance = _hInstance;
        WindowClass.lpszClassName = L"GooseUI_Window";
        WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        RegisterClassW(&WindowClass);

        // Calculate Screen Posistion
        RECT screenSpace;
        GetClientRect(GetDesktopWindow(), &screenSpace);

        int posX, posY;
        int screenWidth, screenHeight;
        screenWidth = screenSpace.right;
        screenHeight = screenSpace.bottom;

        switch(posistion)
        {
            case SCREEN_TOP:
                posX = (screenWidth - width) / 2;
                break;
            case SCREEN_BOTTOM:
                posX = (screenWidth - width) / 2;
                posY = screenHeight - height;
                break;
            case SCREEN_LEFT:
                posY = (screenHeight - height) / 2;
                break;
            case SCREEN_RIGHT:
                posX = screenWidth - width;
                posY = (screenHeight - height) / 2;
                break;
            case SCREEN_TOP_LEFT:
                break;
            case SCREEN_TOP_RIGHT:
                posX = screenWidth - width;
                break;
            case SCREEN_BOTTOM_LEFT:
                posY = screenHeight - height;
                break;
            case SCREEN_BOTTOM_RIGHT:
                posX = screenWidth - width;
                posY = screenHeight - height;
                break;
            case SCREEN_CENTER:
                posX = (screenWidth - width) / 2;
                posY = (screenHeight - height) / 2;
                break;

            default:
                break;
        }

        // Convert Title to WideString
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

        // Create window
        _hwnd = CreateWindowExW(
            WS_EX_OVERLAPPEDWINDOW,
            L"GooseUI_Window",
            windowTitle.c_str(),
            CW_USEDEFAULT,
            posX,
            posY,
            width,
            height,
            NULL,
            NULL,
            _hInstance,
            NULL
        );

        if(!_hwnd) { printf("GooseUI: Failed to create Win32 Window \n"); }
        SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        
        // Init Backend
        _bgColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        
        switch (application::getBackendType()) 
        {
            #if GOOSEUI_HAS_OPENGL
            case application::backendType::OpenGL:
                _gl_createContext();
                application::getRenderer()->initRenderer();
                _gl_shareContext();
                break;
            #endif
            
            #if GOOSEUI_ENABLE_VULKAN
            #endif
            
            default:
                printf("GooseUI: Backend Not Initilized! \n");
                break;
        }

        _isRunning = true;
    }
    
    win32_window::~win32_window()
    {
        _isRunning = false;
        
        switch (application::getBackendType()) 
        {
            #if GOOSEUI_HAS_OPENGL
            case application::backendType::OpenGL:
                _gl_destoryContext();
                break;
            #endif
            
            #if GOOSEUI_ENABLE_VULKAN
            #endif
            
            default:
                printf("GooseUI: Backend Not Initilized! \n");
                break;
        }
        
        if(_hwnd) { DestroyWindow(_hwnd); }
    }
    
    HWND win32_window::getHwnd() { return _hwnd; }
    
    // OVERIDES
    // Window Configuration
    void win32_window::setWindowIcon(const std::string& ICO) 
    {
        // TODO
    };
    
    void win32_window::setHeader(const std::string& title, bool isVisible, bool hasButtons, bool hasMinimize, bool hasMaximise)
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
    
    void win32_window::isResizeable(bool isResizeable)
    {
        // Disables Maximise button while at it, might change later
        LONG_PTR WindowStyle = GetWindowLongPtr(_hwnd, GWL_STYLE);
        if(isResizeable) { WindowStyle |= WS_THICKFRAME; WindowStyle |= WS_MAXIMIZEBOX; } else { WindowStyle &= ~WS_THICKFRAME; WindowStyle &= ~WS_MAXIMIZEBOX; }
        
        SetWindowLongPtr(_hwnd, GWL_STYLE, WindowStyle);
        SetWindowPos(_hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
    
    void win32_window::isAllwaysOnTop(bool isOnTop)
    {
        if(isOnTop) { SetWindowPos(_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE); } 
        else { SetWindowPos(_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE); }
    }
    
    void win32_window::setSize(int width, int height)
    {
        RECT currentRect;
        RECT rect =  {0, 0, width, height};

        bool hasMenu = GetMenu(_hwnd) != nullptr;
        DWORD WindowStyle = GetWindowLong(_hwnd, GWL_STYLE);
        
        AdjustWindowRect(&rect, WindowStyle, hasMenu);
        GetWindowRect(_hwnd, &currentRect);

        SetWindowPos(_hwnd, nullptr, currentRect.left, currentRect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOACTIVATE);
    }
    
    void win32_window::maximize() { ShowWindow(_hwnd, SW_MAXIMIZE); UpdateWindow(_hwnd);}
    void win32_window::minimize() { ShowWindow(_hwnd, SW_MINIMIZE); UpdateWindow(_hwnd);}
    void win32_window::restoreSize() { ShowWindow(_hwnd, SW_RESTORE); UpdateWindow(_hwnd);}
    
    // Window Visibility
    void win32_window::show() { ShowWindow(_hwnd, SW_SHOW); UpdateWindow(_hwnd); }
    void win32_window::hide() { ShowWindow(_hwnd, SW_HIDE); UpdateWindow(_hwnd); }
    void win32_window::destroy() { DestroyWindow(_hwnd); }
    
    // Widget Management
    void win32_window::addWidgetToVector(absractions::iWidget* widget) { _widgets.push_back(widget); }
    void win32_window::removeWidgetFromVector(absractions::iWidget* widget)
    {
        std::vector<absractions::iWidget*>::iterator target = std::find(_widgets.begin(), _widgets.end(), widget);
        if(target != _widgets.end()){ _widgets.erase(target); }
    }
    
    void win32_window::renderWidgets()
    {
        if(!application::getRenderer()) return;
        _startRenderFrame();
        
        for(absractions::iWidget* widget : _widgets)
        {
            if(widget)
            {
                widget->draw(); // Huh, guess we dont need ot pass it since it now centralized
            }
        }
        
        _endRenderFrame();
    }
    
    void win32_window::handelEvents()
    {
        MSG msg;
        while(PeekMessage(&msg, getHwnd(), 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            // Set evtData & run event loop
            bool handelWidgets = true;

            event::data evtData;
            evtData.mouseX = ((int)(short)LOWORD(msg.lParam));
            evtData.mouseY = ((int)(short)HIWORD(msg.lParam));

            switch(msg.message)
            {
                case WM_QUIT: { _isRunning = false; handelWidgets = false; break; }
                
                case WM_LBUTTONDOWN: { evtData.type = event::type::leftMouseDown; break; }
                case WM_LBUTTONUP: { evtData.type = event::type::leftMouseUp; break; }
                case WM_RBUTTONDOWN: { evtData.type = event::type::rightMouseDown; break; }

                default: { handelWidgets = false; break; }
            }

            if(handelWidgets)
            {
                for(absractions::iWidget* widget : _widgets)
                {
                    if(widget)
                    {
                        widget->pollEvent(evtData);
                    }
                }
            }

            renderWidgets();
        }
    }
    
    // Returns
    displayService win32_window::getDisplayService() const { return displayService::win32; }
    int win32_window::getWidth() { RECT rect; GetWindowRect(_hwnd, &rect); return rect.right - rect.left; }
    int win32_window::getHeight() { RECT rect; GetWindowRect(_hwnd, &rect); return rect.bottom - rect.top; }
}