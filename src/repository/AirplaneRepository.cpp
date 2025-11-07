#include "../../include/repository/AirplaneRepository.h"

// ===== Constructor =====
AirplaneRepository::AirplaneRepository() {
    loadAllAirplanes();
}

// ===== Destructor =====
AirplaneRepository::~AirplaneRepository() {
    saveAllAirplanes();

    // Giải phóng bộ nhớ để tránh leak
    for (auto airplane : m_airplanes)
        delete airplane;
    m_airplanes.clear();
}

// ====== Thêm máy bay ======
void AirplaneRepository::add(const Airplane& airplane) {
    m_airplanes.push_back(new Airplane(airplane));
}

// ====== Xóa máy bay theo ID ======
void AirplaneRepository::remove(const string& id) {
    auto it = findByID(id);
    if (it != m_airplanes.end()) {
        delete *it;
        m_airplanes.erase(it);
    }
}

// ====== Tìm máy bay theo ID ======
vector<Airplane*>::iterator AirplaneRepository::findByID(const string& id) {
    for (auto it = m_airplanes.begin(); it != m_airplanes.end(); ++it) {
        if ((*it)->getID() == id)
            return it;
    }
    return m_airplanes.end();
}

// ====== Lấy danh sách ghế của máy bay ======
vector<int> AirplaneRepository::getSeatList(const string& id) {
    auto it = findByID(id);
    vector<int> result;

    if (it != m_airplanes.end()) {
        vector<bool> seats = (*it)->getSeatList();
        for (bool s : seats)
            result.push_back(s ? 1 : 0);
    }
    return result;
}

// ====== Lấy toàn bộ danh sách ======
vector<Airplane*>& AirplaneRepository::getAll() {
    return m_airplanes;
}

// ====== Load dữ liệu từ file ======
void AirplaneRepository::loadAllAirplanes() {
    ifstream reader(PATH);
    if (!reader.is_open()) {
        cerr << "Không thể mở file airplane.txt để đọc.\n";
        return;
    }

    string line;
    while (getline(reader, line)) {
        stringstream ss(line);
        string id;
        int seatCount;

        getline(ss, id, '|');  // Tách phần ID trước dấu '|'
        ss >> seatCount;       // Đọc tiếp số lượng ghế

        Airplane* plane = new Airplane(id, seatCount); // Tạo đối tượng máy bay mới
        m_airplanes.push_back(plane); // Lưu con trỏ vào vector
    }

    reader.close();
}

// ====== Lưu dữ liệu xuống file ======
void AirplaneRepository::saveAllAirplanes() const {
    ofstream writer(PATH);
    if (!writer.is_open()) {
        cerr << "Không thể mở file airplane.txt để ghi.\n";
        return;
    }

    for (const auto& plane : m_airplanes) {
        writer << plane->getID() << "|" << plane->getSeatCount() << endl;
    }

    writer.close();
}