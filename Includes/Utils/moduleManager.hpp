#pragma once

#include <Windows.h>
#include <TlHelp32.h>

class moduleManager {
    public:
        moduleManager();
        ~moduleManager();
        void loadModules(DWORD pid);

        DWORD const &getDwBaseClient() const;
        DWORD const &getDwBaseEngine() const;
    private:
        DWORD _dwBaseClient;
        DWORD _dwBaseEngine;
};