#include "../../include/core/Ticket.h"
Ticket::Ticket(const string& ticketID, const string& flightID,
               const string& customerID, const string& customerName,
               const int seatNumber) {
    m_strTicketID = ticketID;
    m_strFlightID = flightID;
    m_strCustomerID = customerID;
    m_strCustomerName = customerName;
    m_iSeatNumber = seatNumber;
}


Ticket::~Ticket() {}

const string& Ticket::getTicketID() const {
    return m_strTicketID;
}

const string& Ticket::getFlightID() const {
    return m_strFlightID;
}

const string& Ticket::getCustomerID() const {
    return m_strCustomerID;
}

const string& Ticket::getCustomerName() const {
    return m_strCustomerName;
}

int Ticket::getSeatNumber() const {
    return m_iSeatNumber;
}

void Ticket::setTicketID(const string& newID) {
    m_strTicketID = newID;
}

void Ticket::setFlightID(const string& newID) {
    m_strFlightID = newID;
}

void Ticket::setCustomerID(const string& newID) {
    m_strCustomerID = newID;
}

void Ticket::setCustomerName(const string& newName) {
    m_strCustomerName = newName;
}

void Ticket::setSeatNumber(const int newSeatNumber) {
    m_iSeatNumber = newSeatNumber;
}

//tra ve dang chuoi
string Ticket::toString() const {
    string info = m_strTicketID + "|" + m_strFlightID + "|" + m_strCustomerID + "|" + m_strCustomerName + "|" + to_string(m_iSeatNumber);
    return info;
}

void Ticket::printTicketInfo() const {
    cout << "Ma ve: " << m_strTicketID << endl;
    cout << "Ma chuyen bay: " << m_strFlightID << endl;
    cout << "Ma khach hang: " << m_strCustomerID << endl;
    cout << "Ten khach hang: " << m_strCustomerName << endl;
    cout << "So ghe: " << m_iSeatNumber << endl;
}

bool Ticket::operator==(const Ticket &other) const {
    return m_strTicketID == other.m_strTicketID;
}
