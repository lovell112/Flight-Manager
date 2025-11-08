//
// Created by HP on 05/11/2025.
//

#include "../../include/repository/FlightRepository.h"

using namespace std;

// ------------------------------------------------------
// them chuyen bay moi
// ------------------------------------------------------
void FlightRepository::add(const Flight& flight) {
	m_flights.push_back(flight); // them vao vector
}

// ------------------------------------------------------
// xoa chuyen bay
// ------------------------------------------------------
void FlightRepository::remove(const string& flightID) {
	for (auto it = m_flights.begin(); it != m_flights.end(); ++it) { // duyet vector
		if (it->getFlightID() == flightID) { // neu tim thay chuyen bay can xoa
            m_flights.erase(it);
            break;
        }
    }
}

// ------------------------------------------------------
// cap nhat trang thai chuyen bay
// ------------------------------------------------------
void FlightRepository::setFlightStatus(const string& flightID, const FlightStatus& status) {
	auto it = findByID(flightID); // dung ham tim kiem
	if (it != m_flights.end()) {  // cap nhat neu tim thay
        it->setStatus(status);
    }
}

// ------------------------------------------------------
// tim theo ID
// ------------------------------------------------------
vector<Flight*>::iterator FlightRepository::findByID(const string& flightID) {
    for (auto it = m_flights.begin(); it != m_flights.end(); ++it) {
        if (it->getFlightID() == flightID)
			return it; // tra ve iterator neu tim thay
    }
	return m_flights.end(); // khong tim thay tra ve end()
}

// ------------------------------------------------------
// tim theo ngay
// ------------------------------------------------------
vector<Flight*> FlightRepository::findByDate(const string& dateString) {
    vector<Flight*> result;
    for (auto& f : m_flights) {
        if (f->getDepartureDate()->toString() == dateString) { // so sanh
			result.push_back(f); // them vao ket qua
        }
    }
    return result;
}

// ------------------------------------------------------
// tim theo destination
// ------------------------------------------------------
vector<Flight*> FlightRepository::findByDestination(const string& destination) {
    vector<Flight*> result;
    for (auto& f : m_flights) {
        if (f->getDestinationAirport() == destination) {
            result.push_back(f);
        }
    }
    return result;
}

// ------------------------------------------------------
// lay tat ca chuyen bay
// ------------------------------------------------------
vector<Flight*>& FlightRepository::getAll() {
    static vector<Flight*> all;
    all.clear();
    for (auto& f : m_flights)
        all.push_back(f);
    return all;
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

    m_flights.clear();
    string line;
    while (getline(reader, line)) {
        stringstream ss(line);
        string id, plane, dest;
        int day, month, year, hour, minute, statusInt;

        ss >> id >> plane >> dest >> day >> month >> year >> hour >> minute >> statusInt;

        DateTime dt{ day, month, year, hour, minute };
        FlightStatus status = static_cast<FlightStatus>(statusInt);
        Flight* f = new Flight(id, plane, dest, dt, status);
        m_flights.push_back(f);
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

    for (auto& f : m_flights) {
        DateTime d = f->getDepartureDate();
        writer << f->getFlightID() << " "
            << f->getAirplaneID() << " "
            << f->getDestinationAirport() << " "
            << d->day << " " << d.month << " " << d.year << " "
            << d->hour << " " << d.minute << " "
            << static_cast<int>(f.getStatus()) << "\n";
    }

    writer.close();
}
