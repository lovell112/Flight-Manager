#include "../../include/service/CustomerService.h"
#include <iostream>

// Constructor - khoi tao repository
CustomerService::CustomerService() {
    m_ticketRepository = new TicketRepository();
    m_customerRepository = new CustomerRepository();
    m_flightRepository = new FlightRepository();
    m_airplaneRepository = new AirplaneRepository();
    m_ticketQueueRepository = new TicketQueueRepository();
}

CustomerService::~CustomerService() {
    delete m_ticketRepository;
    delete m_customerRepository;
    delete m_flightRepository;
    delete m_airplaneRepository;
    delete m_ticketQueueRepository;
}

// them khach hang vao repository
void CustomerService::addCustomer(const Customer& customer) const {
    m_customerRepository->add(customer);
}

// - xoa khach hang theo ID
void CustomerService::removeCustomer(const string& customerID) const {
    m_customerRepository->remove(customerID);
}

bool CustomerService::tryBookTicket(const string& flightID, const string& customerID, const string& customerFullname, int seatNumber) const {
    // Kiem tra chuyen bay co ton tai khong
    const auto flight = m_flightRepository->findByID(flightID);
    if (flight == m_flightRepository->undefineFlight()) {
        cout << string(20, ' ') << "Khong tim thay chuyen bay voi ID: " << flightID << endl;
        return false; // khong thi return
    }

    auto flightStatus = (*flight)->getStatus();
    if (flightStatus != FlightStatus::AVAILABLE) {
        switch (flightStatus) {
            case FlightStatus::CANCELLED:
                cout << string(20, ' ') << "Chuyen bay da bi huy\n";
                break;
            case FlightStatus::SOLD_OUT:
                cout << string(20, ' ') << "Chuyen bay da het ve\n";
                break;
            case FlightStatus::COMPLETED:
                cout << string(20, ' ') << "Chuyen bay da hoan tat\n";
                break;
            default: ;
        }

        return false;
    }


    const auto airplane = m_airplaneRepository->findByID((*flight)->getAirplaneID());
    // cerr << (*airplane)->toString() << endl;
    // kiem tra ghe trong khong
    if (!(*airplane)->isSeatAvailable(seatNumber)) {
        cout << string(20, ' ') << "Ghe da duoc dat!" << endl;
        return false;
    }

    // tao ve moi va them vao hang doi de duyet
    const string ticketID = flightID + "-" + to_string(seatNumber);
    m_ticketQueueRepository->push(Ticket(ticketID, flightID, customerID, customerFullname, seatNumber));

    const int customerNumber = m_customerRepository->getAll().size() == 0 ? 0 : m_customerRepository->getAll().size();

    m_customerRepository->add(Customer(customerNumber, customerFullname, customerID));

    // cout << (*m_ticketQueueRepository->findByID(ticketID))->toString() << endl;
    cout << string(20, ' ') << "Dat ve thanh cong cho khach: " << customerFullname << endl;
    return true;
}

//tim khach hang theo ID, tra ve Iterator
vector<Customer*>::iterator CustomerService::findCustomerByID(const string& customerID) const {
    return vector<Customer *>::iterator(m_customerRepository->findByID(customerID));
}

//lay tat ca khach hang, tra ve Iterator dau tien
List<Customer *> CustomerService::getAll() const {
    return m_customerRepository->getAll();
}
// end - lay Iterator cuoi cung
Customer **CustomerService::undefineCustomer() const {
    return m_customerRepository->undefineCustomer();
}
