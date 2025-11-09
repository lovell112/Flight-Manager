#ifndef AIRPLANEMANAGER_FLIGHTMANAGER_H
#define AIRPLANEMANAGER_FLIGHTMANAGER_H

#include "../repository/AirplaneRepository.h"
#include "../repository/FlightRepository.h"
#include "../repository/TicketRepository.h"
#include "../core/FlightStatus.h"


using namespace std;
class FlightManager {
    FlightRepository* m_flightRepository;
    TicketRepository* m_ticketRepository;
    AirplaneRepository* m_airplaneRepository;
public:
    FlightManager(FlightRepository*, TicketRepository*, AirplaneRepository*);
    ~FlightManager();
    void addFlight(const Flight&) const;
    void cancelFlight(const string&) const;
    void updateFlightStatus(const string&, const FlightStatus&) const;

    vector<Flight*>::iterator findFlightByID(const string&) const;
    vector<Flight*> findFlightByDate(const string&) const;
    vector<Flight*> findFlightByDestination(const string&) const;

    vector<int> getAvailableSeats(const string&) const;
    vector<Flight*>& getAllFlight() const;
};




#endif //AIRPLANEMANAGER_FLIGHTMANAGER_H