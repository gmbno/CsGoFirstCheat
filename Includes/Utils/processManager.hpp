#pragma once

#include <Windows.h>
#include <string>
#include <iostream>

class processManager {
    public:
        processManager();
        ~processManager();
        void loadProcess(std::string const &winName = "Counter-Strike: Global Offensive");
        DWORD const &getPid() const;
        HANDLE const &getHandle() const;
    private:
        DWORD _pid;
        HANDLE _handle;
};