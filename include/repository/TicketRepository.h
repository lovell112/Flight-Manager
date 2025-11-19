//
// Created by HP on 05/11/2025.
//

#ifndef FLIGHTMANAGER_TICKETREPOSITORY_H
#define FLIGHTMANAGER_TICKETREPOSITORY_H
#include "../core/Ticket.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <vector>
using namespace std;

class TicketRepository {
    vector<Ticket*> m_tickets;
    const string FOLDER_PATH = "../data/tickets";
public:
    TicketRepository();
    ~TicketRepository();
    void add(const Ticket&);
    void remove(const string&);
    vector<Ticket*>::iterator findByID(const string&);
    [[nodiscard]] vector<Ticket*> findByFlightID(const string&) const;
    vector<Ticket*>& getAll();
    const vector<Ticket*>::iterator undefineTicket();
    void loadAllTickets();
    void saveAllTickets();
};


#endif //FLIGHTMANAGER_TICKETREPOSITORY_H
