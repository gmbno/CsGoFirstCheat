#include "loopManager.hpp"

loopManager::loopManager() {
    this->_trgbEnabled = 0;
}

loopManager::~loopManager() {

}

int loopManager::mainLoop(processManager &pm, moduleManager const &mm) {
    while (1) {
        pm.refreshHandle();
        if (GetAsyncKeyState(VK_F11)) {
            std::cout << "Leaving..." << std::endl;
            Sleep(3000);
            return -1;
        }
        if (GetAsyncKeyState(VK_F10)) {
            if (this->_trgbEnabled == 0) {
                this->_trgbEnabled = 1;
                std::cout << "Trgb is now enabled" << std::endl;
            }
            else {
                this->_trgbEnabled = 0;
                std::cout << "Trgb is now disabled" << std::endl;                
            }
            while (GetAsyncKeyState(VK_F10));
        }

        if (this->_trgbEnabled == 1) {
            this->_trgb.loop();
        }

        Sleep(10);
    }
}