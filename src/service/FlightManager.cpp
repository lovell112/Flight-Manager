#include "../../include/service/FlightManager.h"

void FlightManager::saveData() {
    m_flightRepository->saveAllFlights();
    m_ticketRepository->saveAllTickets();
    m_airplaneRepository->saveAllAirplanes();
    m_customerRepository->saveAllCustomers();
}

void FlightManager::loadData() {
    m_flightRepository->loadAllFlights();
    m_ticketRepository->loadAllTickets();
    m_airplaneRepository->loadAllAirplanes();
    m_customerRepository->loadAllCustomers();
}


// ====================== Constructor ======================
FlightManager::FlightManager() {
    m_flightRepository = new FlightRepository();
    m_ticketRepository = new TicketRepository();
    m_airplaneRepository = new AirplaneRepository();
    m_customerRepository = new CustomerRepository();
}

FlightManager::FlightManager(FlightRepository* flightRepo,
                             TicketRepository* ticketRepo,
                             AirplaneRepository* airplaneRepo,
                             CustomerRepository* customerRepo)
{
    m_flightRepository = flightRepo;       // Repository chứa danh sách chuyến bay
    m_ticketRepository = ticketRepo;       // Repository chứa danh sách vé
    m_airplaneRepository = airplaneRepo;   // Repository chứa danh sách máy bay
    m_customerRepository = customerRepo;
}

// ====================== Destructor ======================
FlightManager::~FlightManager() {
    delete m_flightRepository;
    delete m_ticketRepository;
    delete m_airplaneRepository;
    delete m_customerRepository;
}

// ====================== Thêm chuyến bay mới ======================
void FlightManager::addFlight(const Flight& flight){
    // Gọi hàm add() trong FlightRepository để thêm chuyến bay vào danh sách
    m_flightRepository->add(flight);

    saveData();
    loadData();
}

// ====================== Hủy chuyến bay theo ID ======================
void FlightManager::cancelFlight(const string& flightID){
    // Tìm chuyến bay có mã tương ứng
    auto it = m_flightRepository->findByID(flightID);

    // Nếu tìm thấy (iterator không trỏ tới end)
    if (it != m_flightRepository->undefineFlight()) {
        // Cập nhật trạng thái chuyến bay sang "Cancelled"
        (*it)->setFlightStatus(FlightStatus::CANCELLED);

        cout << "Đã hủy chuyến bay: " << flightID << endl;
    }
    else {
        // Nếu không tìm thấy, in thông báo lỗi
        cerr << "Không tìm thấy chuyến bay cần hủy.\n";
    }

    saveData();
    loadData();
}

// ====================== Cập nhật trạng thái chuyến bay ======================
void FlightManager::updateFlightStatus(const string& flightID, const FlightStatus& status){
    // Gọi hàm trong FlightRepository để thay đổi trạng thái
    m_flightRepository->setFlightStatus(flightID, status);

    saveData();
    loadData();
}

// ====================== Tìm chuyến bay theo ID ======================
// Trả về iterator trỏ tới vị trí chuyến bay trong danh sách
vector<Flight*>::iterator FlightManager::findFlightByID(const string& flightID){
    loadData();
    return m_flightRepository->findByID(flightID);
}

// ====================== Tìm chuyến bay theo ngày khởi hành ======================
vector<Flight*> FlightManager::findFlightByDate(const string& date) {
    loadData();
    // Gọi hàm trong FlightRepository, trả danh sách con theo ngày
    return m_flightRepository->findByDate(date);
}

// ====================== Tìm chuyến bay theo điểm đến ======================
vector<Flight*> FlightManager::findFlightByDestination(const string& destination){
    loadData();
    return m_flightRepository->findByDestination(destination);
}

int FlightManager::countFlightOfOneAirplane(const string &airplaneID) {
    loadData();
    int count = 0;
    for (const auto& flight : m_flightRepository->getAll()) {
        if (flight->getAirplaneID() == airplaneID)
            count++;
    }

    return count;
}




// ====================== Lấy danh sách ghế của chuyến bay ======================
vector<int> FlightManager::getSeats(const string& flightID) {
    loadData();
    // Tìm chuyến bay theo ID
    auto flightIt = m_flightRepository->findByID(flightID);

    // Nếu chuyến bay tồn tại
    if (flightIt != m_flightRepository->undefineFlight()) {
        // Lấy mã máy bay gắn với chuyến bay này
        string airplaneID = (*flightIt)->getAirplaneID();

        // Truy cập sang AirplaneRepository để lấy danh sách ghế
        // Trả về vector<int> biểu diễn trạng thái từng ghế (0 = trống, 1 = đã đặt)
        return m_airplaneRepository->getSeatList(airplaneID);
    }

    // Nếu không tìm thấy chuyến bay
    cerr << "Không tìm thấy chuyến bay: " << flightID << endl;
    return {}; // Trả vector rỗng
}

vector<int> FlightManager::getAvailableSeat(const string &flightID) {
    auto flight = m_flightRepository->findByID(flightID);
    if (flight == m_flightRepository->undefineFlight())
        return{};

    auto airplane = m_airplaneRepository->findByID((*flight)->getAirplaneID());
    if (airplane == m_airplaneRepository->undefineAirplane())
        return{};

    auto seats = (*airplane)->getSeatList();
    vector<int> res;
    for (int i = 0; i < seats.size(); i++) {
        if (!seats[i]) {
            res.push_back(i+1);
        }
    }
    return res;
}

vector<Flight *> FlightManager::findFlightQuantityOfAirplane(const string &airplaneID) {
    vector<Flight *> res;
    for (auto flight : m_flightRepository->getAll()) {
        if (flight->getAirplaneID() == airplaneID)
            res.push_back(flight);
    }

    return res;
}



// ====================== Lấy tất cả chuyến bay hiện có trong hệ thống ======================
vector<Flight*>& FlightManager::getAllFlight() {
    loadData();
    return m_flightRepository->getAll();
}