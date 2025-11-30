/**
 * @file MenuController.cpp
 * @description Triển khai các method của MenuController
 */

#include "../../include/ui/MenuController.h"
#include <iomanip>
#include <conio.h>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _HAS_STD_BYTE 0
#include <windows.h>

string MenuController::ESCAPE = "VK_ESCAPE";

MenuController::MenuController() {
    m_customerService = new CustomerService();
    m_authService = new AuthService();
    m_flightManager = new FlightManager();
    m_ticketManager = new TicketManager();
}

MenuController::~MenuController() {
    delete m_customerService;
    delete m_authService;
    delete m_flightManager;
    delete m_ticketManager;
}

void MenuController::mainMenu() {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << string(20, ' ') << "*****************************************\n";
    cout << string(20, ' ') << "*             SAN BAY NOI DIA           *\n";
    cout << string(20, ' ') << "*****************************************\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << string(20, ' ') << "1. Hien thi danh sach cac chuyen bay\n";
    cout << string(20, ' ') << "2. Dat ve\n";
    cout << string(20, ' ') << "3. Quan li\n";
    cout << string(20, ' ') << "0. Thoat\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << string(20, ' ') <<">>>> ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Moi ban nhap lua chon: ";
}

void MenuController::flightListMenu() const {
    const int flightIDWidth = 12;
    const int departureWidth = 20;
    const int destWidth = 16;
    const int statusWidth = 12;
    const int ticketWidth = 20;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << string(20, ' ') << "*****************************************\n";
    cout << string(20, ' ') << "*             SAN BAY NOI DIA           *\n";
    cout << string(20, ' ') << "*          (xem cac chuyen bay)         *\n";
    cout << string(20, ' ') << "*****************************************\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << string(29, ' ') << "DANH SACH CAC CHUYEN BAY\n\n";
    cout<< string(5, ' ') << string(flightIDWidth + departureWidth + destWidth + statusWidth + ticketWidth, '-') << endl;
    cout<< string(5, ' ') << left
        << setw(flightIDWidth) << "Flight ID"
        << setw(departureWidth) << "Departure date"
        << setw(destWidth) << "Destination"
        << setw(statusWidth) << "Status"
        << setw(ticketWidth) << "Ticket "
        << endl;
    cout<< string(5, ' ') << string(flightIDWidth + departureWidth + destWidth + statusWidth + ticketWidth, '-') << endl;

    for (const auto& flight : m_flightManager->getAllFlight()) {
        string status;
        switch (flight->getStatus()) {
            case FlightStatus::CANCELLED:
                status = "Huy chuyen";
                break;
            case FlightStatus::AVAILABLE:
                status = "Con ve";
                break;
            case FlightStatus::SOLD_OUT:
                status = "Het ve";
                break;
            case FlightStatus::COMPLETED:
                status = "Hoan tat";
                break;
        }
        cout << string(5, ' ') << left
        << setw(flightIDWidth) << flight->getFlightID()
        << setw(departureWidth) << flight->getDepartureDate().toString()
        << setw(destWidth) << flight->getDestinationAirport()
        << setw(statusWidth) << status;
        bool isFirstLine = true;
        if (flight->getTickets().empty()) {
            cout << "<none>\n";
            continue;
        }
        for (const auto& ticketID : flight->getTickets()) {
            if (!isFirstLine)
                cout << ", ";
            cout << ticketID;
            isFirstLine = false;
        }
        cout << endl;
    }
    cout<< string(5, ' ') << string(flightIDWidth + departureWidth + destWidth + statusWidth + ticketWidth, '-') << endl;
}

