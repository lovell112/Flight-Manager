#ifndef FLIGHTMANAGER_TICKETQUEUE_H
#define FLIGHTMANAGER_TICKETQUEUE_H
#include "../core/Ticket.h"
#include <vector>
using namespace std;

class TicketQueueRepository {
    vector<Ticket*> m_tickets;
    const string PATH = "../data/ticket_queue.txt";
public:
    TicketQueueRepository();
    ~TicketQueueRepository();
    void add(const Ticket&);
    void remove(const string&);
    void pop();
    vector<Ticket*>::iterator front();
    vector<Ticket*>::iterator findByID(const string&);
    vector<Ticket*>& getAll();
    const vector<Ticket*>::iterator undefineTicket();
    void loadAllTickets();
    void saveAllTickets() const;
};


#endif //FLIGHTMANAGER_TICKETQUEUE_H