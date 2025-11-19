#include "../../include/service/TicketManager.h"

void TicketManager::saveData() {
    m_ticketRepository->saveAllTickets();
    m_flightRepository->saveAllFlights();
    m_airplaneRepository->saveAllAirplanes();
    m_ticketQueueRepository->saveAllTickets();
    m_customerRepository->saveAllCustomers();
}
void TicketManager::loadData() {
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

void TicketManager::addTicket(const Ticket &ticket) {
    m_ticketRepository->add(ticket);

    auto flight = m_flightRepository->findByID(ticket.getFlightID());
    auto airplane = m_airplaneRepository->findByID((*flight)->getAirplaneID());
    (*flight)->addTicket(ticket.getTicketID());
    (*airplane)->bookSeat(ticket.getSeatNumber());

    m_ticketQueueRepository->remove(ticket.getTicketID()); // delete ve khoi hang doi
    m_customerRepository->remove(ticket.getCustomerID()); // delete khoi hang doi khach cho mua

    saveData();
    loadData();
}

void TicketManager::removeTicket(const string &ticketID) {
    auto ticket = m_ticketRepository->findByID(ticketID);
    if (ticket == m_ticketRepository->undefineTicket()) {
        cout << "Khong ton tai ve : " << ticketID << endl;
        return;
    }

    auto flight = m_flightRepository->findByID((*ticket)->getFlightID());
    if ((*flight)->getStatus() == FlightStatus::COMPLETED) {
        cout << "Chuyen bay " << (*flight)->getFlightID() << " da hoan tat, khong the tra ve\n";
        return;
    }

    auto airplane = m_airplaneRepository->findByID((*flight)->getAirplaneID());
    m_ticketRepository->remove(ticketID);
    (*flight)->removeTicket(ticketID);
    (*airplane)->cancelSeat((*ticket)->getSeatNumber());

    saveData();
    loadData();
}

vector<Ticket*> TicketManager::findByDate(const string& date) {
    loadData();
    const auto& tickets = m_ticketRepository->getAll();
    vector<Ticket*> result;
    for (const auto ticket : tickets) {
        auto flight = m_flightRepository->findByID(ticket->getFlightID());
        if ((*flight)->getDepartureDate() == DateTime(date))
            result.push_back(ticket);
    }

    return result;
}

vector<Ticket*>::iterator TicketManager::findByID(const string& ticketID) {
    loadData();
    return m_ticketRepository->findByID(ticketID);
}

vector<Ticket*> TicketManager::findByDestination(const string& destination) {
    loadData();
    const auto& tickets = m_ticketRepository->getAll();
    vector<Ticket*> result;
    for (const auto ticket : tickets) {
        auto flight = m_flightRepository->findByID(ticket->getFlightID());
        if ((*flight)->getDestinationAirport() == destination)
            result.push_back(ticket);
    }

    return result;
}

vector<Ticket *> TicketManager::findByFlightID(const string &flightID) {
    return m_ticketRepository->findByFlightID(flightID);
}


TicketRepository &TicketManager::getTicketRepository() {
    loadData();
    return *m_ticketRepository;
}

FlightRepository &TicketManager::getFlightRepository() {
    loadData();
    return *m_flightRepository;
}

AirplaneRepository &TicketManager::getAirplaneRepository() {
    loadData();
    return *m_airplaneRepository;
}

TicketQueueRepository &TicketManager::getTicketQueueRepository() {
    loadData();
    return *m_ticketQueueRepository;
}
