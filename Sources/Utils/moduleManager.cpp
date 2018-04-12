#include "moduleManager.hpp"

moduleManager::moduleManager() {
    this->_dwBaseClient = 0x0;
    this->_dwBaseEngine = 0x0;
    this->_dwBasePlayer = 0x0;
}

moduleManager::~moduleManager() {
    
}

void moduleManager::loadModules(DWORD pid, HANDLE const &handle) {
    HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    MODULEENTRY32 mEntry;
    mEntry.dwSize = sizeof(mEntry);
 
    while (Module32Next(hModule, &mEntry)) {
        if (!strcmp(mEntry.szModule, "client.dll"))
        {
            this->_dwBaseClient = (DWORD)mEntry.modBaseAddr;
            ReadProcessMemory(handle, 
                reinterpret_cast<LPVOID>(this->_dwBaseClient + Offsets::m_dwLocalPlayer),
                &this->_dwBasePlayer, sizeof(this->_dwBasePlayer), NULL);
            ReadProcessMemory(handle, 
                reinterpret_cast<LPVOID>(this->_dwEntityList + Offsets::m_dwEntityList),
                &this->_dwEntityList, sizeof(this->_dwEntityList), NULL);
        } else if (!strcmp(mEntry.szModule, "engine.dll")) {
            this->_dwBaseEngine = (DWORD)mEntry.modBaseAddr;            
        }
    }
    CloseHandle(hModule);
}

DWORD const &moduleManager::getDwBaseClient() const {
    return this->_dwBaseClient;
}

DWORD const &moduleManager::getDwBaseEngine() const {
    return this->_dwBaseEngine;
}

DWORD const &moduleManager::getDwBasePlayer() const {
    return this->_dwBasePlayer;
}

DWORD const &moduleManager::getDwEntityList() const {
    return this->_dwEntityList;
}