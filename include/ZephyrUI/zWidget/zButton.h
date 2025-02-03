#ifndef _ZBUTTON_H_
#define _ZBUTTON_H_

#include "ZephyrUI/zCore/zWidget.h"
#include <string>

namespace zUI
{
    namespace zWidget
    {
        class zButton : public zCore::zWidget
        {
            public:
            virtual ~zButton() = default;

            virtual void onClick() = 0;
            virtual void setLabel(std::string label) = 0;
        };

        zButton* createButton(zWindow* window, int eventID, zCore::zEnumerations::zComponentScale, int zComponentAlign, int X, int Y, int Width, int Height, zCore::zEventDispatcher& EvtDispatcher);
    }
}

#endif /*_ZBUTTON_H_*/