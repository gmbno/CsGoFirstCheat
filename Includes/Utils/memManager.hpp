#pragma once

#include <Windows.h>
#include <TlHelp32.h>

class memManager {
    public:
        memManager();
        ~memManager();

        static void myRead(HANDLE handle, DWORD address, LPVOID value, DWORD size);
        static void myWrite(HANDLE handle, DWORD address, LPVOID value, DWORD size);
    private:
};