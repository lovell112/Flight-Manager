#ifndef AIRPLANEMANAGER_MENUCONTROLLER_H
#define AIRPLANEMANAGER_MENUCONTROLLER_H
#include "../service/AuthService.h"
#include "../service/CustomerService.h"
#include "../service/TicketManager.h"
#include "../service/FlightManager.h"


class FlightManager;

class MenuController {
    CustomerService* m_customerService;
    AuthService* m_authService;
    FlightManager* m_flightManager;
    TicketManager* m_ticketManager;

    // const int

    void mainMenu();
    void flightListMenu();
    void bookTicketMenu();
    void manageMenu();
    void showAllTicketQueue();
    void showAllTicket();
    void showTicketByFlightID(const string&);
    void showAvailableSeatOfFlight(const string&) const;
    void showFlightQuantityOfAirplane(const string&);
    void handleTicketBooking();
    void handleTicketCancelation();
    void showStatistics();

    static void displayLoginLogo();

    static string inputHiddenPassword();
    static string input();
    void showLogin();
public:
    MenuController();
    ~MenuController();
    void run();
};


#endif //AIRPLANEMANAGER_MENUCONTROLLER_H