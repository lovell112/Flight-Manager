#ifndef FLIGHTMANAGER_FLIGHTREPOSITORY_H
#define FLIGHTMANAGER_FLIGHTREPOSITORY_H

#include "../core/Flight.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class FlightRepository {
private:
    const string PATH = "../data/flight.txt";
    vector<Flight*> m_flights;

public:
    void add(const Flight&);
    void remove(const string&);
    void setFlightStatus(const string&, const FlightStatus&);

    vector<Flight*>::iterator findByID(const string&);
    vector<Flight*> findByDate(const string&);
    vector<Flight*> findByDestination(const string&);

    vector<Flight*>& getAll();
    void loadAllFlights();
    void saveAllFlights();
};

#endif //FLIGHTMANAGER_FLÌGHTREPOSITORY_H
