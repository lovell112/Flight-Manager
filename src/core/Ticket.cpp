//
// Created by HP on 05/11/2025.
//

#include "../../include/core/Ticket.h"
Ticket::Ticket(const string& ticketID, const string& flightID,
               const string& customerID, const string& customerName,
               const int& seatNumber) {
    m_strTicketID = ticketID;
    m_strFlightID = flightID;
    m_strCustomerID = customerID;
    m_strCustomerName = customerName;
    m_iSeatNumber = seatNumber;
}


Ticket::~Ticket() {}

string Ticket::getTicket() const {
    return m_strTicketID;
}

int Ticket::getSeatNumber() const {
    return m_iSeatNumber;
}

string Ticket::getCustomer() const {
    return m_strCustomerID;
}

//tra ve dang chuoi
string Ticket::toString() const {
    string info = m_strTicketID + "|" + m_strFlightID + "|" + m_strCustomerID + "|" + m_strCustomerName + "|" + to_string(m_iSeatNumber);
    return info;
}


void Ticket::printTicketInfo() {
    cout << "Ma ve: " << m_strTicketID << endl;
    cout << "Ma chuyen bay: " << m_strFlightID << endl;
    cout << "Ma khach hang: " << m_strCustomerID << endl;
    cout << "Ten khach hang: " << m_strCustomerName << endl;
    cout << "So ghe: " << m_iSeatNumber << endl;
}
