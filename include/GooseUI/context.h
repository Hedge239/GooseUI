#ifndef _GOOSEUI_CONTEXT_H_
#define _GOOSEUI_CONTEXT_H_

#if GOOSEUI_HAS_VULKAN
    // TODO
#endif

#if GOOSEUI_HAS_OPENGL
    #include "GooseUI/graphics/GL/glRenderer.h"
#endif

/* 
    The Idea of this is too prevent people from having multiple Backends per application, which could cause future issues.
    This also simplifies adding a access point for a backendPanel to allow user access without dependence on making a custom widget
*/

namespace GooseUI
{
    class application
    {  
        public:
        //enum class graphicsBackend{ OpenGL, Vulkan }; - We add VK Support later
        enum class backendType{ OpenGL };
        
        static void init(backendType backendType);
        static backendType getBackendType();
        static absractions::iRenderer* getRenderer();
        
        private: // Hate using this, but it just easier
        inline static backendType _backendType = application::backendType::OpenGL;
        inline static absractions::iRenderer* _renderer = nullptr;
        inline static application* _instance = nullptr;
    };
}

#endif /*_GOOSEUI_CONTEX_H_*/