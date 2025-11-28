/******************************************************************************
 * @file Flight.cpp
 * @description Triển khai các method của Flight
 ******************************************************************************/

#include "../../include/core/Flight.h"
#include <algorithm> // cho std::remove

// --- Constructor & Destructor ---
Flight::Flight(const string& flightID,
    const string& airplaneID,
    const string& destination,
    const string& departure,
    const FlightStatus& status,
    const List<string>& tickets)
    : m_strFlightID(flightID),
    m_strAirplaneID(airplaneID),
    m_strDestinationAirport(destination),
    m_departureDate(new DateTime(departure)),
    m_status(status),
    m_tickets(tickets) {}

Flight::~Flight() {
    delete m_departureDate;
}

const string& Flight::getFlightID() const {
    return m_strFlightID;
}

const string& Flight::getAirplaneID() const {
    return m_strAirplaneID;
}

const string& Flight::getDestinationAirport() const {
    return m_strDestinationAirport;
}

const DateTime& Flight::getDepartureDate() const {
    return *m_departureDate;
}

const FlightStatus& Flight::getStatus() const {
    return m_status;
}

List<string>& Flight::getTickets() {
    return m_tickets;
}

void Flight::setFlightID(const string& id) {
    m_strFlightID = id;
}

void Flight::setAirplaneID(const string& id) {
    m_strAirplaneID = id;
}


void Flight::setDestinationAirport(const string& dest) {
    m_strDestinationAirport = dest;
}

void Flight::setDepartureDate(const string& date) const {
    m_departureDate->set(date);
}

void Flight::setFlightStatus(const FlightStatus& status) {
    m_status = status;
}

void Flight::addTicket(const string& ticketID) { m_tickets.add(ticketID); }

void Flight::removeTicket(const string& ticketID) {
    for (size_t i = 0; i < m_tickets.size(); i++) {
        if (m_tickets[i] == ticketID)
            m_tickets.remove(i);
    }
}

string Flight::toString() const {
    string result;
    result += m_strFlightID + "|" +
        m_strAirplaneID + "|" +
        m_strDestinationAirport + "|" +
        m_departureDate->toString() + "|";
    if (m_status == FlightStatus::CANCELLED)
        result += to_string(0);
    else if (m_status == FlightStatus::AVAILABLE)
        result += to_string(1);
    else if (m_status == FlightStatus::SOLD_OUT)
        result += to_string(2);
    else
        result += to_string(3);

    for (auto& ticketID : m_tickets)
        result += "|" + ticketID;

    return result;
}

void Flight::printFlightInfo() const {
    cout << toString() << endl;
    cout << "Status: ";
    switch (m_status) {
    case FlightStatus::CANCELLED: cout << "CANCELLED"; break;
    case FlightStatus::AVAILABLE: cout << "AVAILABLE"; break;
    case FlightStatus::SOLD_OUT:  cout << "SOLD_OUT"; break;
    case FlightStatus::COMPLETED: cout << "COMPLETED"; break;
    default: cout << "UNKNOWN"; break;
    }
    cout << endl;

    cout << "Tickets: ";
    if (m_tickets.empty()) {
        cout << "No tickets.";
    }
    else {
        for (const auto& t : m_tickets)
            cout << t << " ";
    }
    cout << endl;
}
