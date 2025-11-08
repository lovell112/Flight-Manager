//
// Created by HP on 05/11/2025.
//
#include <string>
#include <vector>
#include <iostream>
#include "../../include/core/Flight.h"
#include "../../include/core/FlightStatus.h"
#include "../../include/core/Ticket.h"
#include "../../include/core/DateTime.h"
#include "../../include/core/Ticket.h"



Flight::Flight(const string& flightID, const string& airplaneID,
    const string& Destination, const DateTime& Date, FlightStatus Status)
    : m_strFlightID(flightID),
    m_strAirplaneID(airplaneID),
    m_strDestinationAirport(destination),
    m_departureDate(date),
    m_status(status) {}
Flight::Flight() {}
//lay du lieu
string Flight::getFlightID() const { return m_strFlightID; }

string Flight::getAirplaneID() const { return m_strAirplaneID; }

string Flight::getDestinationAirport() const { return m_strDestinationAirport; }

DateTime Flight::getDepartureDate() const { return m_departureDate; }
//lay status chuyen bay
FlightStatus Flight::getStatus() const { return m_status; }
//set lai status chuyen bay
void Flight::setStatus(FlightStatus Status) { m_status = Status; }

void Ticket::addTicket(const string& ticketID) {
    m_tickets.push_back(ticketID);
}

void Ticket::removeTicket(const string& ticketID) {
    m_tickets.erase(remove(m_tickets.begin(), m_tickets.end(), ticketID), m_tickets.end());
}

vector<string>& Ticket::getTickets() { return m_tickets; }

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
    case FlightStatus::SOLD_OUT: cout << "SOLD_OUT"; break;
    case FlightStatus::COMPLETED: cout << "COMPLETED"; break;
    }
    cout << endl;
    cout << "Tickets: ";
    for (const auto& t : m_tickets)
        cout << t << " ";
    cout << endl;
}
