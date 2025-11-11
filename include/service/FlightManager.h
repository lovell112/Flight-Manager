#ifndef AIRPLANEMANAGER_FLIGHTMANAGER_H
#define AIRPLANEMANAGER_FLIGHTMANAGER_H

#include "../repository/AirplaneRepository.h"
#include "../repository/FlightRepository.h"
#include "../repository/TicketRepository.h"
#include "../core/FlightStatus.h"
#include "../repository/CustomerRepository.h"


using namespace std;
class FlightManager {
    FlightRepository* m_flightRepository;
    TicketRepository* m_ticketRepository;
    AirplaneRepository* m_airplaneRepository;
    CustomerRepository* m_customerRepository;

    void saveData();
    void loadData();
public:
    FlightManager();
    FlightManager(FlightRepository*, TicketRepository*, AirplaneRepository*, CustomerRepository*);
    ~FlightManager();
    void addFlight(const Flight&);
    void cancelFlight(const string&);
    void updateFlightStatus(const string&, const FlightStatus&);

    vector<Flight*>::iterator findFlightByID(const string&);
    vector<Flight*> findFlightByDate(const string&);
    vector<Flight*> findFlightByDestination(const string&);
    vector<int> getAvailableSeat(const string&);
    vector<Flight*> findFlightQuantityOfAirplane(const string&);

    int countFlightOfOneAirplane(const string&);
    vector<int> getSeats(const string&);
    vector<Flight*>& getAllFlight();
};




#endif //AIRPLANEMANAGER_FLIGHTMANAGER_H