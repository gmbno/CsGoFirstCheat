#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include "Utils/Offsets.hpp"

class moduleManager {
    public:
        moduleManager();
        ~moduleManager();
        void loadModules(DWORD pid, HANDLE const &handle);

        DWORD const &getDwBaseClient() const;
        DWORD const &getDwBaseEngine() const;
        DWORD const &getDwBasePlayer() const;
        DWORD const &getDwEntityList() const;
    private:
        DWORD _dwBaseClient;
        DWORD _dwBaseEngine;
        DWORD _dwBasePlayer;
        DWORD _dwEntityList;
};