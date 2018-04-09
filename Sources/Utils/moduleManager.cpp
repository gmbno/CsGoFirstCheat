#include "moduleManager.hpp"

moduleManager::moduleManager() {
    this->_dwBaseClient = 0x0;
    this->_dwBaseEngine = 0x0;
}

moduleManager::~moduleManager() {
    
}

void moduleManager::loadModules(DWORD pid) {
    HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    MODULEENTRY32 mEntry;
    mEntry.dwSize = sizeof(mEntry);
 
    while (Module32Next(hModule, &mEntry)) {
        if (!strcmp(mEntry.szModule, "client.dll"))
        {
            this->_dwBaseClient = (DWORD)mEntry.modBaseAddr;
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