void MenuController::bookTicketMenu() const {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << string(20, ' ') << "*****************************************\n";
    cout << string(20, ' ') << "*             SAN BAY NOI DIA           *\n";
    cout << string(20, ' ') << "*                (dat ve)               *\n";
    cout << string(20, ' ') << "*****************************************\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    flightListMenu();

    cout << string(20, ' ') << "Vui long dien day du cac thong tin sau:\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << string(20, ' ') << ">>>> ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "CCCD: ";
    const string customerID = input();
    if (customerID == ESCAPE)
        return;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << string(20, ' ') << ">>>> ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Ho ten: ";
    const string customerFullname = input();
    if (customerFullname == ESCAPE)
        return;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << string(20, ' ') << ">>>> ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Ma chuyen bay: ";
    const string flightID = input();
    if (flightID == ESCAPE)
        return;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << string(20, ' ') << ">>>> ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "So ghe: ";
    int seatNumber;
    try {
        const auto temp = input();
        if (temp == ESCAPE)
            return;
        seatNumber = stoi(temp);
    } catch (exception e) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << string(20, ' ') << "Thong tin khong hop le, vui long kiem tra lai!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }

    if (!m_customerService->tryBookTicket(flightID, customerID, customerFullname, seatNumber)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << string(20, ' ') << "Thong tin khong hop le, vui long kiem tra lai!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    } else {

    }
    cout << string(20, ' ') << "(Enter)";
    cin.ignore();
    cin.get();
}

void MenuController::manageMenu() const {
    int option = -1;

    do {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
        cout << string(20, ' ') << "*****************************************\n";
        cout << string(20, ' ') << "*            QUAN LI CHUYEN BAY         *\n";
        cout << string(20, ' ') << "*****************************************\n\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        cout << string(20, ' ') << "1. Xu li dat ve\n";
        cout << string(20, ' ') << "2. Xu li huy ve\n";
        cout << string(20, ' ') << "3. Thong ke\n";
        cout << string(20, ' ') << "0. Tro ve\n\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << string(20, ' ') << ">>>> ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Xin nhap lua chon cua ban: ";

        auto tempInput = input();
        if (tempInput == ESCAPE)
            return;

        try {
            option = stoi(tempInput);
        } catch (exception e) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "Vui long nhap so!\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            cout << "(Enter)";
            cin.ignore();
            cin.get();
            continue;
        }

        switch (option) {
            case 1:
                handleTicketBooking();
                break;
            case 2:
                handleTicketCancelation();
                break;
            case 3:
                showStatistics();
                break;
            default: ;
        }
    } while (option != 0);
}

void MenuController::showAllTicketQueue() const {
    const int ticketIDWidth = 10, flightIDWidth = 20, customerIDWidth = 20, customerNameWidth = 20, seatNumberWidth = 10;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << string(20, ' ') << "*****************************************\n";
    cout << string(20, ' ') << "*            QUAN LI CHUYEN BAY         *\n";
    cout << string(20, ' ') << "*          (danh sach ve duoc dat)      *\n";
    cout << string(20, ' ') << "*****************************************\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << string(5, ' ') << string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << string(5, ' ') << left
        << setw(ticketIDWidth) << "Ma ve"
        << setw(flightIDWidth) << "Ma chuyen bay"
        << setw(customerIDWidth) << "Ma khach hang"
        << setw(customerNameWidth) << "Ten khach hang"
        << setw(seatNumberWidth) << "So ghe"
        << endl;
    cout<< string(5, ' ') << string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;

    if (m_ticketManager->getTicketQueueRepository().getList().empty()) {
        cout << string(5, ' ') << left
        << setw(ticketIDWidth) << "<none>"
        << setw(flightIDWidth) << "<none>"
        << setw(customerIDWidth) << "<none>"
        << setw(customerNameWidth) << "<none>"
        << setw(seatNumberWidth) << "<none>"
        << endl;
    } else {
        for (const auto& ticket : m_ticketManager->getTicketQueueRepository().getList()) {
            cout << string(5, ' ') << left
            << setw(ticketIDWidth) << ticket->getTicketID()
            << setw(flightIDWidth) << ticket->getFlightID()
            << setw(customerIDWidth) << ticket->getCustomerID()
            << setw(customerNameWidth) << ticket->getCustomerName()
            << setw(seatNumberWidth) << ticket->getSeatNumber()
            << endl;
        }
    }
    cout<< string(5, ' ') << string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << endl;
}

