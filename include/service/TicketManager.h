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

    void saveData() const;
    void loadData() const;
public:
    TicketManager();
    ~TicketManager();
    void addTicketFromQueue() const;
    void removeTicketQueue() const;
    void removeTicket(const string&) const;
    List<Ticket*> findByDate(const string&) const;
    Ticket** findByID(const string&) const;
    List<Ticket*> findByDestination(const string&) const;
    List<Ticket*> findByFlightID(const string&) const;
    TicketRepository& getTicketRepository() const;
    FlightRepository& getFlightRepository() const;
    AirplaneRepository& getAirplaneRepository() const;
    TicketQueueRepository& getTicketQueueRepository() const;
};
#endif //AIRPLANEMANAGER_TICKETMANAGER_H
