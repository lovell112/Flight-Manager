#include <filesystem>
#include <iostream>
#include "include/repository/AirplaneRepository.h"
#include "include/repository/CustomerRepository.h"
#include "include/repository/FlightRepository.h"
#include "include/repository/TicketRepository.h"
#include "include/service/AuthService.h"
int main() {
    AirplaneRepository* airRepo = new AirplaneRepository();
    CustomerRepository* cusRepo = new CustomerRepository();
    FlightRepository* flightRepo = new FlightRepository();
    TicketRepository* ticketRepo = new TicketRepository();

    airRepo->add(Airplane("VN001", 10));
    cout << (*airRepo->findByID("VN001"))->toString() << endl;

    // ticketRepo->add(Ticket("T001", "VN002", "0928733372", "Tran Nhi Nho", 8));
    // ticketRepo->add(Ticket("T002", "VN003", "0922736398", "Tran Nho Nha", 9));
    // ticketRepo->add(Ticket("T003", "VN003", "0928722222", "Tran Thanh Nha", 4));
    // ticketRepo->add(Ticket("T004", "VN003", "0928736372", "Tran Nhi Nhanh", 7));
    auto it = ticketRepo->findByID("T003");
    if (it != ticketRepo->undefineTicket())
        cout << (*it)->toString() << endl;
    else
        cout << "khong ton tai\n";
    delete airRepo;
    delete cusRepo;
    delete flightRepo;
    delete ticketRepo;
    return 0;
}