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
    Customer(int, const string&, const string&);
    ~Customer() = default;

    // getter
    [[nodiscard]] const string& getCustomerID() const;
    [[nodiscard]] const string& getFullName() const;
    [[nodiscard]] int getNumber() const;

    // setter
    void setNumber(int);
    void setFullname(const string&);
    void setCustomerID(const string&);

    // dinh dang obj -> string
    [[nodiscard]] string toString() const;

    // in 
    void printCustomerInfo() const;
};

#endif
