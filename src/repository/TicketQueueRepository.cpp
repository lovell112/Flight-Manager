#include "../../include/repository/TicketQueueRepository.h"
#include <fstream>
#include <sstream>

TicketQueueRepository::TicketQueueRepository() {
    loadAllTickets();
}

TicketQueueRepository::~TicketQueueRepository() {
    loadAllTickets(); // cap nhat du lieu moi nhat
    saveAllTickets(); // auto save
    while (!m_tickets.empty()) {
        delete m_tickets.front();
        m_tickets.pop();
    }
}

void TicketQueueRepository::push(const Ticket &ticket) {
    loadAllTickets();
    m_tickets.push(new Ticket(ticket));
    saveAllTickets();
    loadAllTickets();
}

void TicketQueueRepository::pop() {
    loadAllTickets();
    if (m_tickets.empty())
        return;

    m_tickets.pop();
    saveAllTickets();
    loadAllTickets();
}

Ticket * TicketQueueRepository::front() {
    loadAllTickets();
    if (m_tickets.empty())
        return nullptr;

    return m_tickets.front();
}

queue<Ticket *> &TicketQueueRepository::getAll() {
    loadAllTickets();
    return m_tickets;
}

const Ticket* TicketQueueRepository::undefineTicket() {
    return nullptr;
}

void TicketQueueRepository::loadAllTickets() {
    ifstream reader(PATH);
    if (!reader.is_open()) {
        cerr << "Khong doc duoc file ticket_queue.txt\n";
        return;
    }

    while (!m_tickets.empty()) {
        delete m_tickets.front();
        m_tickets.pop();
    }

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

        m_tickets.push(new Ticket(ticketID, flightID, customerID, customerFullname, stoi(seatNumberString)));
    }
    reader.close();
}

void TicketQueueRepository::saveAllTickets() const {
    ofstream writer(PATH);

    if (!writer.is_open()) {
        cerr << "Khong ghi duoc file ticket_queue.txt\n";
        return;
    }

    queue<Ticket*> temp;

    while (!m_tickets.empty()) {
        writer << m_tickets.front()->toString() << endl;
        temp.push(m_tickets.front());
        m_tickets.pop()
    }

    writer.close();
}
