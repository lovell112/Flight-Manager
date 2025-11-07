#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

class Customer {
private:
    int m_iNumber;
    string m_strFullName;
    string m_strID;

public:
    // Constructor mặc định (không có tham số)
    Customer();

    Customer(int, string, string);

    const string getCustomerID() const;
    const string getFullName() const;
    const int getNumber() const;

    const string toString() const;

    // in 
    void printCustomerInfo() const;
};

#endif
