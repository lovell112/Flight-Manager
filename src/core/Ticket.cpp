#include "../../include/core/Ticket.h"

#include <iomanip>

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
    const string idTicketTitle = "Ma ve: ";
    const string idFlightTitle = "Ma chuyen bay: ";
    const string idCustomerTitle = "Ma khach hang: ";
    const string customerNameTitle = "Ten khach hang: ";
    const string numberSeatTitle = "So ghe: ";

    auto maxTitle = max(idTicketTitle.size(),
                max(idFlightTitle.size(),
                max(idCustomerTitle.size(),
                max(customerNameTitle.size(),
                numberSeatTitle.size()))));

    auto maxData = max(m_strTicketID.size(),
                max(m_strFlightID.size(),
                max(m_strCustomerID.size(),
                max(m_strCustomerName.size(),
                to_string(m_iSeatNumber).size()))));
    cout << string(20, ' ') << string(maxTitle+maxData+2, '-') << endl;

    cout << string(20, ' ') << "|" << setw(maxTitle) << "Ma ve: " << setw(maxData) << m_strTicketID << "|" << endl;
    cout << string(20, ' ') << "|" << setw(maxTitle) << "Ma chuyen bay: " << setw(maxData) << m_strFlightID << "|" << endl;
    cout << string(20, ' ') << "|" << setw(maxTitle) << "Ma khach hang: " << setw(maxData) << m_strCustomerID << "|" << endl;
    cout << string(20, ' ') << "|" << setw(maxTitle) << "Ten khach hang: " << setw(maxData) << m_strCustomerName << "|" << endl;
    cout << string(20, ' ') << "|" << setw(maxTitle) << "So ghe: " << setw(maxData) << m_iSeatNumber << "|" << endl;

    cout << string(20, ' ') << string(maxTitle+maxData+2, '-') << endl;
}

bool Ticket::operator==(const Ticket &other) const {
    return m_strTicketID == other.m_strTicketID;
}
