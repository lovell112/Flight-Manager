#ifndef AIRPLANEMANAGER_TICKETMANAGER_H
#define AIRPLANEMANAGER_TICKETMANAGER_H
#include <queue>

#include "../repository/FlightRepository.h"
#include "../repository/TicketRepository.h"
#include "../repository/AirplaneRepository.h"
#include "../repository/TicketQueueRepository.h"
#include "CustomerService.h"

class TicketManager {
    TicketRepository* m_ticketRepository;
    FlightRepository* m_flightRepository;
    AirplaneRepository* m_airplaneRepository;
    TicketQueueRepository* m_ticketQueueRepository;
    CustomerRepository* m_customerRepository;

    void saveData();
    void loadData();
public:
    TicketManager();
    ~TicketManager();
    void addTicketFromQueue();
    void removeTicket(const string&);
    vector<Ticket*> findByDate(const string&);
    vector<Ticket*>::iterator findByID(const string&);
    vector<Ticket*> findByDestination(const string&);
    vector<Ticket*> findByFlightID(const string&);
    TicketRepository& getTicketRepository();
    FlightRepository& getFlightRepository();
    AirplaneRepository& getAirplaneRepository();
    TicketQueueRepository& getTicketQueueRepository();
};
#endif //AIRPLANEMANAGER_TICKETMANAGER_H