void MenuController::showAllTicket() const {
    const int ticketIDWidth = 10, flightIDWidth = 20, customerIDWidth = 20, customerNameWidth = 20, seatNumberWidth = 10;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << string(20, ' ') << "*****************************************\n";
    cout << string(20, ' ') << "*            QUAN LI CHUYEN BAY         *\n";
    cout << string(20, ' ') << "*      (danh sach ve dat thanh cong)    *\n";
    cout << string(20, ' ') << "*****************************************\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout<< string(5, ' ') << string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << string(5, ' ') << left
        << setw(ticketIDWidth) << "Ma ve"
        << setw(flightIDWidth) << "Ma chuyen bay"
        << setw(customerIDWidth) << "Ma khach hang"
        << setw(customerNameWidth) << "Ten khach hang"
        << setw(seatNumberWidth) << "So ghe"
        << endl;
    cout<< string(5, ' ') << string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;

    if (m_ticketManager->getTicketRepository().getAll().empty()) {
        cout << string(5, ' ') << left
        << setw(ticketIDWidth) << "<none>"
        << setw(flightIDWidth) << "<none>"
        << setw(customerIDWidth) << "<none>"
        << setw(customerNameWidth) << "<none>"
        << setw(seatNumberWidth) << "<none>"
        << endl;
    } else {
        for (const auto& ticket : m_ticketManager->getTicketRepository().getAll()) {
            cout << string(5, ' ') << left
            << setw(ticketIDWidth) << ticket->getTicketID()
            << setw(flightIDWidth) << ticket->getFlightID()
            << setw(customerIDWidth) << ticket->getCustomerID()
            << setw(customerNameWidth) << ticket->getCustomerName()
            << setw(seatNumberWidth) << ticket->getSeatNumber()
            << endl;
        }
    }
    cout<< string(5, ' ') << string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << endl;
}

