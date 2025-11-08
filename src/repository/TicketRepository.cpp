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
    Ticket* newTicket = new Ticket(ticket);
    m_tickets.push_back(newTicket);
}


// xoa ve theo ID

void TicketRepository::remove(const string& ticketID) {
    auto it = findByID(ticketID);
    if (it != m_tickets.end()) {
        delete *it;  // Giai phong bo nho
        m_tickets.erase(it);
    } else {
        cerr << "khong tim thay ve co ID: " << ticketID << endl;
    }
}

// tim ve theo ID
vector<Ticket*>::iterator TicketRepository::findByID(const string& id) {
    for (auto it = m_tickets.begin(); it != m_tickets.end(); ++it) {
        if ((*it)->getID() == id) {
            return it;
        }
    }
    return m_tickets.end(); // khong tim thay thi return
}


// tim ve theo ngay

vector<Ticket*> TicketRepository::findByDate(const string& date) {
    vector<Ticket*> result;
    for (auto ticket : m_tickets) {
        if (ticket->getDate() == date) {
            result.push_back(ticket);
        }
    }
    return result;
}


 //tim ve theo điem den

vector<Ticket*> TicketRepository::findByDestination(const string& destination) {
    vector<Ticket*> result;
    for (auto ticket : m_tickets) {
        if (ticket->getDestination() == destination) {
            result.push_back(ticket);
        }
    }
    return result;
}


// lay toan bo danh sach vé
// ===============================
vector<Ticket*>& TicketRepository::getAll() {
    return m_tickets;
}


// tai du lieu ve tu file ra

void TicketRepository::loadAllTickets() {
    ifstream inFile(PATH);
    if (!inFile) {
        cerr << "khong mo duoc file!" << endl;
        return;
    }

    m_tickets.clear();
    string id, date, destination;
  

    while (inFile >> id >> date >> destination) {
        Ticket* t = new Ticket(id, date, destination);
        m_tickets.push_back(t);
    }

    inFile.close();
    cout << "da tai " << m_tickets.size() << " ve tu file" << endl;
}

//
// luu toan bo ve ra file
//
void TicketRepository::saveAllTickets() {
    ofstream outFile(PATH);
    // kiem tra doc file
    if (!outFile) {
        cerr << "khong the mo duoc file ticket.txt!" << endl;
        return;
    }

    for (auto ticket : m_tickets) {
        outFile << ticket->getID() << " "
                << ticket->getDate() << " "
                << ticket->getDestination() << " " << endl;
    }

    outFile.close();
    cout << "da luu toan bo ve ra file." << endl;
}

}


