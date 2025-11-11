#include "../../include/repository/FlightRepository.h"

using namespace std;

FlightRepository::FlightRepository() {
    loadAllFlights();
}

FlightRepository::~FlightRepository() {
    loadAllFlights();
    saveAllFlights();
    for (auto& flight : m_flights) {
        delete flight;
    }
    m_flights.clear();
}


// ------------------------------------------------------
// them chuyen bay moi
// ------------------------------------------------------
void FlightRepository::add(const Flight& flight) {
    loadAllFlights();
	m_flights.push_back(new Flight(flight)); // them vao vector
    saveAllFlights();
    loadAllFlights();
}

// ------------------------------------------------------
// xoa chuyen bay
// ------------------------------------------------------
void FlightRepository::remove(const string& flightID) {
    loadAllFlights();
    vector<Flight *>::iterator flight = findByID(flightID);
    if (flight != undefineFlight()) {
        delete *flight;
        m_flights.erase(flight);
    } else
        cerr << "Chuyen bay " << flightID << " khong ton tai.\n";
    saveAllFlights();
    loadAllFlights();
}

// ------------------------------------------------------
// cap nhat trang thai chuyen bay
// ------------------------------------------------------
void FlightRepository::setFlightStatus(const string& flightID, const FlightStatus& status) {
    loadAllFlights();
	auto it = findByID(flightID); // dung ham tim kiem
	if (it != undefineFlight()) {  // cap nhat neu tim thay
        (*it)->setFlightStatus(status);
    }
    saveAllFlights();
    loadAllFlights();
}

// ------------------------------------------------------
// tim theo ID
// ------------------------------------------------------
vector<Flight*>::iterator FlightRepository::findByID(const string& flightID) {
    loadAllFlights();
    for (auto it = m_flights.begin(); it != m_flights.end(); ++it) {
        if ((*it)->getFlightID() == flightID)
			return it; // tra ve iterator neu tim thay
    }
	return undefineFlight(); // khong tim thay tra ve undefine flight
}

// ------------------------------------------------------
// tim theo ngay
// ------------------------------------------------------
vector<Flight*> FlightRepository::findByDate(const string& dateString) {
    loadAllFlights();
    vector<Flight*> result;
    for (auto& flight : m_flights) {
        if (flight->getDepartureDate().toString() == dateString) { // so sanh
			result.push_back(flight); // them vao ket qua
        }
    }
    return result;
}

// ------------------------------------------------------
// tim theo destination
// ------------------------------------------------------
vector<Flight*> FlightRepository::findByDestination(const string& destination) {
    loadAllFlights();
    vector<Flight*> result;
    for (auto& flight : m_flights) {
        if (flight->getDestinationAirport() == destination) {
            result.push_back(flight);
        }
    }
    return result;
}

vector<Flight *> FlightRepository::findByAirplane(const string &airplaneID) {
    vector<Flight*> res;
    for (auto flight: m_flights) {
        if (flight->getAirplaneID() == airplaneID)
            res.push_back(flight);
    }

    return res;
}

// ------------------------------------------------------
// tra ve 1 chuyen bay khong ton tai theo dinh dang iterator - o day se la iterator end
// ------------------------------------------------------
vector<Flight *>::iterator FlightRepository::undefineFlight() {
    loadAllFlights();
    return m_flights.end();
}

// ------------------------------------------------------
// lay tat ca chuyen bay
// ------------------------------------------------------
vector<Flight*>& FlightRepository::getAll() {
    loadAllFlights();
    return m_flights;
}

// ------------------------------------------------------
// doc toan bo du lieu chuyen bay tu file flights.txt
// ------------------------------------------------------
void FlightRepository::loadAllFlights() {
    ifstream reader(PATH);

    if (!reader.is_open()) {
        cerr << "Khong doc duoc file" << endl;
        return;
    }

    // don dep danh sach cu neu co
    for (auto& flight : m_flights)
        delete flight;
    m_flights.clear();

    // doc tung dong trong flight.txt
    string line;
    while (getline(reader, line)) {
        if (line.empty())
            continue;
        stringstream spliter(line);
        string flightID, airplaneID, destination, departure, statusString;
        vector<string> tickets;

        getline(spliter, flightID,'|');
        getline(spliter, airplaneID,'|');
        getline(spliter, destination,'|');
        getline(spliter, departure,'|');
        getline(spliter, statusString,'|');

        string ticketItem;
        while (getline(spliter, ticketItem, '|')) {
            tickets.push_back(ticketItem);
        }

        FlightStatus status;
        if (statusString == "0")
            status = FlightStatus::CANCELLED;
        else if (statusString == "1")
            status = FlightStatus::AVAILABLE;
        else if (statusString == "2")
            status = FlightStatus::SOLD_OUT;
        else
            status = FlightStatus::COMPLETED;

        Flight* flight = new Flight(flightID, airplaneID, destination, departure, status, tickets);
        m_flights.push_back(flight);
    }

    reader.close();
}

// ------------------------------------------------------
// ghi toan bo du lieu chuyen bay vao file flights.txt
// ------------------------------------------------------
void FlightRepository::saveAllFlights() {
    ofstream writer(PATH);
    if (!writer.is_open()) {
        cerr << "Khong viet duoc file" << endl;
        return;
    }

    for (auto& flight : m_flights)
        writer << flight->toString() << endl;

    writer.close();
}