void MenuController::showTicketByFlightID(const string& flightID) const {
    const auto flight = m_flightManager->findFlightByID(flightID);
    if (flight == m_flightManager->getFlightRepository().undefineFlight()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << string(20, ' ') << "Khong ton tai chuyen bay " << flightID << "!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }
    const auto tickets = m_ticketManager->findByFlightID(flightID);
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << string(20, ' ') << "*****************************************\n";
    cout << string(20, ' ') << "*            QUAN LI CHUYEN BAY         *\n";
    cout << string(20, ' ') << "*     (danh sach ve theo chuyen bay)    *\n";
    cout << string(20, ' ') << "*****************************************\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    if (tickets.empty()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << string(20, ' ') << "Khong co ve nao cho chuyen bay: " << flightID << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }

    const int ticketIDWidth = 10, flightIDWidth = 20, customerIDWidth = 20, customerNameWidth = 20, seatNumberWidth = 10;

    cout << string(25, ' ') << "VE BAY THEO MA CHUYEN BAY: " << flightID << endl;
    cout<< string(5, ' ') << string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << string(5, ' ') << left
        << setw(ticketIDWidth) << "Ma ve"
        << setw(flightIDWidth) << "Ma chuyen bay"
        << setw(customerIDWidth) << "Ma khach hang"
        << setw(customerNameWidth) << "Ten khach hang"
        << setw(seatNumberWidth) << "So ghe"
        << endl;
    cout<< string(5, ' ') << string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;

    for (auto& ticket : tickets) {
        cout << string(5, ' ') << left
        << setw(ticketIDWidth) << ticket->getTicketID()
        << setw(flightIDWidth) << ticket->getFlightID()
        << setw(customerIDWidth) << ticket->getCustomerID()
        << setw(customerNameWidth) << ticket->getCustomerName()
        << setw(seatNumberWidth) << ticket->getSeatNumber()
        << endl;
    }
    cout<< string(5, ' ') << string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << "(Enter)";
    cin.ignore();
    cin.get();
}

void MenuController::showAvailableSeatOfFlight(const string &flightID) const {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << string(20, ' ') << "*****************************************\n";
    cout << string(20, ' ') << "*            QUAN LI CHUYEN BAY         *\n";
    cout << string(20, ' ') << "*             (cac ghe hop le)          *\n";
    cout << string(20, ' ') << "*****************************************\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    const auto flight = m_flightManager->findFlightByID(flightID);
    if (flight == m_flightManager->getFlightRepository().undefineFlight()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << string(20, ' ') << "Khong ton tai chuyen bay co ID: " << flightID << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }

    if ((*flight)->getStatus() == FlightStatus::COMPLETED) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << string(20, ' ') << "CHUYEN BAY DA HOAN TAT!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }

    const auto seats = m_flightManager->getAvailableSeat(flightID);
    if (seats.empty()) {
        cout << string(20, ' ') << "Chuyen bay da het cho trong\n";
        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }

    cout << string(20, ' ') << "DANH SACH GHE TRONG CUA CHUYEN BAY: " << flightID << " la: " << seats.size() << endl;
    for (const auto i : seats)
        cout << string(20, ' ') << "[Ghe thu " << i << "]\n";

    cout << string(20, ' ') << "(Enter)";
    cin.ignore();
    cin.get();
}

void MenuController::showFlightQuantityOfAirplane(const string &airplaneID) const {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << string(20, ' ') << "*****************************************\n";
    cout << string(20, ' ') << "*            QUAN LI CHUYEN BAY         *\n";
    cout << string(20, ' ') << "*  (danh sach chuyen bay theo may bay)  *\n";
    cout << string(20, ' ') << "*****************************************\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    const auto flights = m_flightManager->findFlightQuantityOfAirplane(airplaneID);
    const auto airplane = m_flightManager->getAirplaneRepository().findByID(airplaneID);
    if (airplane == m_flightManager->getAirplaneRepository().undefineAirplane()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << string(20, ' ') << "Khong ton tai may bay " << airplaneID << "!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }
    if (flights.empty()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << string(20, ' ') << "May bay " << airplaneID << " khong co chuyen bay nao\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }

    const int flightIDWidth = 12;
    const int departureWidth = 20;
    const int destWidth = 16;
    const int statusWidth = 12;
    const int ticketWidth = 20;

    cout << string(20, ' ') << "CAC CHUYEN BAY CUA MAY BAY " << airplaneID << endl;
    cout<< string(5, ' ') << string(flightIDWidth + departureWidth + destWidth + statusWidth + ticketWidth, '-') << endl;
    cout<< string(5, ' ') << left
        << setw(flightIDWidth) << "Flight ID"
        << setw(departureWidth) << "Departure date"
        << setw(destWidth) << "Destination"
        << setw(statusWidth) << "Status"
        << setw(ticketWidth) << "Ticket "
        << endl;
    cout<< string(5, ' ') << string(flightIDWidth + departureWidth + destWidth + statusWidth + ticketWidth, '-') << endl;

    for (const auto flight : flights) {
        string status;
        switch (flight->getStatus()) {
            case FlightStatus::CANCELLED:
                status = "Huy chuyen";
                break;
            case FlightStatus::AVAILABLE:
                status = "Con ve";
                break;
            case FlightStatus::SOLD_OUT:
                status = "Het ve";
                break;
            case FlightStatus::COMPLETED:
                status = "Hoan tat";
                break;
        }
        cout<< string(5, ' ') << left
        << setw(flightIDWidth) << flight->getFlightID()
        << setw(departureWidth) << flight->getDepartureDate().toString()
        << setw(destWidth) << flight->getDestinationAirport()
        << setw(statusWidth) << status;
        bool isFirstLine = true;
        if (flight->getTickets().empty()) {
            cout << "<none>\n";
            continue;
        }
        for (const auto& ticketID : flight->getTickets()) {
            if (!isFirstLine)
                cout << ", ";
            cout << ticketID;
            isFirstLine = false;
        }
        cout << endl;
    }
    cout<< string(5, ' ') << string(flightIDWidth + departureWidth + destWidth + statusWidth + ticketWidth, '-') << endl;
    cout << "(Enter)";
    cin.ignore();
    cin.get();
}

void MenuController::handleTicketBooking() const {
    int option = -1;
    do {
        showAllTicketQueue();

        cout << string(20, ' ') << "1. Them ve\n";
        cout << string(20, ' ') << "2. Xoa ve\n";
        cout << string(20, ' ') << "0. Tro ve\n\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << string(20, ' ') << ">>>> ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Nhap lua chon: ";
        auto tempInput = input();

        // neu user nhan esc thi thoat
        if (tempInput == ESCAPE)
            return;

        // kiem tra thong tin user nhap co hop le???
        try {
            option = stoi(tempInput);
        } catch (exception e) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << string(20, ' ') << "Vui long nhap so!\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            cout << string(20, ' ') << "(Enter)";
            cin.ignore();
            cin.get();
            continue;
        }

        if (option != 1 && option != 2 && option != 0)
            continue;

        if (option == 0)
            continue;

        switch (option) {
            case 1: {
                const auto ticket = m_ticketManager->getTicketQueueRepository().front();
                if (ticket == m_ticketManager->getTicketQueueRepository().undefineTicket()) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << string(20, ' ') << "Chua co ve nao duoc dat!\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                } else {
                    m_ticketManager->addTicketFromQueue();
                }
                break;
            }
            case 2: {
                const auto ticket = m_ticketManager->getTicketQueueRepository().front();
                if (ticket == m_ticketManager->getTicketQueueRepository().undefineTicket()) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << string(20, ' ') << "Chua co ve nao duoc dat!\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                } else {
                    const string ticketID = ticket->getTicketID();
                    m_ticketManager->getTicketQueueRepository().pop();
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                    cout << string(20, ' ') << "Da xoa ve : " << ticketID << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                break;
            }
            default: {}
        }

        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
    } while (option != 0);
}

void MenuController::handleTicketCancelation() const {

    int option = -1;

    do {
        showAllTicket();
        cout << string(20, ' ') << "1. Xoa ve theo ma\n";
        cout << string(20, ' ') << "0. Tro ve\n\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << string(20, ' ') << ">>>> ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Nhap lua chon: ";

        auto tempInput = input();
        if (tempInput == ESCAPE)
            return;

        try {
            option = stoi(tempInput);
        } catch (exception e) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << string(20, ' ') << "Vui long nhap so!\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            cout << string(20, ' ') << "(Enter)";
            cin.ignore();
            cin.get();
            continue;
        }

        if (option == 0)
            continue;

        showAllTicket();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << string(20, ' ') << ">>>> ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Nhap ma ve: ";
        const string ticketID = input();
        if (ticketID == ESCAPE)
            return;
        const auto ticket = m_ticketManager->findByID(ticketID);
        if (ticket == m_ticketManager->getTicketRepository().undefineTicket()) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << string(20, ' ') << "Khong tim thay ve " << ticketID << "!\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        } else {
            m_ticketManager->removeTicket(ticketID);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            cout << string(20, ' ') << "Da xoa ve : " << ticketID << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
    } while (option != 0);
}

