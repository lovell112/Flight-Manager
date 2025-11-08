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

class FlightRepository {
    vector<Ticket*> m_tickets;
    const string PATH = "../data/ticket.txt";
public:
    TicketRepository();
    ~TicketRepository();
    void add(const Ticket& ticket);
    void remove(const string& ticketID);
    vector<Ticket*>::iterator findByID(const string& id);
    vector<Ticket*> findByDate(const string& date);
    vector<Ticket*> findByDestination(const string& destination);
    vector<Ticket*>& getAll();
    void loadAllTickets();
    void saveAllTickets();
};


#endif //FLIGHTMANAGER_FLÌGHTREPOSITORY_H
