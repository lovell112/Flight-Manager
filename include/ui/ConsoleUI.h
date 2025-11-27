//
// Created by HP on 05/11/2025.
//

#ifndef AIRPLANEMANAGER_CONSOLEUI_H
#define AIRPLANEMANAGER_CONSOLEUI_H
#include "MenuController.h"


class ConsoleUI {
    MenuController* m_controller;
public:
    ConsoleUI();
    ~ConsoleUI();
    void exec() const;
};


#endif //AIRPLANEMANAGER_CONSOLEUI_H