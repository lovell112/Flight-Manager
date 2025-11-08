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
    Ticket(const string&, const string&, const string&, const string&, int);
    ~Ticket();
    const string& getTicketID() const;
    const string& getFlightID() const;
    const string& getCustomerID() const;
    const string& getCustomerName() const;
    int getSeatNumber() const;
    void setTicketID(const string&);
    void setFlightID(const string&);
    void setCustomerID(const string&);
    void setCustomerName(const string&);
    void setSeatNumber(int);
    string toString() const;
    void printTicketInfo();
};


#endif //AIRPLANEMANAGER_TICKET_H
