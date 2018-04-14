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
    float vel[3];
    DWORD teamNum = 0;
    DWORD attackValue = 5;
    DWORD inCrossEntityBase = 0;
    DWORD inCrossEntityTeam = 0;

    memManager::myRead(this->_handle, this->_mm.getDwBasePlayer() + Offsets::m_iCrossHairID, &crossHairId, sizeof(crossHairId));
    memManager::myRead(this->_handle, this->_mm.getDwBasePlayer() + Offsets::m_iTeamNum, &teamNum, sizeof(teamNum));
    memManager::myRead(this->_handle, this->_mm.getDwBasePlayer() + Offsets::m_vecVelocity, &vel, sizeof(vel));
    if (vel[0] > 50 || vel[1] > 50 || vel[0] < -50 || vel[1] < -50) {
        attackValue = 0;
        memManager::myWrite(this->_handle, this->_mm.getDwBaseClient() + Offsets::m_dwForceAttack, &attackValue, sizeof(attackValue));
        return;
    }
    if (crossHairId > 0 && crossHairId <= 64)
    {
        memManager::myRead(this->_handle, this->_mm.getDwBaseClient() + Offsets::m_dwEntityList + (crossHairId - 1) * 0x10, &inCrossEntityBase, sizeof(inCrossEntityBase));
        memManager::myRead(this->_handle, inCrossEntityBase + Offsets::m_iTeamNum, &inCrossEntityTeam, sizeof(inCrossEntityTeam));
        if (teamNum != inCrossEntityTeam)
        {
            attackValue = 5;
            memManager::myWrite(this->_handle, this->_mm.getDwBaseClient() + Offsets::m_dwForceAttack, &attackValue, sizeof(attackValue));
        }
    }
    else if (attackValue != 0)
    {
        attackValue = 0;
        memManager::myWrite(this->_handle, this->_mm.getDwBaseClient() + Offsets::m_dwForceAttack, &attackValue, sizeof(attackValue));
    }
}