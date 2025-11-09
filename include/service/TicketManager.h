//
// Created by HP on 05/11/2025.
//

#ifndef AIRPLANEMANAGER_TICKETMANAGER_H
#define AIRPLANEMANAGER_TICKETMANAGER_H


class TicketManager {
     FlightRepository* m_flightRepository;
    TicketRepository* m_ticketRepository;
    CustomerService* m_customerService;

public:
    TicketManager();
    ~TicketManager();
    bool tryBookTicket(const string&, const string&, int);
    bool tryCancelTicket(const string&);
    vector<Ticket*>& findByDate(const string&);
    vector<Ticket*>::iterator findByID(const string&);
    vector<Ticket*>& findByDestination(const string&);
};
#endif //AIRPLANEMANAGER_TICKETMANAGER_H
