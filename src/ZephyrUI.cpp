#include "ZephyrUI/ZephyrUI.h"

#include <string>


std::string zephyr::common::xdgType()
{
    return std::getenv("XDG_SESSION_TYPE");
}