void MenuController::showStatistics() const {

    int option = -1;
    do {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
        cout << string(20, ' ') << "*****************************************\n";
        cout << string(20, ' ') << "*            QUAN LI CHUYEN BAY         *\n";
        cout << string(20, ' ') << "*                (Thong ke)             *\n";
        cout << string(20, ' ') << "*****************************************\n\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        cout << string(20, ' ') << "1. Danh sach khach cua 1 chuyen bay theo ma (ve)\n";
        cout << string(20, ' ') << "2. Danh sach ghe trong cua 1 chuyen bay theo ma\n";
        cout << string(20, ' ') << "3. So lan thuc hien chuyen bay cua 1 may bay theo ma\n";
        cout << string(20, ' ') << "0. Tro ve\n\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << string(20, ' ') << ">>>> ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Nhap lua chon: ";

        auto tempInput = input();
        if (tempInput == ESCAPE)
            return;

        try {
            option = stoi(tempInput);
        } catch (exception e) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << string(20, ' ') << "Vui long nhap so!\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            cout << string(20, ' ') << "(Enter)";
            cin.ignore();
            cin.get();
            continue;
        }

        if (option == 0)
            continue;

        switch (option) {
            case 1: {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                cout << string(20, ' ') << ">>>> ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                cout << "Nhap vao ma chuyen bay: ";
                const string flightID = input();
                if (flightID == ESCAPE)
                    return;

                showTicketByFlightID(flightID);
                break;
            }
            case 2: {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                cout << string(20, ' ') << ">>>> ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                cout << "Nhap vao ma chuyen bay: ";
                const string flightID = input();
                if (flightID == ESCAPE)
                    return;

                showAvailableSeatOfFlight(flightID);
                break;
            }
            case 3: {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                cout << string(20, ' ') << ">>>> ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                cout << "Nhap vao ma may bay: ";
                const string airplaneID = input();
                if (airplaneID == ESCAPE)
                    return;
                if (airplaneID.empty()) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << string(20, ' ') << "Ban chua nhap ma chuyen bay!\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    cout << string(20, ' ') << "(Enter)";
                    cin.ignore();
                    cin.get();
                    continue;
                }

                showFlightQuantityOfAirplane(airplaneID);
                break;
            }
            default: ;
        }
    } while (option != 0);
}

