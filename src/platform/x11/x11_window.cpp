#include "GooseUI/platform/x11/x11_window.h"

#include <algorithm>


namespace goose::platform::gX11
{
    // Graphic Dependent
    #if GOOSEUI_ENABLE_OPENGL
    

    void gX11_window::_createContext_openGL()
    {
        static GLint glxAttribs[] = {
		GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER,
        None
	    };

        int frameBufferCount;
        GLXFBConfig* fbc = glXChooseFBConfig(_display, DefaultScreen(_display), glxAttribs, &frameBufferCount);

        GLXFBConfig chosenFbc = fbc[0];
        XVisualInfo* vi = glXGetVisualFromFBConfig(_display, chosenFbc);

        GLXContext ctx = glXCreateNewContext(_display, chosenFbc, GLX_RGBA_TYPE, nullptr, True);
        glXMakeCurrent(_display, _window, ctx);

        XFree(fbc);
    }

    void gX11_window::_shareContext_openGL()
    {
        static GLint glxAttribs[] = {
		GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER,
        None
	    };

        graphics::gl::glRenderer* glBackend = static_cast<graphics::gl::glRenderer*>(_backend);
        GLXContext ctx = glXGetCurrentContext();

        int frameBufferCount;
        GLXFBConfig* fbc = glXChooseFBConfig(_display, DefaultScreen(_display), glxAttribs, &frameBufferCount);

        GLXFBConfig chosenFbc = fbc[0];

        if(!glBackend->hasContext())
        {
            glBackend->setContext(new graphics::gl::glContext{ctx});
            GLXContext sharedCtx = glXCreateNewContext(_display, chosenFbc, GLX_RGBA_TYPE, glBackend->getContext().glxContext, True);
        }else 
        {
            GLXContext sharedCtx = glXCreateNewContext(_display, chosenFbc, GLX_RGBA_TYPE, glBackend->getContext().glxContext, True);
        }
    }

    void gX11_window::_destroyContext_openGL()
    {
    }
    #endif

    #if GOOSEUI_ENABLE_VULKAN
    #endif
}

