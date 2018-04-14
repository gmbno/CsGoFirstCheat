#include "loopManager.hpp"

loopManager::loopManager()
{
    this->_trgbEnabled = 0;
    this->_aimbtEnabled = 0;
}

loopManager::~loopManager()
{
}

void loopManager::initFeatures(processManager &pm, moduleManager const &mm)
{
    this->_trgb = trgbFeature(pm.getHandle(), mm);
    this->_aimbt = aimbtFeature(pm.getHandle(), mm);
}

int loopManager::mainLoop()
{
    while (1)
    {
        if (GetAsyncKeyState(VK_F11))
        {
            std::cout << "Leaving..." << std::endl;
            Sleep(3000);
            return -1;
        }
        if (GetAsyncKeyState(VK_F10))
        {
            if (this->_trgbEnabled == 0)
            {
                this->_trgbEnabled = 1;
                std::cout << "Trgb is now enabled" << std::endl;
            }
            else
            {
                this->_trgbEnabled = 0;
                std::cout << "Trgb is now disabled" << std::endl;
            }
            while (GetAsyncKeyState(VK_F10));
        }

        if (GetAsyncKeyState(VK_F9))
        {
            if (this->_aimbtEnabled == 0)
            {
                this->_aimbtEnabled = 1;
                std::cout << "Aimbt is now enabled" << std::endl;
            }
            else
            {
                this->_aimbtEnabled = 0;
                std::cout << "Aimbt is now disabled" << std::endl;
            }
            while (GetAsyncKeyState(VK_F9));
        }

        if (this->_aimbtEnabled == 1)
        {
            this->_aimbt.loop();
        }
        if (this->_trgbEnabled == 1)
        {
            this->_trgb.loop();
        }

        Sleep(30);
    }
}