#ifndef FLIGHTMANAGER_TICKETQUEUE_H
#define FLIGHTMANAGER_TICKETQUEUE_H

#include "../core/Ticket.h"
#include "../datastructures/Queue.hpp"
#include <vector>
using namespace std;

class TicketQueueRepository {
    Queue<Ticket*> m_tickets;
    const string PATH = "../data/ticket_queue.txt";
public:
    TicketQueueRepository();
    ~TicketQueueRepository();
    void push(const Ticket&);
    void pop();
    [[nodiscard]] Ticket* front();
    Queue<Ticket*>& getAll();

    vector<Ticket *> getList();

    const Ticket* undefineTicket();
    void loadAllTickets();
    void saveAllTickets() const;
};


#endif //FLIGHTMANAGER_TICKETQUEUE_H