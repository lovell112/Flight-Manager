#ifndef FLIGHTMANAGER_FLIGHTREPOSITORY_H
#define FLIGHTMANAGER_FLIGHTREPOSITORY_H

#include "../../include/core/Flight.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

class FlightRepository {
private:
    const string PATH = "../data/flight.txt";
    vector<Flight*> m_flights;

public:
    FlightRepository();
    ~FlightRepository();
    void add(const Flight&);
    void remove(const string&);
    void setFlightStatus(const string&, const FlightStatus&);

    vector<Flight*>::iterator findByID(const string&);
    vector<Flight*> findByDate(const string&);
    vector<Flight*> findByDestination(const string&);

    [[nodiscard]] vector<Flight*>::iterator undefineFlight();

    vector<Flight*>& getAll();
    void loadAllFlights();
    void saveAllFlights();
};

#endif //FLIGHTMANAGER_FLÌGHTREPOSITORY_H
