#include "../../include/service/CustomerService.h"
#include <iostream>

// Constructor - khoi tao repository
CustomerService::CustomerService() {
    m_customerRepository = new CustomerRepository();
}

CustomerService::~CustomerService() {
    cout << "Delete CustomerService thanh cong\n";
    delete m_customerRepository;
}

// them khach hang vao repository
void CustomerService::addCustomer(const Customer& customer) {
    m_customerRepository->add(customer);
}

// - xoa khach hang theo ID
void CustomerService::removeCustomer(const string& customerID) {
    m_customerRepository->remove(customerID);
}

//tim khach hang theo ID, tra ve iterator
vector<Customer*>::iterator CustomerService::findCustomerByID(const string& customerID) {
    return m_customerRepository->findByID(customerID);
}

//lay tat ca khach hang, tra ve iterator dau tien
vector<Customer*>::iterator CustomerService::getAll() {
    return m_customerRepository->getAll();
}
// end - lay iterator cuoi cung
vector<Customer*>::iterator CustomerService::end() {
    return m_customerRepository->end();
}
