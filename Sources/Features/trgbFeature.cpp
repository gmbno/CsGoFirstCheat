#include "Features/trgbFeature.hpp"

trgbFeature::trgbFeature(HANDLE handle, moduleManager const &mm) {
    this->_handle = handle;
    this->_mm = mm;
}

trgbFeature::trgbFeature() {

}

trgbFeature::~trgbFeature() {

}

#include <iostream>
void trgbFeature::loop() {
    DWORD crossHairId = 0;

    ReadProcessMemory(this->_handle, 
        reinterpret_cast<LPVOID>(this->_mm.getDwBasePlayer() + 0xFC), &crossHairId, sizeof(crossHairId), NULL);
    std::cout << crossHairId << std::endl;
}