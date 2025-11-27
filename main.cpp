#include <filesystem>
#include <iostream>
#include "include/repository/AirplaneRepository.h"
#include "include/repository/CustomerRepository.h"
#include "include/repository/FlightRepository.h"
#include "include/repository/TicketRepository.h"
#include "include/service/AuthService.h"
#include "include/ui/ConsoleUI.h"
#include "include/ui/MenuController.h"

int main() {
    const auto* consoleApp = new ConsoleUI();
    consoleApp->exec();
    delete consoleApp;
    return 0;
}