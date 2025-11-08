//
// Created by HP on 05/11/2025.
//

#ifndef FLIGHTMANAGER_FLÌGHTREPOSITORY_H
#define FLIGHTMANAGER_FLÌGHTREPOSITORY_H
#include "../core/Ticket.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class TicketRepository {
    vector<Ticket*> m_tickets;
    const string PATH = "../data/ticket.txt";
public:
    TicketRepository();
    ~TicketRepository();
    void add(const Ticket&);
    void remove(const string&);
    vector<Ticket*>::iterator findByID(const string&);
    vector<Ticket*> findByDate(const string&);
    vector<Ticket*> findByDestination(const string&);
    vector<Ticket*>& getAll();
    void loadAllTickets();
    void saveAllTickets();
};


#endif //FLIGHTMANAGER_FLÌGHTREPOSITORY_H
