#include "../../include/service/CustomerService.h"
#include <iostream>
#include <functional>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _HAS_STD_BYTE 0
#include <windows.h>

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

    function<bool (const string&)> isValidID = [](const string& id) ->bool  {
        if (id.size() != 12)
            return false;
        for (const auto ch : id) {
            if (ch < 48 || ch > 57)
                return false;
        }

        return true;
    };

    if (!isValidID(customerID)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << string(20, ' ') << "Can cuoc cong dan khong hop le!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return false;
    }

    if (customerFullname.empty()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << string(20, ' ') << "Ten cua ban khong hop le!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return false;
    }

    // Kiem tra chuyen bay co ton tai khong
    const auto flight = m_flightRepository->findByID(flightID);
    if (flight == m_flightRepository->undefineFlight()) {
        cout << string(20, ' ') << "Khong tim thay chuyen bay voi ID: " << flightID << endl;
        return false; // khong thi return
    }

    auto flightStatus = (*flight)->getStatus();
    if (flightStatus != FlightStatus::AVAILABLE) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        switch (flightStatus) {
            case FlightStatus::CANCELLED:
                cout << string(20, ' ') << "Chuyen bay da bi huy, vui long chon chuyen bay khac\n";
                break;
            case FlightStatus::SOLD_OUT:
                cout << string(20, ' ') << "Chuyen bay da het ve, vui long chon chuyen bay khac\n";
                break;
            case FlightStatus::COMPLETED:
                cout << string(20, ' ') << "Chuyen bay da hoan tat, vui long chon chuyen bay khac\n";
                break;
            default: ;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return false;
    }

    const auto airplane = m_airplaneRepository->findByID((*flight)->getAirplaneID());
    // cerr << (*airplane)->toString() << endl;
    // kiem tra ghe trong khong
    if (!(*airplane)->isSeatAvailable(seatNumber)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << string(20, ' ') << "Ghe da duoc dat!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        return false;
    }

    // tao ve moi va them vao hang doi de duyet
    const string ticketID = flightID + "-" + to_string(seatNumber);

    const Ticket ticket(ticketID, flightID, customerID, customerFullname, seatNumber);
    m_ticketQueueRepository->push(ticket);
    const int customerNumber = m_customerRepository->getAll().size() == 0 ? 0 : m_customerRepository->getAll().size();

    m_customerRepository->add(Customer(customerNumber, customerFullname, customerID));

    // cout << (*m_ticketQueueRepository->findByID(ticketID))->toString() << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << string(20, ' ') << "Dat ve thanh cong cho khach: " << customerFullname << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << endl;
    cout << string(20, ' ') << "Ve da dat\n";
    ticket.printTicketInfo();
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
