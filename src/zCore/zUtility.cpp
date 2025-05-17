#include "ZephyrUI/zCore/zUtility.h"

using namespace zUI;
using namespace zCore;

// I created this just for this -_-
bool zUtility::contains(int objectPosX, int objectPosY, int ObjectWidth, int ObjectHeight, int PosX, int PosY)
{
    return
    PosX >= objectPosX && PosX < objectPosX + ObjectWidth &&
    PosY >= objectPosY && PosY < objectPosY + ObjectHeight;
}