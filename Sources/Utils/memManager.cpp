#include "Utils/memManager.hpp"

memManager::memManager() {

}

memManager::~memManager() {

}

void memManager::myRead(HANDLE handle, DWORD address, LPVOID value, DWORD size) {
    ReadProcessMemory(handle, reinterpret_cast<LPVOID>(address), value, size, NULL);
}

void memManager::myWrite(HANDLE handle, DWORD address, LPVOID value, DWORD size) {
    WriteProcessMemory(handle, reinterpret_cast<LPVOID>(address), value, size, NULL);
}
