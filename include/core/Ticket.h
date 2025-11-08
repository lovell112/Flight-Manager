//
// Created by HP on 05/11/2025.
//
#ifndef AIRPLANEMANAGER_TICKET_H
#define AIRPLANEMANAGER_TICKET_H
#include <iostream>
#include <string>
using namespace std;
class Ticket {
    string m_strTicketID;
    string m_strFlightID;
    string m_strCustomerID;
    string m_strCustomerName;
    int m_iSeatNumber;

public:
    Ticket(const string&, const string&, const string&, const string&, const int&);
    ~Ticket();
    string getTicket() const;
    int getSeatNumber() const;
    string getCustomer() const;
    string toString() const;
    void printTicketInfo();
};


#endif //AIRPLANEMANAGER_TICKET_H
