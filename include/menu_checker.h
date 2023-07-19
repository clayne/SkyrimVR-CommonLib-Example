// credit to Shizof for this method
#pragma once

#include "customEventSink.hpp"
#include <unordered_map>

namespace MenuChecker
{

    extern std::vector<std::string> gameStoppingMenus;

    extern std::unordered_map<std::string, bool> menuTypes;

    bool isGameStopped();

    void begin();

    void onMenuOpenClose(RE::MenuOpenCloseEvent const *evn);
}
