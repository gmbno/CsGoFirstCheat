#pragma once

#include "Utils/offsets.hpp"
#include "Utils/moduleManager.hpp"
#include <Windows.h>

class trgbFeature {
    public:
        trgbFeature();
        trgbFeature(HANDLE handle, moduleManager const &mm);
        ~trgbFeature();
        void loop();
    private:
        moduleManager _mm;
        HANDLE _handle;
};