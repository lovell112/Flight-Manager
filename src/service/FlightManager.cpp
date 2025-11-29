#include "../../include/service/FlightManager.h"

/**********************************************************
* @Description Lưu toàn bộ dữ liệu hiện có của hệ thống
* @return  Không
* @attention  Gọi lần lượt saveAll() của các repository
**********************************************************/
void FlightManager::saveData() const {
    m_flightRepository->saveAllFlights();
    m_ticketRepository->saveAllTickets();
    m_airplaneRepository->saveAllAirplanes();
    m_customerRepository->saveAllCustomers();
}

/**********************************************************
* @Description Load toàn bộ dữ liệu hiện có của hệ thống
* @return  Không
* @attention  Gọi lần lượt loadAll() của các repository
**********************************************************/
void FlightManager::loadData() const {
    m_flightRepository->loadAllFlights();
    m_ticketRepository->loadAllTickets();
    m_airplaneRepository->loadAllAirplanes();
    m_customerRepository->loadAllCustomers();
}


/**********************************************************
* @Description Constructor mặc định
* @return  Pointer trỏ đến FlightManager vừa tạo
* @attention  Tạo mới các repository mặc định
**********************************************************/
FlightManager::FlightManager() {
    m_flightRepository = new FlightRepository();
    m_ticketRepository = new TicketRepository();
    m_airplaneRepository = new AirplaneRepository();
    m_customerRepository = new CustomerRepository();
}

/**********************************************************
* @Description Constructor với repository có sẵn
* @param flightRepo Pointer repository chuyến bay
* @param ticketRepo Pointer repository vé
* @param airplaneRepo Pointer repository máy bay
* @param customerRepo Pointer repository khách hàng
* @return  Pointer trỏ đến FlightManager vừa tạo
**********************************************************/
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

/**********************************************************
* @Description Destructor
* @return  Không
* @attention  Giải phóng bộ nhớ của các repository
**********************************************************/
FlightManager::~FlightManager() {
    delete m_flightRepository;
    delete m_ticketRepository;
    delete m_airplaneRepository;
    delete m_customerRepository;
}

/**********************************************************
* @Description Lấy FlightRepository
* @return  Pointer trỏ đến FlightRepository
**********************************************************/
FlightRepository& FlightManager::getFlightRepository() const {
    return *m_flightRepository;
}

/**********************************************************
* @Description Lấy TicketRepository
* @return  Pointer trỏ đến TicketRepository
**********************************************************/
TicketRepository& FlightManager::getTicketRepository() const {
    return *m_ticketRepository;
}

/**********************************************************
* @Description Lấy AirplaneRepository
* @return  Pointer trỏ đến AirplaneRepository
**********************************************************/
AirplaneRepository& FlightManager::getAirplaneRepository() const {
    return *m_airplaneRepository;
}

/**********************************************************
* @Description Lấy CustomerRepository
* @return  Pointer trỏ đến CustomerRepository
**********************************************************/
CustomerRepository& FlightManager::getCustomerRepository() const {
    return *m_customerRepository;
}

/**********************************************************
* @Description Thêm chuyến bay mới vào hệ thống
* @param flight Chuyến bay cần thêm
* @return  Không
* @attention  Gọi add() trong FlightRepository, sau đó saveData() và loadData()
**********************************************************/
void FlightManager::addFlight(const Flight& flight) const {
    // Gọi hàm add() trong FlightRepository để thêm chuyến bay vào danh sách
    m_flightRepository->add(flight);

    saveData();
    loadData();
}

/**********************************************************
* @Description Hủy chuyến bay theo ID
* @param flightID ID chuyến bay cần hủy
* @return  Không
* @attention  Cập nhật trạng thái sang CANCELLED nếu tồn tại
**********************************************************/
void FlightManager::cancelFlight(const string& flightID) const {
    // Tìm chuyến bay có mã tương ứng
    auto it = m_flightRepository->findByID(flightID);

    // Nếu tìm thấy (Iterator không trỏ tới end)
    if (it != m_flightRepository->undefineFlight()) {
        // Cập nhật trạng thái chuyến bay sang "Cancelled"
        (*it)->setFlightStatus(FlightStatus::CANCELLED);

        cout << string(20, ' ') << "Da huy chuyen bay: " << flightID << endl;
    }
    else {
        // Nếu không tìm thấy, in thông báo lỗi
        cout << string(20, ' ') << "Khong tim thay chuyen bay.\n";
    }

    saveData();
    loadData();
}

