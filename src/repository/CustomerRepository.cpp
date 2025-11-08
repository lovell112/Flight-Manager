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
    if (it != m_customers.end()) {
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
    return m_customers.end();
}

// getAll - tra ve iterator dau tien
vector<Customer*>::iterator CustomerRepository::getAll() {
    return m_customers.begin();
}

vector<Customer*>::iterator CustomerRepository::end() {
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
    
    for (const auto& customer : m_customers) {
        writer << customer->getNumber() << "|" 
               << customer->getFullName() << "|" 
               << customer->getCustomerID() << endl;
    }
    writer.close();
}
