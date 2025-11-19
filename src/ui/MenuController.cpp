#include "../../include/ui/MenuController.h"
#include <iomanip>
#include <conio.h>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _HAS_STD_BYTE 0
#include <windows.h>

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
    cout << "1. Hien thi danh sach cac chuyen bay\n";
    cout << "2. Dat ve\n";
    cout << "3. Quan li\n";
    cout << "0. Thoat\n\n";
    cout << ">>>> Moi ban nhap lua chon: ";
}

void MenuController::airplaneListMenu() {
    const int flightIDWidth = 12;
    const int departureWidth = 20;
    const int destWidth = 16;
    const int statusWidth = 12;
    const int ticketWidth = 20;

    system("cls");
    cout<< left
        << setw(flightIDWidth) << "Flight ID"
        << setw(departureWidth) << "Departure date"
        << setw(destWidth) << "Destination"
        << setw(statusWidth) << "Status"
        << setw(ticketWidth) << "Ticket "
        << endl;
    cout<< string(flightIDWidth + departureWidth + destWidth + statusWidth + ticketWidth, '-') << endl;

    for (auto& flight : m_flightManager->getAllFlight()) {
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
        cout<< left
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
    cout << "(Enter)";
    cin.ignore();
    cin.get();
}

void MenuController::bookTicketMenu() {
    system("cls");
    string customerID, customerFullname, flightID;
    int seatNumber;
    cout << "Vui long dien day du cac thong tin sau:\n";
    cout << left << setw(20) << ">>>> CCCD: "; cin >> customerID;
    cin.ignore();
    cout << left << setw(20) << ">>>> Ho ten: "; getline(cin, customerFullname);
    cout << left << setw(20) << ">>>> Ma chuyen bay: "; cin >> flightID;
    cout << left << setw(20) << ">>>> So ghe: "; cin >> seatNumber;
    if (!m_customerService->tryBookTicket(flightID, customerID, customerFullname, seatNumber))
        cout << "Thong tin khong hop le, vui long kiem tra lai!\n";
    cout << "(Enter)";
    cin.ignore();
    cin.get();
}

void MenuController::manageMenu() {
    int option;

    do {
        system("cls");
        cout << "1. Xu li dat ve\n";
        cout << "2. Xu li huy ve\n";
        cout << "3. Thong ke\n";
        cout << "0. Tro ve\n\n";
        cout << ">>>> Xin nhap lua chon cua ban: ";
        cin >> option;

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
        }
    } while (option != 0);
}

void MenuController::showAllTicketQueue() {
    const int ticketIDWidth = 10, flightIDWidth = 20, customerIDWidth = 20, customerNameWidth = 20, seatNumberWidth = 10;

    system("cls");
    cout<< string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << left
        << setw(ticketIDWidth) << "Ma ve"
        << setw(flightIDWidth) << "Ma chuyen bay"
        << setw(customerIDWidth) << "Ma khach hang"
        << setw(customerNameWidth) << "Ten khach hang"
        << setw(seatNumberWidth) << "So ghe"
        << endl;
    cout<< string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;

    for (const auto& ticket : m_ticketManager->getTicketQueueRepository().getAll()) {
        cout << left
        << setw(ticketIDWidth) << ticket->getTicketID()
        << setw(flightIDWidth) << ticket->getFlightID()
        << setw(customerIDWidth) << ticket->getCustomerID()
        << setw(customerNameWidth) << ticket->getCustomerName()
        << setw(seatNumberWidth) << ticket->getSeatNumber()
        << endl;
    }
    cout<< string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << endl;
}

