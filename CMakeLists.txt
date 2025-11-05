cmake_minimum_required(VERSION 4.0)
project(FlightManager)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp
        src/core/Airplane.cpp
        include/core/Airplane.h
        src/core/Flight.cpp
        include/core/Flight.h
        src/core/Customer.cpp
        include/core/Customer.h
        src/core/Ticket.cpp
        include/core/Ticket.h
        src/core/Admin.cpp
        include/core/Admin.h
        include/core/FlightStatus.h
        src/data/DataProcessor.cpp
        include/data/DataProcessor.h
        src/service/FlightManager.cpp
        include/service/FlightManager.h
        src/service/TicketManager.cpp
        include/service/TicketManager.h
        src/service/AuthService.cpp
        include/service/AuthService.h
        src/service/CustomerService.cpp
        include/service/CustomerService.h
        src/ui/ConsoleUI.cpp
        include/ui/ConsoleUI.h
        src/ui/MenuController.cpp
        include/ui/MenuController.h)
