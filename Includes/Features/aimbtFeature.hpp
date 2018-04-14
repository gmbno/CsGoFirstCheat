#pragma once

#include "Utils/offsets.hpp"
#include "Utils/moduleManager.hpp"
#include <Windows.h>
#include <math.h>
#include "Utils/memManager.hpp"

class aimbtFeature {
    

    public:
        aimbtFeature();
        aimbtFeature(HANDLE handle, moduleManager const &mm);
        ~aimbtFeature();
        void loop();
    private:
        moduleManager _mm;
        HANDLE _handle;

        void getAngles(float *src, float *dst, float *newAngles);
        float getFOV(float *angles, float *source, float *dst);
        void makeVector(float *pfin, float *vector);
};