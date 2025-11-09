#ifndef FLIGHTMANAGER_CUSTOMERSERVICE_H
#define FLIGHTMANAGER_CUSTOMERSERVICE_H

#include "../repository/CustomerRepository.h"
#include <vector>
using namespace std;

class CustomerService {
private:
    CustomerRepository* m_customerRepository;

public:
    CustomerService();
    ~CustomerService();

    void addCustomer(const Customer&);
    void removeCustomer(const string&);

    vector<Customer*>::iterator findCustomerByID(const string&);
    vector<Customer*>::iterator getAll();
    vector<Customer*>::iterator end();
};

#endif //FLIGHTMANAGER_CUSTOMERSERVICE_H
