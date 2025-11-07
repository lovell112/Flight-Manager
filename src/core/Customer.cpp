#include "Customer.h"
#include <iostream>

Customer::Customer() {
    m_iNumber = 0;
    m_strFullName = "";
    m_strID = "";
}

// Constructor có tham số - khởi tạo với giá trị được truyền vào
Customer::Customer(int number, string fullName, string id) {
    m_iNumber = number;
    m_strFullName = fullName;
    m_strID = id;
}

// lấy ID khách hàng
const string Customer::getCustomerID() const {
    return m_strID;
}

// lấy tên đầy đủ
const string Customer::getFullName() const {
    return m_strFullName;
}

//  lấys ID
const int Customer::getNumber() const {
    return m_iNumber;
}

// chuyển đối tượng thành chuỗi
const string Customer::toString() const {
    return "Customer m_strAirplaneID: " + m_strID +
        "\nItem: " + m_strFullName +
        "\nNumber: " + to_string(m_iNumber);
}

// in ra thông tin
void Customer::printCustomerInfo() const {
    cout << toString() << endl;
}