void MenuController::showAllTicket() {
    const int ticketIDWidth = 10, flightIDWidth = 20, customerIDWidth = 20, customerNameWidth = 20, seatNumberWidth = 10;

    system("cls");
    cout<< string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << left
        << setw(ticketIDWidth) << "Ma ve"
        << setw(flightIDWidth) << "Ma chuyen bay"
        << setw(customerIDWidth) << "Ma khach hang"
        << setw(customerNameWidth) << "Ten khach hang"
        << setw(seatNumberWidth) << "So ghe"
        << endl;
    cout<< string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;

    for (const auto& ticket : m_ticketManager->getTicketRepository().getAll()) {
        cout << left
        << setw(ticketIDWidth) << ticket->getTicketID()
        << setw(flightIDWidth) << ticket->getFlightID()
        << setw(customerIDWidth) << ticket->getCustomerID()
        << setw(customerNameWidth) << ticket->getCustomerName()
        << setw(seatNumberWidth) << ticket->getSeatNumber()
        << endl;
    }
    cout<< string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << endl;
}

void MenuController::showTicketByFlightID(const string& flightID) {
    auto tickets = m_ticketManager->findByFlightID(flightID);
    system("cls");
    if (tickets.empty()) {
        cout << "Khong co ve nao cho chuyen bay: " << flightID << endl;
        cout << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }

    const int ticketIDWidth = 10, flightIDWidth = 20, customerIDWidth = 20, customerNameWidth = 20, seatNumberWidth = 10;

    cout << setw(40) << "VE BAY THEO MA CHUYEN BAY: " << flightID << endl;
    cout<< string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << left
        << setw(ticketIDWidth) << "Ma ve"
        << setw(flightIDWidth) << "Ma chuyen bay"
        << setw(customerIDWidth) << "Ma khach hang"
        << setw(customerNameWidth) << "Ten khach hang"
        << setw(seatNumberWidth) << "So ghe"
        << endl;
    cout<< string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;

    for (auto& ticket : tickets) {
        cout << left
        << setw(ticketIDWidth) << ticket->getTicketID()
        << setw(flightIDWidth) << ticket->getFlightID()
        << setw(customerIDWidth) << ticket->getCustomerID()
        << setw(customerNameWidth) << ticket->getCustomerName()
        << setw(seatNumberWidth) << ticket->getSeatNumber()
        << endl;
    }
    cout<< string(ticketIDWidth + flightIDWidth + customerIDWidth + customerNameWidth + seatNumberWidth, '-') << endl;
    cout << endl;
    cout << "(Enter)";
    cin.ignore();
    cin.get();
}

void MenuController::showAvailableSeatOfFlight(const string &flightID) {
    system("cls");
    auto seats = m_flightManager->getAvailableSeat(flightID);
    if (seats.empty()) {
        cout << " Chuyen bay da het cho trong\n";
        cout << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }

    cout << setw(30) << "DANH SACH GHE TRONG CUA CHUYEN BAY: " << flightID << " la: " << seats.size() << endl;
    for (auto i : seats)
        cout << "[Ghe thu " << i << "]\n";

    cout << "(Enter)";
    cin.ignore();
    cin.get();
}

