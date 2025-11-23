//
// Created by HP on 05/11/2025.
//

#ifndef FLIGHTMANAGER_TICKETREPOSITORY_H
#define FLIGHTMANAGER_TICKETREPOSITORY_H
#include "../core/Ticket.h"
#include "../datastructures/List.hpp"
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
using namespace std;

class TicketRepository {
    List<Ticket*> m_tickets;
    const string FOLDER_PATH = "../data/tickets";
public:
    TicketRepository();
    ~TicketRepository();
    void add(const Ticket&);
    void remove(const string&);
    Ticket** findByID(const string&);
    [[nodiscard]] List<Ticket*> findByFlightID(const string&) const;
    List<Ticket*>& getAll();

    Ticket **undefineTicket();
    void loadAllTickets();
    void saveAllTickets() const;
};


#endif //FLIGHTMANAGER_TICKETREPOSITORY_H