void MenuController::displayLoginLogo() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout<< left
        << string(20, ' ') << "*****************************************\n"
        << string(20, ' ') << "*         DANG  NHAP  HE  THONG         *\n"
        << string(20, ' ') << "*****************************************\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

string MenuController::inputHiddenPassword() {
    string password;
    char ch;

    while ((ch = _getch()) != '\r') { // '\r' = Enter
        if (ch == 27)
            return ESCAPE;
        if (ch == '\b') { // Xử lý Backspace
            if (!password.empty()) {
                // sleep(1000);
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            password.push_back(ch);
            cout << '*'; // Hiển thị dấu *
        }
    }
    cout << endl;
    return password;
}
string MenuController::input() {
    string res;
    char ch;

    while ((ch = _getch()) != '\r') { // '\r' = Enter
        if (ch == 27) // phim ESC = 27
            return ESCAPE;
        if (ch == '\b') { // Xử lý Backspace
            if (!res.empty()) {
                // sleep(1000);
                res.pop_back();
                cout << "\b \b";
            }
        } else {
            res.push_back(ch);
            cout << (char)ch;
        }
    }
    cout << endl;
    return res;
}

void MenuController::showLogin() const {
    int count = 0;
    while (count < 3) {
        system("cls");
        displayLoginLogo();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << string(20, ' ') << ">>>> ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout <<"Username: ";
        const string username = input();
        if (username == ESCAPE)
            return;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << string(20, ' ') << ">>>> ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Password: ";
        const string password = inputHiddenPassword();
        if (password == ESCAPE)
            return;

        // cout << m_authService->tryLogin(username, password) << endl;
        if (m_authService->tryLogin(username, password)) {
            manageMenu();
            return;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << endl;
        cout << string(20, ' ') << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
        cout << string(20, ' ') << "X  Tai khoan khong hop le!  X\n";
        cout << string(20, ' ') << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
        cout << string(20, ' ') << "Sai " << ++count << "/3 lan\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        if (count == 3)
            continue;
        cout << string(20, ' ') << "(Enter)";
        cin.ignore();
        cin.get();
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << string(20, ' ') << "Ban da nhap sai qua 3 lan, chung toi se thoat he thong!\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << string(20, ' ') << "(Enter de thoat khoi he thong!!!)";
    cin.ignore();
    cin.get();
}

void MenuController::run() const {
    int option = -1;
    do {
        mainMenu();
        auto o = input();
        if (o == "VK_ESCAPE"){
            return;
        }

        try {
            option = stoi(o);
            switch (option) {
                case 1:
                    flightListMenu();
                    cout << "(Enter)";
                    cin.ignore();
                    cin.get();
                    break;
                case 2:
                    bookTicketMenu();
                    break;
                case 3:
                    showLogin();
                    break;
                default: ;
            }
        } catch (exception e) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << endl;
            cout << string(20, ' ') << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
            cout << string(20, ' ') << "X  Vui long nhap cac lua chon hop le  X\n";
            cout << string(20, ' ') << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            cout << string(20, ' ') << "(Enter)";
            cin.ignore();
            cin.get();
        }
    } while (option != 0);
}
