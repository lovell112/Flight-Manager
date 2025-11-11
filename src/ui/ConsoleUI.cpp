//
// Created by HP on 05/11/2025.
//

#include "../../include/ui/ConsoleUI.h"

ConsoleUI::ConsoleUI() {
    m_controller = new MenuController();
}

ConsoleUI::~ConsoleUI() {
    delete m_controller;
}


void ConsoleUI::exec() {
    m_controller->run();
}
