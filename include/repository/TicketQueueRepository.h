#ifndef FLIGHTMANAGER_TICKETQUEUE_H
#define FLIGHTMANAGER_TICKETQUEUE_H
#include <queue>

#include "../core/Ticket.h"
#include <vector>
using namespace std;

class TicketQueueRepository {
    queue<Ticket*> m_tickets;
    const string PATH = "../data/ticket_queue.txt";
public:
    TicketQueueRepository();
    ~TicketQueueRepository();
    void push(const Ticket&);
    void pop();
    [[nodiscard]] Ticket* front();
    queue<Ticket*>& getAll();

    static const Ticket* undefineTicket();
    void loadAllTickets();
    void saveAllTickets() const;
};


#endif //FLIGHTMANAGER_TICKETQUEUE_H