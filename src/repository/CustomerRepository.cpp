#include "../../include/repository/CustomerRepository.h"
#include <iostream>

CustomerRepository::CustomerRepository() {
    loadAllCustomers();
}

// Destructor - luu du lieu xuong file truoc khi delete
CustomerRepository::~CustomerRepository() {
    // Luu lai cac khach hang truoc khi delete
    saveAllCustomers();
    for (auto& customer : m_customers) {
        delete customer;
    }
    m_customers.clear();
}

// add - them khach hang vao danh sach
void CustomerRepository::add(const Customer& customer) {
    m_customers.push_back(new Customer(customer));
}

// remove - xoa khach hang theo ID
void CustomerRepository::remove(const string& customerID) {
    auto it = findByID(customerID);
    if (it != undefineCustomer()) {
        delete *it;
        m_customers.erase(it);
    }
}

// findByID - tim khach hang theo ID, tra ve iterator
vector<Customer*>::iterator CustomerRepository::findByID(const string& customerID) {
    for (auto it = m_customers.begin(); it != m_customers.end(); ++it) {
        if ((*it)->getCustomerID() == customerID) {
            return it;
        }
    }

    return undefineCustomer();
}

// getAll - tra ve danh sach customer
vector<Customer*>& CustomerRepository::getAll() {
    return m_customers;
}

// tra ve 1 phan tu khong hop le trong danh sach - o day se la iterator end
vector<Customer*>::iterator CustomerRepository::undefineCustomer() {
    return m_customers.end();
}

void CustomerRepository::loadAllCustomers() {
    ifstream reader(PATH);
   
    if (!reader.is_open()) {
        cerr << "Khong doc duoc file\n";
        return;
    }

    // Doc 1 dong, sau do tach du lieu tu dong doc duoc
    string line;
    while (getline(reader, line)) {
        if (line.empty()) continue;
        
        stringstream spliter(line);
        string numberStr, fullName, id;
        
        getline(spliter, numberStr, '|');  
        getline(spliter, fullName, '|');  
        getline(spliter, id, '|');        
        
        int number = stoi(numberStr);
        m_customers.push_back(new Customer(number, fullName, id)); // add customer vao repo
    }
    reader.close();
}

//  ghi du lieu vao file
void CustomerRepository::saveAllCustomers() const {
    ofstream writer(PATH);
    // Kiem tra co ghi duoc file khong?
    if (!writer.is_open()) {
        cerr << "Khong viet duoc file\n";
        return;
    }

    // ghi ra file theo dinh dang cua obj
    for (auto& customer : m_customers)
        writer << customer->toString() << endl;

    writer.close();
}
