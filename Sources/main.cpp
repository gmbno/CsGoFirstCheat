#include <iostream>
#include "Utils/processManager.hpp"
#include "Utils/moduleManager.hpp"
#include "loopManager.hpp"

int main() {
    processManager pm;
    moduleManager mm;
    loopManager lm;

    pm.loadProcess();
    mm.loadModules(pm.getPid(), pm.getHandle());

    lm.initFeatures(pm, mm);
    return lm.mainLoop();
}