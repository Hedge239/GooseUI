#ifndef _ZUTILITY_H_
#define _ZUTILITY_H_

namespace zUI
{
    namespace zCore
    {
        class zUtility
        {
            public:
            static bool contains(int objectPosX, int objectPosY, int ObjectWidth, int ObjectHeight, int PosX, int PosY);
        };
    }
}

#endif /*_ZUTILITY_H_*/