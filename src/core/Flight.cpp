//
// Created by HP on 05/11/2025.
//

#include "../../include/core/Flight.h"
#include <algorithm> // cho std::remove

// --- Constructor & Destructor ---
Flight::Flight(const string& flightID,
    const string& airplaneID,
    const string& destination,
    const DateTime& departure,
    const FlightStatus& status,
    const vector<Ticket>& tickets)
    : m_strFlightID(flightID),
    m_strAirplaneID(airplaneID),
    m_strDestinationAirport(destination),
    m_departureDate(departure),
    m_status(status),
    m_tickets(tickets) {
}

Flight::~Flight() = default;

string Flight::getFlightID() const {
    return m_strFlightID;
}

void Flight::setFlightID(const string& id) { 
    m_strFlightID = id; 
}

string Flight::getAirplaneID() const {
    return m_strAirplaneID;
}

void Flight::setAirplaneID(const string& id) { 
    m_strAirplaneID = id; 
}

string Flight::getDestinationAirport() const {
    return m_strDestinationAirport;
}

void Flight::setDestinationAirport(const string& dest) { 
    m_strDestinationAirport = dest;
}

DateTime Flight::getDepartureDate() const {
    return m_departureDate;
}

void Flight::setDepartureDate(const DateTime& date) { 
    m_departureDate = date; 
}

FlightStatus Flight::getStatus() const {
    return m_status;
}

vector<Ticket>& Flight::getTickets() {
    return m_tickets;
}


void Flight::setStatus(FlightStatus newStatus) {
    m_status = newStatus;
}

void Ticket::addTicket(const string& ticketID) { m_tickets.push_back(ticketID); }

void Ticket::removeTicket(const string& ticketID) { m_tickets.erase(remove(m_tickets.begin(), m_tickets.end(), ticketID), m_tickets.end()); }

string Flight::toString() const {
    return "FlightID: " + m_strFlightID +
        ", AirplaneID: " + m_strAirplaneID +
        ", Destination: " + m_strDestinationAirport +
        ", Departure: " + m_departureDate.toString();
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
            cout << t.getTicketID() << " ";
    }
    cout << endl;
}
