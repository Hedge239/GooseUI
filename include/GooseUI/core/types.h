#ifndef _GOOSEUI_TYPES_H_
#define _GOOSEUI_TYPES_H_

namespace goose
{
    namespace interface
    {
        class iWindow;      //FORWARD DECLERATION
        class iWidget;      //FORWARD DECLERATION
        class iRenderer;    //FORWARD DECLERATION
    }
    
    namespace core 
    {
        namespace types
        {
            enum class graphicsBackend
            {
                opengl,
                vulkan
            };

            enum displayService
            {
                win32 = 1 << 0,
                x11 = 1 << 1,
                wayland = 1 << 2
            };
            
            enum windowPosistion
            {
                SCREEN_TOP,
                SCREEN_BOTTOM,
                SCREEN_LEFT,
                SCREEN_RIGHT,
                SCREEN_TOP_LEFT,
                SCREEN_TOP_RIGHT,
                SCREEN_BOTTOM_LEFT,
                SCREEN_BOTTOM_RIGHT,
                SCREEN_CENTER
            };

            enum componentScale
            {
                SCALE_NONE,
                SCALE_VERTICAL,
                SCALE_HORIZONTAL,
                SCALE_ALL
            };

            enum componentAlign
            {
                ALIGN_TOP = 1 << 0,
                ALIGN_BOTTOM = 1 << 1,
                ALIGN_LEFT = 1 << 2,
                ALIGN_RIGHT = 1 << 3
            };
            
            struct layoutRestraints
            {
                int minWidth = 0;
                int minHeight = 0;
                int maxWidth = 0;
                int maxHeight = 0;
                
                int minX = 0;
                int minY = 0;
                int maxX = 0;
                int maxY = 0;
            };
            
            struct color 
            { 
                float 
                R, 
                G, 
                B, 
                A; 
            };
            
            namespace event
            {
                // Changed how this works, now it used to pass data from the window to the widget (Ie mouse posistion) instead of data from widget to user
                // I will just add more functions like getText() or whatnot
                enum class eventType
                {
                    none,
                    leftMouseDown,
                    leftMouseUp,
                    rightMouseDown,
                };
    
                struct eventData
                {
                    eventType type = eventType::none;
    
                    float mouseX = 0;
                    float mouseY = 0;
                };
            }
        }
    }
}

#endif /*_GOOSEUI_TYPES_H_*/