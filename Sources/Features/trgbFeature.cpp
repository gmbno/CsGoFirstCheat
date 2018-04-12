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
    DWORD teamNum = 0;

    ReadProcessMemory(this->_handle, 
        reinterpret_cast<LPVOID>(this->_mm.getDwBasePlayer() + Offsets::m_iCrossHairID), &crossHairId, sizeof(crossHairId), NULL);
    ReadProcessMemory(this->_handle, 
        reinterpret_cast<LPVOID>(this->_mm.getDwBasePlayer() + Offsets::m_iTeamNum), &teamNum, sizeof(teamNum), NULL);
    std::cout << "CrossId: " << crossHairId << std::endl;
    DWORD attack = 5;
    DWORD reset = 0;
    DWORD inCrossEntityBase = 0;
    DWORD inCrossEntityTeam = 0;
    if (crossHairId > 0 && crossHairId <= 64) {
        for (int i = 1; i < 64; i++) {
            ReadProcessMemory(this->_handle, 
                reinterpret_cast<LPVOID>(this->_mm.getDwBaseClient() + Offsets::m_dwEntityList + (crossHairId - 1) * 0x10), &inCrossEntityBase, sizeof(inCrossEntityBase), NULL);
            ReadProcessMemory(this->_handle, 
                reinterpret_cast<LPVOID>(inCrossEntityBase + Offsets::m_iTeamNum), &inCrossEntityTeam, sizeof(inCrossEntityTeam), NULL);
            std::cout << "CrossTeam: " << inCrossEntityTeam << std::endl;
            if (teamNum != inCrossEntityTeam) {
                WriteProcessMemory(this->_handle, 
                    reinterpret_cast<LPVOID>(this->_mm.getDwBaseClient() + Offsets::m_dwForceAttack), &attack, sizeof(attack), NULL);
            }
        }
    } else {
         WriteProcessMemory(this->_handle, 
            reinterpret_cast<LPVOID>(this->_mm.getDwBaseClient() + Offsets::m_dwForceAttack), &reset, sizeof(reset), NULL);
    }
}