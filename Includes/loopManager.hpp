#pragma once

#include "Utils/processManager.hpp"
#include "Utils/moduleManager.hpp"
#include "Features/trgbFeature.hpp"
#include "Features/aimbtFeature.hpp"

class loopManager {
    public:
        loopManager();
        ~loopManager();
        void initFeatures(processManager &pm, moduleManager const &mm);
        int mainLoop();
    private:
        BOOL _trgbEnabled;
        trgbFeature _trgb;
        BOOL _aimbtEnabled;
        aimbtFeature _aimbt;
};