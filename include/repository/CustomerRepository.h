#ifndef FLIGHTMANAGER_CUSTOMERREPOSITORY_H
#define FLIGHTMANAGER_CUSTOMERREPOSITORY_H

#include "../core/Customer.h"
#include <string>
#include <fstream>
#include <sstream>
#include "../datastructures/List.hpp"
using namespace std;

class CustomerRepository {
private:
    List<Customer*> m_customers;
    const string PATH = "../data/customer.txt";

public:
    CustomerRepository();
    ~CustomerRepository();
    
    void add(const Customer&);
    void remove(const string&);

    Customer **findByID(const string &);

    List<Customer *> &getAll();

    Customer **undefineCustomer();
    
    void loadAllCustomers();
    void saveAllCustomers() const;
};

#endif //FLIGHTMANAGER_CUSTOMERREPOSITORY_H
