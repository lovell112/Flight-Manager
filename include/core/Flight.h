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
#include "../../include/core/Ticket.h"
using namespace std;

class Flight {
    string m_strFlightID;
    string m_strAirplaneID;
    string m_strDestinationAirport;
    DateTime m_departureDate;
    FlightStatus m_status;
    Ticket vector<string> m_tickets;

public:
    Flight(const string&, const string&,
        const string&, const DateTime&,const& FlightStatus, Ticket const&);
    ~Flight();

	string getFlightID() const;
    string getAirplaneID() const;
    string getDestinationAirport() const;
    DateTime getDepartureDate() const;
	FlightStatus getStatus() const;
    void setStatus(FlightStatus);
	void getTickets(const string&) ;
	void removeTicket(const string&);
    vector<string>& getTickets(const string&);
    string toString() const;
    void printFlightInfo() const;
};

#endif



#endif //AIRPLANEMANAGER_FLIGHT_H
