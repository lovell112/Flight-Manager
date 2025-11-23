//
// Created by HP on 05/11/2025.
//

#ifndef FLIGHTMANAGER_FLIGHT_H
#define FLIGHTMANAGER_FLIGHT_H

#include <string>
#include "../datastructures/List.hpp"
#include <iostream>
#include "../../include/core/FlightStatus.h"
#include "../../include/core/Ticket.h"
#include "../../include/core/DateTime.h"

using namespace std;

class Flight {
private:
    string m_strFlightID;
    string m_strAirplaneID;
    string m_strDestinationAirport;
    DateTime* m_departureDate;
    FlightStatus m_status;
    List<string> m_tickets;

public:

    Flight() = default;
    Flight(const string &flightID,
        const string &airplaneID,
        const string &destination,
        const string &departure,
        const FlightStatus &status,
        const List<string> &tickets);
    ~Flight();



    [[nodiscard]] const string& getFlightID() const;
    [[nodiscard]] const string& getAirplaneID() const;
    [[nodiscard]] const string& getDestinationAirport() const;
    [[nodiscard]] const DateTime& getDepartureDate() const;
    [[nodiscard]] const FlightStatus& getStatus() const;
    List<string>& getTickets();

    void setFlightID(const string&);
    void setAirplaneID(const string&);
    void setDestinationAirport(const string&);
    void setDepartureDate(const string&) const;
    void setFlightStatus(const FlightStatus&);

    void addTicket(const string&);
    void removeTicket(const string&);

    [[nodiscard]] string toString() const;
    void printFlightInfo() const;
};

#endif // FLIGHTMANAGER_FLIGHT_H
