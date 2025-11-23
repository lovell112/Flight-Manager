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

    void saveData() const;
    void loadData() const;
public:
    FlightManager();
    FlightManager(FlightRepository*, TicketRepository*, AirplaneRepository*, CustomerRepository*);

    ~FlightManager();

    [[nodiscard]] FlightRepository& getFlightRepository() const;

    [[nodiscard]] TicketRepository& getTicketRepository() const;

    [[nodiscard]] AirplaneRepository& getAirplaneRepository() const;

    [[nodiscard]] CustomerRepository& getCustomerRepository() const;
    void addFlight(const Flight&) const;
    void cancelFlight(const string&) const;
    void updateFlightStatus(const string&, const FlightStatus&) const;

    Flight** findFlightByID(const string&) const;
    List<Flight*> findFlightByDate(const string&) const;
    List<Flight*> findFlightByDestination(const string&) const;
    List<int> getAvailableSeat(const string&) const;
    List<Flight*> findFlightQuantityOfAirplane(const string&) const;

    int countFlightOfOneAirplane(const string&) const;
    List<int> getSeats(const string&) const;
    List<Flight*>& getAllFlight() const;
};

#endif //AIRPLANEMANAGER_FLIGHTMANAGER_H