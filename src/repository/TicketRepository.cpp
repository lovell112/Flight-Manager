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
    m_tickets.push_back(new Ticket(ticket));
}

// xoa ve theo ID

void TicketRepository::remove(const string& ticketID) {
    auto it = findByID(ticketID);
    if (it != undefineTicket()) {
        delete *it;  // Giai phong bo nho
        m_tickets.erase(it);
    } else {
        cerr << "khong tim thay ve co ID: " << ticketID << endl;
    }
}

// tim ve theo ID
vector<Ticket*>::iterator TicketRepository::findByID(const string& id) {
    for (auto it = m_tickets.begin(); it != m_tickets.end(); ++it) {
        if ((*it)->getTicketID() == id) {
            return it;
        }
    }
    return undefineTicket(); // khong tim thay thi return
}

// lay toan bo danh sach vé
// ===============================
vector<Ticket*>& TicketRepository::getAll() {
    return m_tickets;
}

const vector<Ticket *>::iterator TicketRepository::undefineTicket() {
    return m_tickets.end();
}


// tai du lieu ve tu file ra
void TicketRepository::loadAllTickets() {

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

            m_tickets.clear();
            string ticketID, flightID, customerID, customerName, seatNumber;
            string line;
            getline(reader, line);
            stringstream spliter(line);
            getline(spliter, ticketID, '|');
            getline(spliter, flightID, '|');
            getline(spliter, customerID, '|');
            getline(spliter, customerName, '|');
            getline(spliter, seatNumber, '|');
            Ticket* ticket = new Ticket(ticketID, flightID, customerID, customerName, stoi(seatNumber));
            m_tickets.push_back(ticket);
            reader.close();
        }
    }

    // cout << "da tai " << m_tickets.size() << " ve tu file" << endl;
}

//
// luu toan bo ve ra file
//
void TicketRepository::saveAllTickets() {
    for (auto& ticket : m_tickets) {
        cout << ticket->toString() << endl;
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

    cout << "da luu toan bo ve ra file." << endl;
}



