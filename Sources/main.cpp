#include <iostream>
#include "processManager.hpp"
#include "moduleManager.hpp"
#include "loopManager.hpp"

int main() {
    processManager pm;
    moduleManager mm;
    loopManager lm;

    pm.loadProcess();
    mm.loadModules(pm.getPid());

    return lm.mainLoop(pm, mm);
}