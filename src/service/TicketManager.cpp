//
// Created by HP on 05/11/2025.
//

#include "../../include/service/TicketManager.h"
TicketManager::TicketManager() {
    m_flightRepository = new FlightRepository();
    m_ticketRepository = new TicketRepository();
    m_customerService = new CustomerService();
}

// giai phong bo nho
TicketManager::~TicketManager() {
    delete m_flightRepository;
    delete m_ticketRepository;
    delete m_customerService;
}


bool TicketManager::tryBookTicket(const string& flightID, const string& customerID, int seatNumber) {
    // Kiem tra chuyen bay co ton tai khong
    Flight* flight = m_flightRepository->findByID(flightID);
    if (!flight) {
        cout << "Khong tim thay chuyen bay voi ID: " << flightID << endl;
        return false; // khong thi return
    }

    // Kiem tra khach hang co ton tai khong
    Customer* customer = m_customerService->findByID(customerID);
    if (!customer) {
        cout << "Khong tim thay khach hang voi ID: " << customerID << endl;
        return false;
    }

    // kiem tra ghe trong khong
    if (!flight->isSeatAvailable(seatNumber)) {
        cout << "Ghe da duoc dat!" << endl;
        return false;
    }

    // tao ve moi va them vao repo
    Ticket* newTicket = new Ticket(flightID, customerID, customer->getName(), seatNumber);
    m_ticketRepository->addTicket(newTicket);

    //cap nhat trang thai ghe
    flight->bookSeat(seatNumber);

    cout << "Dat ve thanh cong cho khach: " << customer->getName() << endl;
    return true;
}


bool TicketManager::tryCancelTicket(const string& ticketID) {
    // tim ve
    Ticket* ticket = m_ticketRepository->findByID(ticketID);
    if (!ticket) {
        cout << "Khong tim thay ve voi ID: " << ticketID << endl;
        return false;
    }

    // lay thong tin chuyen bay de mo lai ghe
    Flight* flight = m_flightRepository->findByID(ticket->getFlightID());
    if (flight) {
        flight->cancelSeat(ticket->getSeatNumber());
    }

    // Xoa ve khoi repository
    m_ticketRepository->removeTicket(ticketID);

    cout << "Huy ve thanh cong: " << ticketID << endl;
    return true;
}


vector<Ticket*>& TicketManager::findByDate(const string& date) {
    return m_ticketRepository->findByDate(date);
}


vector<Ticket*>::iterator TicketManager::findByID(const string& ticketID) {
    return m_ticketRepository->findIteratorByID(ticketID);
}

vector<Ticket*>& TicketManager::findByDestination(const string& destination) {
    return m_ticketRepository->findByDestination(destination);
}
