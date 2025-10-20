#include "GooseUI/platform/win32/win32_window.h"

//#include "GooseUI/graphics/gl_renderer.h"
//#define GOOSEUI_ENABLE_OPENGL true

namespace goose::platform::gWin32
{
    LRESULT CALLBACK gWin32_window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        gWin32_window* self = reinterpret_cast<gWin32_window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        
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

    // Graphic Dependent
    #if GOOSEUI_ENABLE_OPENGL
    void gWin32_window::_createContext_openGL()
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

    void gWin32_window::_shareContext_openGL()
    {
        HDC hdc = GetDC(this->getHwnd());
        HGLRC hglrc = wglGetCurrentContext();
        graphics::gl::glRenderer* glBackend = static_cast<graphics::gl::glRenderer*>(_backend);
        
        if(!glBackend->hasContext())
        {
            glBackend->setContext(new graphics::gl::glContext{hglrc, hdc});
        }else 
        {
            wglShareLists(glBackend->getContext().hglrc, hglrc);
        }
    }

    void gWin32_window::_destroyContext_openGL()
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

    #if GOOSEUI_ENABLE_VULKAN
    #endif
}

namespace goose::platform::gWin32
{
    gWin32_window::gWin32_window(const std::string& title, int width, int height, goose::core::enumerations::windowPos posistion, goose::core::enumerations::graphicsBackend graphicsBackend)
    {
        _hInstance = GetModuleHandle(nullptr);

        // Register Window Class
        WNDCLASSW WindowClass = {0};
        WindowClass.lpfnWndProc = gWin32_window::WindowProc;
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

        switch(graphicsBackend)
        {
            #if GOOSEUI_ENABLE_OPENGL
            case core::enumerations::opengl:
                _createContext_openGL();
                _backend = &goose::graphics::gl::glRenderer::getRenderer();
                _backendContext = core::enumerations::opengl;
                _shareContext_openGL();
                break;
            #endif

            #if GOOSEUI_ENABLE_VULKAN
            case core::enumerations::vulkan:
                break;
            #endif

            default:
                printf("GooseUI: Invalid backend \n");
                break;
        }

        _isRunning = true;
    }

    gWin32_window::~gWin32_window()
    {
        _isRunning = false;

        #if GOOSEUI_ENABLE_OPENGL
            if(_backendContext == core::enumerations::opengl) { _destroyContext_openGL(); }
        #endif

        #if GOOSEUI_ENABLE_VULKAN
            if(_backendContext == core::enumerations::vulkan) { _destroyContext_vulkan(); }
        #endif

        if(_backend) { delete _backend; };
        if(_hwnd) { DestroyWindow(_hwnd); }
    }

    HWND gWin32_window::getHwnd() { return _hwnd; }

    // OVERIDES
    // Window Configuration
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

    // Window Size
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

    void gWin32_window::maximize() { ShowWindow(_hwnd, SW_MAXIMIZE); UpdateWindow(_hwnd);}
    void gWin32_window::minimize() { ShowWindow(_hwnd, SW_MINIMIZE); UpdateWindow(_hwnd);}
    void gWin32_window::restoreSize() { ShowWindow(_hwnd, SW_RESTORE); UpdateWindow(_hwnd);}

    // Window Visibility
    void gWin32_window::show() { ShowWindow(_hwnd, SW_SHOW); UpdateWindow(_hwnd); }
    void gWin32_window::hide() { ShowWindow(_hwnd, SW_HIDE); UpdateWindow(_hwnd); }
    void gWin32_window::destroy() { DestroyWindow(_hwnd); }

    // Widget Management
    void gWin32_window::addWidget(core::templates::widget::base* widget) { _widgets.push_back(widget); }
    void gWin32_window::renderWidgets()
    {
        if(!_backend) return;

        #if GOOSEUI_ENABLE_OPENGL
        graphics::gl::glRenderer* glBackend = static_cast<graphics::gl::glRenderer*>(_backend);
        if(_backendContext == core::enumerations::opengl) { wglMakeCurrent(GetDC(this->getHwnd()), glBackend->getContext().hglrc); }
        #endif

        _backend->beginFrame(getWidth(), getHeight(), _bgColor);

        for(core::templates::widget::base* widget : _widgets)
        {
            if(widget)
            {
                widget->draw(*_backend);
            }
        }

        _backend->endFrame();

        #if GOOSEUI_ENABLE_OPENGL
        if(_backendContext == core::enumerations::opengl) { SwapBuffers(GetDC(this->getHwnd())); }
        #endif
    }

    void gWin32_window::handelEvents()
    {
        MSG msg;
        while(PeekMessage(&msg, getHwnd(), 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            // Set evtData & run event loop
            bool handelWidgets = true;

            core::event::event evtData;
            evtData.mouseX = ((int)(short)LOWORD(msg.lParam));
            evtData.mouseY = ((int)(short)HIWORD(msg.lParam));

            switch(msg.message)
            {
                case WM_QUIT: { _isRunning = false; handelWidgets = false; break; }
                
                case WM_LBUTTONDOWN: { evtData.type = core::event::eventType::leftMouseDown; break; }
                case WM_LBUTTONUP: { evtData.type = core::event::eventType::leftMouseUp; break; }
                case WM_RBUTTONDOWN: { evtData.type = core::event::eventType::rightMouseDown; break; }

                default: { handelWidgets = false; break; }
            }

            if(handelWidgets)
            {
                for(core::templates::widget::base* widget : _widgets)
                {
                    if(widget)
                    {
                        widget->handelEvent(evtData);
                    }
                }
            }

            renderWidgets();
        }
    }

    // Returns
    bool gWin32_window::isRunning() { return _isRunning; }

    int gWin32_window::getWidth() { RECT rect; GetClientRect(_hwnd, &rect); return rect.right - rect.left; }
    int gWin32_window::getHeight() { RECT rect; GetClientRect(_hwnd, &rect); return rect.bottom - rect.top; }
}