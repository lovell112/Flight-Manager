//
// Created by HP on 05/11/2025.
//
#include "../../include/service/FlightManager.h"

// ====================== Constructor ======================
FlightManager::FlightManager(FlightRepository* flightRepo,
                             TicketRepository* ticketRepo,
                             AirplaneRepository* airplaneRepo)
{
    m_flightRepository = flightRepo;       // Repository chứa danh sách chuyến bay
    m_ticketRepository = ticketRepo;       // Repository chứa danh sách vé
    m_airplaneRepository = airplaneRepo;   // Repository chứa danh sách máy bay
}

// ====================== Destructor ======================
FlightManager::~FlightManager() {}

// ====================== Thêm chuyến bay mới ======================
void FlightManager::addFlight(const Flight& flight) const{
    // Gọi hàm add() trong FlightRepository để thêm chuyến bay vào danh sách
    m_flightRepository->add(flight);
}

// ====================== Hủy chuyến bay theo ID ======================
void FlightManager::cancelFlight(const string& flightID) const{
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
}

// ====================== Cập nhật trạng thái chuyến bay ======================
void FlightManager::updateFlightStatus(const string& flightID, const FlightStatus& status) const{
    // Gọi hàm trong FlightRepository để thay đổi trạng thái
    m_flightRepository->setFlightStatus(flightID, status);
}

// ====================== Tìm chuyến bay theo ID ======================
// Trả về iterator trỏ tới vị trí chuyến bay trong danh sách
vector<Flight*>::iterator FlightManager::findFlightByID(const string& flightID) const{
    return m_flightRepository->findByID(flightID);
}

// ====================== Tìm chuyến bay theo ngày khởi hành ======================
vector<Flight*> FlightManager::findFlightByDate(const string& date) const{
    // Gọi hàm trong FlightRepository, trả danh sách con theo ngày
    return m_flightRepository->findByDate(date);
}

// ====================== Tìm chuyến bay theo điểm đến ======================
vector<Flight*> FlightManager::findFlightByDestination(const string& destination) const{
    return m_flightRepository->findByDestination(destination);
}

// ====================== Lấy danh sách ghế trống của chuyến bay ======================
vector<int> FlightManager::getAvailableSeats(const string& flightID) const {
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

// ====================== Lấy tất cả chuyến bay hiện có trong hệ thống ======================
vector<Flight*>& FlightManager::getAllFlight() const {
    return m_flightRepository->getAll();
}