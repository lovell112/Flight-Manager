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
    [[nodiscard]] const string& getTicketID() const;
    [[nodiscard]] const string& getFlightID() const;
    [[nodiscard]] const string& getCustomerID() const;
    [[nodiscard]] const string& getCustomerName() const;
    [[nodiscard]] int getSeatNumber() const;
    void setTicketID(const string&);
    void setFlightID(const string&);
    void setCustomerID(const string&);
    void setCustomerName(const string&);
    void setSeatNumber(int);
    [[nodiscard]] string toString() const;
    void printTicketInfo() const;
    bool operator==(const Ticket &) const;
};


#endif //AIRPLANEMANAGER_TICKET_H
