#pragma once

#include "Utils/processManager.hpp"
#include "Utils/moduleManager.hpp"
#include "Features/trgbFeature.hpp"

class loopManager {
    public:
        loopManager();
        ~loopManager();
        int mainLoop(processManager &pm, moduleManager const &mm);
    private:
        BOOL _trgbEnabled;
        trgbFeature _trgb;
};