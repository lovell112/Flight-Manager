#ifndef FLIGHTMANAGER_CUSTOMERREPOSITORY_H
#define FLIGHTMANAGER_CUSTOMERREPOSITORY_H

#include "../core/Customer.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class CustomerRepository {
private:
    vector<Customer*> m_customers;
    const string PATH = "../data/customer.txt";

public:
    CustomerRepository();
    ~CustomerRepository();
    
    void add(const Customer&);
    void remove(const string&);
    
    vector<Customer*>::iterator findByID(const string&);
    vector<Customer*>& getAll();
    vector<Customer*>::iterator undefineCustomer();
    
    void loadAllCustomers();
    void saveAllCustomers() const;
};

#endif //FLIGHTMANAGER_CUSTOMERREPOSITORY_H
