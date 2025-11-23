#ifndef AIRPLANEMANAGER_MENUCONTROLLER_H
#define AIRPLANEMANAGER_MENUCONTROLLER_H
#include "../service/AuthService.h"
#include "../service/CustomerService.h"
#include "../service/TicketManager.h"
#include "../service/FlightManager.h"


class FlightManager;

class MenuController {
    static string ESCAPE;
    CustomerService* m_customerService;
    AuthService* m_authService;
    FlightManager* m_flightManager;
    TicketManager* m_ticketManager;

    // const int

    static void mainMenu();
    void flightListMenu() const;
    void bookTicketMenu() const;
    void manageMenu() const;
    void showAllTicketQueue() const;
    void showAllTicket() const;
    void showTicketByFlightID(const string&) const;
    void showAvailableSeatOfFlight(const string&) const;
    void showFlightQuantityOfAirplane(const string&) const;
    void handleTicketBooking() const;
    void handleTicketCancelation() const;
    void showStatistics() const;

    static void displayLoginLogo();

    static string inputHiddenPassword();
    static string input();
    void showLogin() const;
public:
    MenuController();
    ~MenuController();
    void run() const;
};
#endif //AIRPLANEMANAGER_MENUCONTROLLER_H