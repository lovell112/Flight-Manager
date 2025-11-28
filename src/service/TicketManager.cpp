#include "../../include/service/TicketManager.h"

void TicketManager::saveData() const {
    m_ticketRepository->saveAllTickets();
    m_flightRepository->saveAllFlights();
    m_airplaneRepository->saveAllAirplanes();
    m_ticketQueueRepository->saveAllTickets();
    m_customerRepository->saveAllCustomers();
}
void TicketManager::loadData() const {
    m_ticketRepository->loadAllTickets();
    m_flightRepository->loadAllFlights();
    m_airplaneRepository->loadAllAirplanes();
    m_ticketQueueRepository->loadAllTickets();
    m_customerRepository->loadAllCustomers();
}

TicketManager::TicketManager() {
    m_ticketRepository = new TicketRepository();
    m_flightRepository = new FlightRepository();
    m_airplaneRepository = new AirplaneRepository();
    m_ticketQueueRepository = new TicketQueueRepository();
    m_customerRepository = new CustomerRepository();
}

// giai phong bo nho
TicketManager::~TicketManager() {
    delete m_ticketRepository;
    delete m_flightRepository;
    delete m_airplaneRepository;
    delete m_ticketQueueRepository;
    delete m_customerRepository;
}

bool TicketManager::addTicketFromQueue() const {
    auto ticket = *m_ticketQueueRepository->front();
    if (m_ticketRepository->contains(&ticket)) {
        m_ticketQueueRepository->pop(); // delete ve khoi hang doi
        return false;
    }
    m_ticketRepository->add(ticket);

    const auto flight = m_flightRepository->findByID(m_ticketQueueRepository->front()->getFlightID());
    const auto airplane = m_airplaneRepository->findByID((*flight)->getAirplaneID());
    (*flight)->addTicket(m_ticketQueueRepository->front()->getTicketID());
    (*airplane)->bookSeat(m_ticketQueueRepository->front()->getSeatNumber());

    m_ticketQueueRepository->pop(); // delete ve khoi hang doi
    // m_customerRepository->remove(ticket.getCustomerID()); // delete khoi hang doi khach cho mua

    saveData();
    loadData();
    return true;
}

void TicketManager::removeTicketQueue() const {
    m_ticketQueueRepository->pop();
    saveData();
    loadData();
}

void TicketManager::removeTicket(const string &ticketID) const {
    const auto ticket = m_ticketRepository->findByID(ticketID);
    if (ticket == m_ticketRepository->undefineTicket()) {
        // cout << string(20, ' ') << "Khong ton tai ve : " << ticketID << endl;
        return;
    }

    const auto flight = m_flightRepository->findByID((*ticket)->getFlightID());
    if ((*flight)->getStatus() == FlightStatus::COMPLETED) {
        // cout << string(20, ' ') << "Chuyen bay " << (*flight)->getFlightID() << " da hoan tat, khong the tra ve\n";
        return;
    }

    const auto airplane = m_airplaneRepository->findByID((*flight)->getAirplaneID());
    (*flight)->removeTicket(ticketID);
    (*airplane)->cancelSeat((*ticket)->getSeatNumber());
    m_ticketRepository->remove(ticketID);

    saveData();
    loadData();
}

List<Ticket*> TicketManager::findByDate(const string& date) const {
    loadData();
    const auto& tickets = m_ticketRepository->getAll();
    List<Ticket *> result;
    for (const auto ticket : tickets) {
        auto flight = m_flightRepository->findByID(ticket->getFlightID());
        if ((*flight)->getDepartureDate() == DateTime(date))
            result.add(ticket);
    }

    return result;
}

Ticket **TicketManager::findByID(const string &ticketID) const {
    loadData();
    return m_ticketRepository->findByID(ticketID);
}

List<Ticket *> TicketManager::findByDestination(const string &destination) const {
    loadData();
    const auto& tickets = m_ticketRepository->getAll();
    List<Ticket*> result;
    for (const auto ticket : tickets) {
        auto flight = m_flightRepository->findByID(ticket->getFlightID());
        if ((*flight)->getDestinationAirport() == destination)
            result.add(ticket);
    }

    return result;
}
// tìm mã chuyến bay
List<Ticket *> TicketManager::findByFlightID(const string &flightID) const {
    return m_ticketRepository->findByFlightID(flightID);
}


TicketRepository &TicketManager::getTicketRepository() const {
    loadData(); // load ticket
    return *m_ticketRepository;
}

FlightRepository &TicketManager::getFlightRepository() const {
    loadData();
    return *m_flightRepository;
}

AirplaneRepository &TicketManager::getAirplaneRepository() const {
    loadData();
    return *m_airplaneRepository;
}

TicketQueueRepository &TicketManager::getTicketQueueRepository() const {
    loadData();
    return *m_ticketQueueRepository;
}
