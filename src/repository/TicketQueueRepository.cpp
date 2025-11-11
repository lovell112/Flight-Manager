#include "../../include/repository/TicketQueueRepository.h"
#include <fstream>
#include <sstream>

TicketQueueRepository::TicketQueueRepository() {
    loadAllTickets();
}

TicketQueueRepository::~TicketQueueRepository() {
    loadAllTickets(); // cap nhat du lieu moi nhat
    saveAllTickets(); // auto save
    for (auto& ticket : m_tickets) {
        delete ticket;
    }
    m_tickets.clear();
}

void TicketQueueRepository::add(const Ticket &ticket) {
    loadAllTickets();
    m_tickets.push_back(new Ticket(ticket));
    saveAllTickets();
    loadAllTickets();
}

void TicketQueueRepository::remove(const string &ticketID) {
    loadAllTickets();
    auto ticket = findByID(ticketID);
    if (ticket == undefineTicket())
        return;
    delete *ticket;
    m_tickets.erase(ticket);
    saveAllTickets();
    loadAllTickets();
}

void TicketQueueRepository::pop() {
    loadAllTickets();
    if (m_tickets.empty())
        return;

    m_tickets.erase(m_tickets.end()-1);
    saveAllTickets();
    loadAllTickets();
}


vector<Ticket *>::iterator TicketQueueRepository::findByID(const string &ticketID) {
    loadAllTickets();
    for (auto ticket = m_tickets.begin(); ticket != m_tickets.end(); ticket++) {
        if ((*ticket)->getTicketID() == ticketID)
            return ticket;
    }
    return undefineTicket();
}

vector<Ticket *> &TicketQueueRepository::getAll() {
    loadAllTickets();
    return m_tickets;
}

const vector<Ticket *>::iterator TicketQueueRepository::undefineTicket() {
    loadAllTickets();
    return m_tickets.end();
}

void TicketQueueRepository::loadAllTickets() {
    ifstream reader(PATH);
    if (!reader.is_open()) {
        cerr << "Khong doc duoc file ticket_queue.txt\n";
        return;
    }

    for (auto& ticket : m_tickets)
        delete ticket;
    m_tickets.clear();

    string line;
    while (getline(reader, line)) {
        if (line.empty())
            continue;

        string ticketID, flightID, customerID, customerFullname, seatNumberString;
        stringstream spliter(line);
        getline(spliter, ticketID, '|');
        getline(spliter, flightID, '|');
        getline(spliter, customerID, '|');
        getline(spliter, customerFullname, '|');
        getline(spliter, seatNumberString, '|');

        m_tickets.push_back(new Ticket(ticketID, flightID, customerID, customerFullname, stoi(seatNumberString)));
    }
    reader.close();
}

void TicketQueueRepository::saveAllTickets() const {
    ofstream writer(PATH);

    if (!writer.is_open()) {
        cerr << "Khong ghi duoc file ticket_queue.txt\n";
        return;
    }

    for (auto& ticket : m_tickets)
        writer << ticket->toString() << endl;

    writer.close();
}
