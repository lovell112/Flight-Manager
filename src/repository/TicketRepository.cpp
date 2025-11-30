//
// Created by HP on 05/11/2025.
//

#include "../../include/repository/TicketRepository.h"
TicketRepository::TicketRepository() {
    loadAllTickets();
}

TicketRepository::~TicketRepository() {
    saveAllTickets();  // auto save truoc khi huy

    //delete tat ca tickets
    for (auto ticket : m_tickets) {
        delete ticket;
    }
    m_tickets.clear();
}
    // them ve vao danh sach
void TicketRepository::add(const Ticket& ticket) {
    m_tickets.add(new Ticket(ticket));
    saveAllTickets();
    loadAllTickets();
}


// xoa ve theo ID

void TicketRepository::remove(const string& ticketID) {
    if (auto it = findByID(ticketID); it != undefineTicket()) {
        delete *it;  // Giai phong bo nho
        m_tickets.remove(it);
        filesystem::remove(FOLDER_PATH+"/"+ticketID);
    }
    saveAllTickets();
    loadAllTickets();
}

bool TicketRepository::contains(Ticket *const ticket) const {
    return m_tickets.contains(ticket);
}

// tim ve theo ID
Ticket** TicketRepository::findByID(const string& id) {
    loadAllTickets();
    for (auto& ticket : m_tickets) {
        if (ticket->getTicketID() == id) {
            return &ticket;
        }
    }
    return undefineTicket(); // khong tim thay thi return
}

List<Ticket *> TicketRepository::findByFlightID(const string &flightID) const {
    List<Ticket*> res;
    for (auto ticket : m_tickets) {
        if (ticket->getFlightID() == flightID)
            res.add(ticket);
    }

    return res;
}

// lay toan bo danh sach vé
// ===============================
List<Ticket*>& TicketRepository::getAll() {
    loadAllTickets();
    return m_tickets;
}

Ticket **TicketRepository::undefineTicket() {
    loadAllTickets();
    return m_tickets.end();
}

// tai du lieu ve tu file ra
void TicketRepository::loadAllTickets() {

    // don dep du lieu cu de load du lieu moi len
    if (!m_tickets.empty()) {
        for (auto& ticket : m_tickets)
            delete ticket;
        m_tickets.clear();
    }

    // truy cap vao thu muc, doc tung file mot
    for (auto& entry : filesystem::directory_iterator(FOLDER_PATH)) {
        // chi lay file
        if (entry.is_regular_file()) {
            // const string PATH = FOLDER_PATH + "/" + entry.path().filename().string();
            const string PATH = entry.path().string();
            ifstream reader(PATH);
            if (!reader.is_open()) {
                cerr << "khong mo duoc file ticket!" << endl;
                return;
            }

            string ticketID, flightID, customerID, customerName, seatNumber;
            string line;
            getline(reader, line);
            stringstream spliter(line);
            getline(spliter, ticketID, '|');
            getline(spliter, flightID, '|');
            getline(spliter, customerID, '|');
            getline(spliter, customerName, '|');
            getline(spliter, seatNumber, '|');
            auto ticket = new Ticket(ticketID, flightID, customerID, customerName, stoi(seatNumber));
            m_tickets.add(ticket);
            reader.close();
        }
    }

    // cout << "da tai " << m_tickets.size() << " ve tu file" << endl;
}

//
// luu toan bo ve ra file
//
void TicketRepository::saveAllTickets() const {

    for (const auto& ticket : m_tickets) {
        const string PATH = FOLDER_PATH + "/" + ticket->getTicketID();
        ofstream writer(PATH);
        // kiem tra doc file
        if (!writer) {
            cerr << "khong the mo duoc file ticket.txt!" << endl;
            return;
        }

        writer << ticket->toString();

        writer.close();
    }
}
