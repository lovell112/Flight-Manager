#ifndef FLIGHTMANAGER_FLIGHTREPOSITORY_H
#define FLIGHTMANAGER_FLIGHTREPOSITORY_H

#include "../../include/core/Flight.h"
#include <string>
#include <fstream>
#include <sstream>
#include "../datastructures/List.hpp"
#include <iostream>
using namespace std;

class FlightRepository {
private:
    const string PATH = "../data/flight.txt";
    List<Flight*> m_flights;

public:
    FlightRepository();
    ~FlightRepository();
    void add(const Flight&);
    void remove(const string&);
    void setFlightStatus(const string&, const FlightStatus&);

    Flight** findByID(const string&);
    List<Flight*> findByDate(const string&);
    List<Flight*> findByDestination(const string&);
    List<Flight*> findByAirplane(const string&);

    [[nodiscard]] Flight** undefineFlight();

    List<Flight*>& getAll();
    void loadAllFlights();
    void saveAllFlights();
};

#endif //FLIGHTMANAGER_FLÌGHTREPOSITORY_H