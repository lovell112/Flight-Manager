/**
 * @file ConsoleUI.cpp
 * @brief Triển khai các method của ConsoleUI
 */

#include "../../include/ui/ConsoleUI.h"

ConsoleUI::ConsoleUI() {
    m_controller = new MenuController();
}

ConsoleUI::~ConsoleUI() {
    delete m_controller;
}

void ConsoleUI::exec() const {
    m_controller->run();
}