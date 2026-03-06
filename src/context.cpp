#include "GooseUI/context.h"

namespace GooseUI // Public
{
    void application::init(backendType backendType)
    {
        if(_instance){ return; }
        
        #if GOOSEUI_HAS_OPENGL
        if(backendType == backendType::OpenGL)
        { 
            _renderer = new graphics::gl::glRenderer(); 
            _backendType = backendType::OpenGL;
        }
        #endif
        
        #if GOOSEUI_HAS_VULKAN
            // TODO
        #endif
        
        _instance = new application();
    }
    
    application::backendType application::getBackendType()
        { return _backendType; }
    
    absractions::iRenderer* application::getRenderer()
        { return _renderer; }
}