void MenuController::showFlightQuantityOfAirplane(const string &airplaneID) {
    system("cls");

    auto flights = m_flightManager->findFlightQuantityOfAirplane(airplaneID);
    if (flights.empty()) {
        cout << "May bay " << airplaneID << " khong co chuyen bay naof\n";
        cout << "(Enter)";
        cin.ignore();
        cin.get();
        return;
    }

    const int flightIDWidth = 12;
    const int departureWidth = 20;
    const int destWidth = 16;
    const int statusWidth = 12;
    const int ticketWidth = 20;

    cout << "CAC CHUYEN BAY CUA MAY BAY " << airplaneID << endl;
    cout<< string(flightIDWidth + departureWidth + destWidth + statusWidth + ticketWidth, '-') << endl;
    cout<< left
        << setw(flightIDWidth) << "Flight ID"
        << setw(departureWidth) << "Departure date"
        << setw(destWidth) << "Destination"
        << setw(statusWidth) << "Status"
        << setw(ticketWidth) << "Ticket "
        << endl;
    cout<< string(flightIDWidth + departureWidth + destWidth + statusWidth + ticketWidth, '-') << endl;

    for (auto flight : flights) {
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
        cout<< left
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
    cout << "(Enter)";
    cin.ignore();
    cin.get();
}


void MenuController::handleTicketBooking() {
    int option;
    do {
        showAllTicketQueue();

        cout << "1. Them ve theo ma\n";
        cout << "0. Tro ve\n\n";
        cout << ">>>> Nhap lua chon: ";
        cin >> option;

        if (option == 0)
            continue;

        showAllTicketQueue();
        cout << ">>>> Nhap ma ve: ";
        string ticketID;
        cin >> ticketID;
        auto ticket = m_ticketManager->getTicketQueueRepository().findByID(ticketID);
        m_ticketManager->addTicket(*(*ticket));
        cout << ">>>> Da chap nhan ve : " << ticketID << endl;
        cout << "(Enter)";
        cin.ignore();
        cin.get();

    } while (option != 0);
}

void MenuController::handleTicketCancelation() {

    int option;

    do {
        showAllTicket();
        cout << "1. Xoa ve theo ma\n";
        cout << "0. Tro ve\n\n";
        cout << ">>>> Nhap lua chon: ";
        cin >> option;

        if (option == 0)
            continue;

        showAllTicket();
        cout << ">>>> Nhap ma ve: ";
        string ticketID;
        cin >> ticketID;
        auto ticket = m_ticketManager->findByID(ticketID);
        m_ticketManager->removeTicket((*ticket)->getTicketID());
        cout << "Da xoa ve : " << ticketID << endl;
        cout << "(Enter)";
        cin.ignore();
        cin.get();
    } while (option != 0);
}

void MenuController::showStatistics() {

    int option;
    do {
        system("cls");
        cout << "1. Danh sach khach cua 1 chuyen bay theo ma (ve)\n";
        cout << "2. Danh sach ghe trong cua 1 chuyen bay theo ma\n";
        cout << "3. So lan thuc hien chuyen bay cua 1 may bay theo ma\n";
        cout << "0. Tro ve\n\n";
        cout << ">>>> Nhap lua chon: ";
        cin >> option;

        if (option == 0)
            continue;

        switch (option) {
            case 1: {
                cout << ">>>> Nhap vao ma chuyen bay: ";
                string flightID;
                cin >> flightID;
                showTicketByFlightID(flightID);
                break;
            }
            case 2: {
                cout << ">>>> Nhap vao ma chuyen bay: ";
                string flightID;
                cin >> flightID;
                showAvailableSeatOfFlight(flightID);
                break;
            }
            case 3: {
                cout << ">>>> Nhap vao ma may bay: ";
                string airplaneID;
                cin >> airplaneID;
                showFlightQuantityOfAirplane(airplaneID);
                break;
            }
        }
    } while (option != 0);
}

void MenuController::displayLoginLogo() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout<< left
        << string(30, ' ') << "***********************************\n"
        << string(30, ' ') << "*      DANG  NHAP  HE  THONG      *\n"
        << string(30, ' ') << "***********************************\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

string MenuController::inputHiddenPassword() {
    string password;
    char ch;

    while ((ch = _getch()) != '\r') { // '\r' = Enter
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

void MenuController::showLogin() {
    string username;
    int count = 0;
    while (count < 3) {
        system("cls");
        displayLoginLogo();
        cout << string(33, ' ') << ">>>> Username: ";
        cin >> username;
        cout << string(33, ' ') << ">>>> Password: ";
        string password = inputHiddenPassword();

        cout << m_authService->tryLogin(username, password) << endl;
        if (m_authService->tryLogin(username, password)) {
            manageMenu();
            return;
        }

        cout << "Tai khoan khong hop le!\n";
        count++;
        cout << "(Enter)";
        cin.ignore();
        cin.get();
    }

    cout << "Ban da nhap sai qua 3 lan, chung toi se thoat he thong!\n";
    cout << "(Enter de thoat khoi he thong!!!)";
    cin.get();
}

void MenuController::run() {
    int option;
    do {
        mainMenu();
        cin >> option;
        switch (option) {
            case 1:
                airplaneListMenu();
                break;
            case 2:
                bookTicketMenu();
                break;
            case 3:
                showLogin();
                break;
        }
    } while (option != 0);
}