/**********************************************************
* @Description Cập nhật trạng thái chuyến bay
* @param flightID ID chuyến bay cần cập nhật
* @param status Trạng thái mới
* @return  Không
**********************************************************/
void FlightManager::updateFlightStatus(const string& flightID, const FlightStatus& status) const {
    // Gọi hàm trong FlightRepository để thay đổi trạng thái
    m_flightRepository->setFlightStatus(flightID, status);

    saveData();
    loadData();
}

/**********************************************************
* @Description Tìm chuyến bay theo ID
* @param flightID ID chuyến bay
* @return  Pointer trỏ đến Flight object, hoặc undefineFlight() nếu không tồn tại
**********************************************************/
Flight **FlightManager::findFlightByID(const string &flightID) const {
    loadData();
    return m_flightRepository->findByID(flightID);
}

/**********************************************************
* @Description Tìm chuyến bay theo ngày khởi hành
* @param date Ngày khởi hành (string)
* @return  Danh sách con trỏ Flight* tương ứng
**********************************************************/
List<Flight *> FlightManager::findFlightByDate(const string &date) const {
    loadData();
    // Gọi hàm trong FlightRepository, trả danh sách con theo ngày
    return m_flightRepository->findByDate(date);
}

/**********************************************************
* @Description Tìm chuyến bay theo điểm đến
* @param destination Điểm đến
* @return  Danh sách con trỏ Flight* tương ứng
**********************************************************/
List<Flight *> FlightManager::findFlightByDestination(const string &destination) const {
    loadData();
    return m_flightRepository->findByDestination(destination);
}

/**********************************************************
* @Description Đếm số chuyến bay sử dụng 1 máy bay
* @param airplaneID ID máy bay
* @return  Số lượng chuyến bay
**********************************************************/
int FlightManager::countFlightOfOneAirplane(const string &airplaneID) const {
    loadData();
    int count = 0;
    for (const auto& flight : m_flightRepository->getAll()) {
        if (flight->getAirplaneID() == airplaneID)
            count++;
    }

    return count;
}

/**********************************************************
* @Description Lấy danh sách ghế của chuyến bay
* @param flightID ID chuyến bay
* @return  Danh sách int: 0 = trống, 1 = đã đặt
* @attention  Trả về danh sách rỗng nếu chuyến bay không tồn tại
**********************************************************/
List<int> FlightManager::getSeats(const string &flightID) const {
    loadData();
    // Tìm chuyến bay theo ID
    auto flightIt = m_flightRepository->findByID(flightID);

    // Nếu chuyến bay tồn tại
    if (flightIt != m_flightRepository->undefineFlight()) {
        // Lấy mã máy bay gắn với chuyến bay này
        const string airplaneID = (*flightIt)->getAirplaneID();

        // Truy cập sang AirplaneRepository để lấy danh sách ghế
        // Trả về vector<int> biểu diễn trạng thái từng ghế (0 = trống, 1 = đã đặt)
        return m_airplaneRepository->getSeatList(airplaneID);
    }

    // Nếu không tìm thấy chuyến bay
    cout << "Khong tim thay chuyen bay: " << flightID << endl;
    return {}; // Trả vector rỗng
}

/**********************************************************
* @Description Lấy danh sách ghế trống của chuyến bay
* @param flightID ID chuyến bay
* @return  Danh sách số ghế trống (1-based)
**********************************************************/
List<int> FlightManager::getAvailableSeat(const string &flightID) const {
    const auto flight = m_flightRepository->findByID(flightID);
    if (flight == m_flightRepository->undefineFlight())
        return{};

    const auto airplane = m_airplaneRepository->findByID((*flight)->getAirplaneID());
    if (airplane == m_airplaneRepository->undefineAirplane())
        return{};

    auto seats = (*airplane)->getSeatList();
    List<int> res;
    for (int i = 0; i < seats.size(); i++) {
        if (!seats[i]) {
            res.add(i+1);
        }
    }
    return res;
}

/**********************************************************
* @Description Lấy tất cả chuyến bay của một máy bay
* @param airplaneID ID máy bay
* @return  Danh sách con trỏ Flight* sử dụng máy bay đó
**********************************************************/
List<Flight *> FlightManager::findFlightQuantityOfAirplane(const string &airplaneID) const {
    List<Flight *> res;
    for (auto flight : m_flightRepository->getAll()) {
        if (flight->getAirplaneID() == airplaneID)
            res.add(flight);
    }

    return res;
}



/**********************************************************
* @Description Lấy toàn bộ chuyến bay hiện có trong hệ thống
* @return  Tham chiếu đến danh sách Flight*
**********************************************************/
List<Flight *> &FlightManager::getAllFlight() const {
    loadData();
    return m_flightRepository->getAll();
}