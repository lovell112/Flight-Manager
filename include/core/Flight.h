//
// Created by HP on 05/11/2025.
//

#ifndef FLIGHTMANAGER_FLIGHT_H
#define FLIGHTMANAGER_FLIGHT_H

#include <string>
#include <vector>
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
    DateTime m_departureDate;
    FlightStatus m_status;
    vector<Ticket> m_tickets;  

public:

    Flight() = default;
    Flight(const string& flightID,
        const string& airplaneID,
        const string& destination,
        const DateTime& departure,
        const FlightStatus& status,
        const vector<Ticket>& tickets = {});
    ~Flight() = default;

  
    string getFlightID() const;
    void setFlightID(const string&);
    string getAirplaneID() const;
    void setAirplaneID(const string&);
    string getDestinationAirport() const;
    void setDestinationAirport(const string&);
    DateTime getDepartureDate() const;
    void setDepartureDate(const DateTime&);
    FlightStatus getStatus() const;
    vector<Ticket>& getTickets(); 


    void setStatus(FlightStatus newStatus);
    void addTicket(const Ticket& ticket);
    void removeTicket(const string& ticketID);

    string toString() const;
    void printFlightInfo() const;
};

#endif // FLIGHTMANAGER_FLIGHT_H
