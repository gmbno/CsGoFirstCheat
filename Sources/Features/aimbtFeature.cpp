#include "Features/aimbtFeature.hpp"

aimbtFeature::aimbtFeature(HANDLE handle, moduleManager const &mm)
{
    this->_handle = handle;
    this->_mm = mm;
}

aimbtFeature::aimbtFeature()
{
}

aimbtFeature::~aimbtFeature()
{
}

void aimbtFeature::makeVector(float *pfin, float *vector)
{
	float pitch = (float) (pfin[0] * M_PI / 180);
	float yaw = (float) (pfin[1] * M_PI / 180);
	float tmp = (float) (cos(pitch));
 
	vector[0] = (float) (-tmp * -cos(yaw));
	vector[1] = (float) (sin(yaw)*tmp);
	vector[2] = (float) (-sin(pitch));
}

float aimbtFeature::getFOV(float *angles, float *source, float *dst)
{
	float ang[3];
    float aim[3];
	float fov;
	this->getAngles(source, dst, ang);
	this->makeVector(angles, aim);
	this->makeVector(ang, ang);
 
	float mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
	float mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
 
	float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];
	fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0f / M_PI);
 
	return fov;
}

void aimbtFeature::getAngles(float *src, float *dst, float *newAngles) {
    double delta[3] = {(src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2])};
    double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
    newAngles[0] = (float)(asinf(delta[2] / hyp) * 57.295779513082f);
    newAngles[1] = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
    newAngles[2] = 0.0f;
    if (delta[0] >= 0.0)
    {
        newAngles[1] += 180.0f;
    }
}

#include <iostream>
void aimbtFeature::loop()
{
    float playerViewAngles[3];
    DWORD playerTeam = 0;
    float playerOrigin[3];
    float playerViewOffset[3];
    float playerEyes[3];

    DWORD entityBase = 0;
    DWORD entityTeam = 0;
    int entityHealth = 0;
    BOOL entityIsDormant = false;
    DWORD entitySkPtr;
    float entitySk[3][4];
    float entityOrigin[3];
    float entityViewOffset[3];
    float entityEyes[3];

    float maxFov = 1.5f;

    memManager::myRead(this->_handle, this->_mm.getDwBaseEngine() + Offsets::m_dwViewAngles, &playerViewAngles, sizeof(playerViewAngles));
    memManager::myRead(this->_handle, this->_mm.getDwBasePlayer() + Offsets::m_iTeamNum, &playerTeam, sizeof(playerTeam));
    memManager::myRead(this->_handle, this->_mm.getDwBasePlayer() + Offsets::m_vecOrigin, &playerOrigin, sizeof(playerOrigin));
    memManager::myRead(this->_handle, this->_mm.getDwBasePlayer() + Offsets::m_vecViewOffset, &playerViewOffset, sizeof(playerViewOffset));
    for (int i = 0; i < 3; i++)
    {
        playerEyes[i] = playerOrigin[i] + playerViewOffset[i];
    }
    for (int i = 1; i < 65; i++)
    {
        memManager::myRead(this->_handle, this->_mm.getDwBaseClient() + Offsets::m_dwEntityList + (i - 1) * 0x10, &entityBase, sizeof(entityBase));
        if (!entityBase)
            continue;
        memManager::myRead(this->_handle, entityBase + Offsets::m_iHealth, &entityHealth, sizeof(entityHealth));
        memManager::myRead(this->_handle, entityBase + Offsets::m_bDormant, &entityIsDormant, sizeof(entityIsDormant));
        memManager::myRead(this->_handle, entityBase + Offsets::m_iTeamNum, &entityTeam, sizeof(entityTeam));
        if (entityIsDormant || entityHealth < 1 || playerTeam == entityTeam)
            continue;
        
        memManager::myRead(this->_handle, entityBase + Offsets::m_vecOrigin, &entityOrigin, sizeof(entityOrigin));
        memManager::myRead(this->_handle,entityBase + Offsets::m_vecViewOffset, &entityViewOffset, sizeof(entityViewOffset));
        for (int i = 0; i < 3; i++)
        {
            entityEyes[i] = entityOrigin[i] + entityViewOffset[i];
        }
        float fov = this->getFOV(playerViewAngles, playerEyes, entityEyes);
        if (fov < maxFov) {
            maxFov = fov;
            memManager::myRead(this->_handle, (entityBase + Offsets::m_dwBoneMatrix), &entitySkPtr, sizeof(entitySkPtr));
            memManager::myRead(this->_handle, (entitySkPtr + 8 * 0x30), &entitySk, sizeof(entitySk));
        }
    }
    if (maxFov >= 1.5)
        return;
    float newAngles[3];
    float entitySkHead[3] = {
        entitySk[0][3],
        entitySk[1][3],
        entitySk[2][3]};
    this->getAngles(playerEyes, entitySkHead, newAngles);

    memManager::myWrite(this->_handle, this->_mm.getDwBaseEngine() + Offsets::m_dwViewAngles, &newAngles, sizeof(newAngles));
}