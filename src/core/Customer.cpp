#include "../../include/core/Customer.h"
#include <iostream>

Customer::Customer() {
    m_iNumber = 0;
    m_strFullName = "";
    m_strID = "";
}

// Constructor có tham số - khởi tạo với giá trị được truyền vào
Customer::Customer(const int number, const string& fullName, const string& id) {
    m_iNumber = number;
    m_strFullName = fullName;
    m_strID = id;
}

// lấy ID khách hàng
const string& Customer::getCustomerID() const {
    return m_strID;
}

// lấy tên đầy đủ
const string& Customer::getFullName() const {
    return m_strFullName;
}

//  lấys ID
int Customer::getNumber() const {
    return m_iNumber;
}

// sua so thu tu
void Customer::setNumber(int number) {
    m_iNumber = number;
}

// sua ho ten
void Customer::setFullname(const string& fullname) {
    m_strFullName = fullname;
}

// sua cmnd
void Customer::setCustomerID(const string& customerID) {
    m_strID = customerID;
}

// chuyển đối tượng thành chuỗi
string Customer::toString() const {
    return to_string(m_iNumber) + "|" + m_strFullName + "|" + m_strID;
}

// in ra thông tin
void Customer::printCustomerInfo() const {
    cout << toString() << endl;
}
