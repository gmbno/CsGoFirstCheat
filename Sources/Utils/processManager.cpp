#include "processManager.hpp"

processManager::processManager() {
    this->_pid = -1;
}

processManager::~processManager() {
    
}

void processManager::loadProcess(std::string const &winName) {
    HWND hwnd;    
    
    hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive");
    if (!hwnd) {
        std::cerr << "Csgo.exe not found." << std::endl;
        Sleep(2000);
        exit(0);
    }
    GetWindowThreadProcessId(hwnd, &this->_pid);
    if (!this->_pid) {
        std::cerr << "Process ID not get." << std::endl;
        Sleep(2000);
        exit(0);
    }
    this->_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pid);
}

DWORD const &processManager::getPid() const {
    return this->_pid;
}

HANDLE const &processManager::getHandle() const {
    return this->_handle;
}