namespace goose::platform::gX11
{
    gX11_window::gX11_window(const std::string& title, int width, int height, goose::core::enumerations::windowPos posistion, goose::core::enumerations::graphicsBackend graphicsBackend)
    {
        _display = XOpenDisplay(nullptr);
        if(!_display) { printf("[GooseUI] -- Faild to open xDisplay\n"); exit(1); }

        // Calculate Screen Posistion
        int defaultScreen = DefaultScreen(_display);
        int screenWidth, screenHeight;
        screenWidth = DisplayWidth(_display, defaultScreen);
        screenHeight = DisplayHeight(_display, defaultScreen);

        int posX, posY;
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

        // Create Window
        _window = XCreateSimpleWindow(
            _display,
            RootWindow(_display, defaultScreen),
            posX,
            posY,
            width,
            height,
            1,
            BlackPixel(_display, defaultScreen),
            WhitePixel(_display, defaultScreen)
        );

        _wm_delete_window = XInternAtom(_display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(_display, _window, &_wm_delete_window, 1);

        XStoreName(_display, _window, title.c_str());
        XSelectInput(_display, _window, ExposureMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask);

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

    gX11_window::~gX11_window()
    {
        _isRunning = false;

        #if GOOSEUI_ENABLE_OPENGL
            if(_backendContext == core::enumerations::opengl) { _destroyContext_openGL(); }
        #endif

        #if GOOSEUI_ENABLE_VULKAN
            if(_backendContext == core::enumerations::vulkan) { _destroyContext_vulkan(); }
        #endif

        if(_backend) { delete _backend; };
        XDestroyWindow(_display, _window);
        XCloseDisplay(_display);
    }

    // OVERIDES
    // Window Configuration
    void gX11_window::setHeader(const std::string& title, bool isVisible, bool hasButtons, bool hasMinimize, bool hasMaximise)
    {
        if(!title.empty()) { XStoreName(_display, _window, title.c_str()); }

        // PAIN
        struct { long flags, functions, decorations, inputMode, status; } hints = {0};

        if(!isVisible)
        {
            hints.flags = 1L << 1 | 1L << 0;

            Atom motif = XInternAtom(_display, "_MOTIF_WM_HINTS", false);
            XChangeProperty(_display, _window, motif, motif, 32, PropModeReplace, reinterpret_cast<unsigned char*>(&hints), 5);
        }else 
        {
            XDeleteProperty(_display, _window, XInternAtom(_display, "_MOTIF_WM_HINTS", False));
        }

        if(hasMaximise) { this->isResizeable(false); } else { this->isResizeable(true); }   // ugh

        if(!hasMinimize) { printf("[GooseUI] -- Variable [hasMinimize] is unsuported for [xOrg]\n"); }
        if(!hasMinimize) { printf("[GooseUI] -- Variable [hasButtons] is unsuported for [xOrg]\n"); }

        XFlush(_display);
    }

    void gX11_window::isResizeable(bool isResizeable)
    {
        XSizeHints* sizeHints = XAllocSizeHints();

        if(!isResizeable)
        {
            sizeHints->flags = PMinSize | PMaxSize;
            sizeHints->min_width = sizeHints->max_width = getWidth();
            sizeHints->min_height = sizeHints->max_height = getHeight();
        }else 
        {
            long currentHints;
            XGetWMNormalHints(_display, _window, sizeHints, &currentHints);
            sizeHints->flags &= ~(PMinSize | PMaxSize);
        }

        XSetWMNormalHints(_display, _window, sizeHints);
        XFree(sizeHints);
    }

    void gX11_window::isAllwaysOnTop(bool isOnTop) { printf("[GooseUI] -- Variable [isOnTop] is unsuported for [xOrg]\n"); }

    // Window Size
    void gX11_window::setSize(int width, int height)
    {
        XSizeHints sizeHints;
        sizeHints.flags = PSize;
        sizeHints.width = width;
        sizeHints.height = height;

        XSetNormalHints(_display, _window, &sizeHints);
        XResizeWindow(_display, _window, width, height);
        XFlush(_display);
    }

    void gX11_window::maximize() 
    {
        Atom wmState = XInternAtom(_display, "_NET_WM_STATE", false);
        Atom maxWidth = XInternAtom(_display, "_NET_WM_STATE_MAXIMIZED_HORZ", false);
        Atom maxHeight = XInternAtom(_display, "_NET_WM_STATE_MAXIMIZED_VERT", false);

        XEvent event;
        event.xclient.type = ClientMessage;
        event.xclient.window = _window;
        event.xclient.message_type = wmState;
        event.xclient.format = 32;
        event.xclient.data.l[0] = 1;
        event.xclient.data.l[1] = maxWidth;
        event.xclient.data.l[2] = maxHeight;

        XSendEvent(_display, DefaultRootWindow(_display), false, SubstructureNotifyMask, &event);
    }

    void gX11_window::minimize() { XIconifyWindow(_display, _window, DefaultScreen(_display)); XFlush(_display); }

    void gX11_window::restoreSize() 
    {
        Atom wmState = XInternAtom(_display, "_NET_WM_STATE", false);
        Atom maxWidth = XInternAtom(_display, "_NET_WM_STATE_MAXIMIZED_HORZ", false);
        Atom maxHeight = XInternAtom(_display, "_NET_WM_STATE_MAXIMIZED_VERT", false);

        XEvent event;
        event.xclient.type = ClientMessage;
        event.xclient.window = _window;
        event.xclient.message_type = wmState;
        event.xclient.format = 32;
        event.xclient.data.l[0] = 0;
        event.xclient.data.l[1] = maxWidth;
        event.xclient.data.l[2] = maxHeight;

        XSendEvent(_display, DefaultRootWindow(_display), false, SubstructureNotifyMask, &event);
    }

    // Window Visibility
    void gX11_window::show() { XMapWindow(_display, _window); XFlush(_display); }
    void gX11_window::hide() { XUnmapWindow(_display, _window); XFlush(_display); }
    void gX11_window::destroy() { XDestroyWindow(_display, _window); }

    // Widget Management
    void gX11_window::addWidget(core::templates::widget::base* widget) { _widgets.push_back(widget); }
    void gX11_window::removeWidget(core::templates::widget::base* widget)
    {
        std::vector<core::templates::widget::base*>::iterator target = std::find(_widgets.begin(), _widgets.end(), widget);
        if(target != _widgets.end()){ _widgets.erase(target); }
    }
    
    void gX11_window::renderWidgets()
    {
        if(!_backend) return;

        #if GOOSEUI_ENABLE_OPENGL
        graphics::gl::glRenderer* glBackend = static_cast<graphics::gl::glRenderer*>(_backend);
        ;
        if(_backendContext == core::enumerations::opengl) {  glXMakeCurrent(_display, _window, glBackend->getContext().glxContext); }
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
        if(_backendContext == core::enumerations::opengl) { glXSwapBuffers(_display, _window); }
        #endif
    }

    void gX11_window::handelEvents()
    {
        XEvent event;
        while(XPending(_display) > 0) // FIX
        {
            XNextEvent(_display, &event);
            
            // Set evtData & run event loop
            bool handelWidgets = true;
            core::event::event evtData;
            
            switch (event.type)
            {
                case ClientMessage:
                {
                    if((Atom)event.xclient.data.l[0] == _wm_delete_window) { _isRunning = false; handelWidgets = false; }
                    break;
                }
                case ButtonPress:
                {
                    evtData.mouseX = event.xbutton.x;
                    evtData.mouseY = event.xbutton.y;

                    if(event.xbutton.button == Button1) { evtData.type = core::event::eventType::leftMouseDown; break; }
                    if(event.xbutton.button == Button3) { evtData.type = core::event::eventType::rightMouseDown; break; }
                    break;
                }
                case ButtonRelease:
                {
                    evtData.mouseX = event.xbutton.x;
                    evtData.mouseY = event.xbutton.y;
                    
                    if(event.xbutton.button == Button1) { evtData.type = core::event::eventType::leftMouseUp; break; }
                    break;
                }

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
        }

        renderWidgets();
    }

    // Returns
    Display* gX11_window::getDisplay() { return _display; }
    Window gX11_window::getWindow() { return _window; }

    bool gX11_window::isRunning() { return _isRunning; }

    int gX11_window::getDisplayService() const { return core::enumerations::displayService::x11; }
    int gX11_window::getWidth() { XWindowAttributes windowAtr; XGetWindowAttributes(_display, _window, &windowAtr); return windowAtr.width; }
    int gX11_window::getHeight() { XWindowAttributes windowAtr; XGetWindowAttributes(_display, _window, &windowAtr); return windowAtr.height; }
}