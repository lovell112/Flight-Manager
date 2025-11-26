#ifndef FLIGHTMANAGER_CUSTOMERSERVICE_H
#define FLIGHTMANAGER_CUSTOMERSERVICE_H

#include "../repository/CustomerRepository.h"
#include <vector>

#include "../repository/AirplaneRepository.h"
#include "../repository/FlightRepository.h"
#include "../repository/TicketQueueRepository.h"
#include "../repository/TicketRepository.h"
class TicketRepository;
using namespace std;

class CustomerService {
private:
    TicketRepository* m_ticketRepository;
    CustomerRepository* m_customerRepository;
    FlightRepository* m_flightRepository;
    AirplaneRepository* m_airplaneRepository;
    TicketQueueRepository* m_ticketQueueRepository;

public:
    CustomerService();
    ~CustomerService();

    void addCustomer(const Customer&) const;
    void removeCustomer(const string&) const;

    bool tryBookTicket(const string&, const string&, const string&, int) const;
    // bool tryCancelTicket(const string&, const string&);

    vector<Customer*>::iterator findCustomerByID(const string&) const;

    List<Customer *> getAll() const;

    Customer **undefineCustomer() const;
};

#endif //FLIGHTMANAGER_CUSTOMERSERVICE_H
