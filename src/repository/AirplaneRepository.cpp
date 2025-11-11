#include "../../include/repository/AirplaneRepository.h"

// ===== Constructor =====
AirplaneRepository::AirplaneRepository() {
    loadAllAirplanes();
}

// ===== Destructor =====
AirplaneRepository::~AirplaneRepository() {
    loadAllAirplanes(); // cap nhat du lieu moi nhat
    saveAllAirplanes(); // auto save

    // Giải phóng bộ nhớ để tránh leak
    for (auto airplane : m_airplanes)
        delete airplane;
    m_airplanes.clear();
}

// ====== Thêm máy bay ======
void AirplaneRepository::add(const Airplane& airplane) {
    loadAllAirplanes();
    m_airplanes.push_back(new Airplane(airplane));
    saveAllAirplanes();
    loadAllAirplanes();
}

// ====== Xóa máy bay theo ID ======
void AirplaneRepository::remove(const string& id) {
    loadAllAirplanes();
    auto it = findByID(id);
    if (it != undefineAirplane()) {
        delete *it;
        m_airplanes.erase(it);
    }
    saveAllAirplanes();
    loadAllAirplanes();
}

// ====== Tìm máy bay theo ID ======
vector<Airplane*>::iterator AirplaneRepository::findByID(const string& id) {
    loadAllAirplanes();
    for (auto it = m_airplanes.begin(); it != m_airplanes.end(); ++it) {
        if ((*it)->getID() == id)
            return it;
    }
    return undefineAirplane();
}



// ====== Lấy danh sách ghế của máy bay ======
vector<int> AirplaneRepository::getSeatList(const string& id) {
    loadAllAirplanes();
    auto it = findByID(id);
    vector<int> result;

    if (it != undefineAirplane()) {
        vector<bool> seats = (*it)->getSeatList();
        for (bool s : seats)
            result.push_back(s ? 1 : 0);
    }
    return result;
}

// ====== Lấy toàn bộ danh sách ======
vector<Airplane*>& AirplaneRepository::getAll() {
    loadAllAirplanes();
    return m_airplanes;
}

// tra ve 1 doi tuong khong ton tai theo dang iterator - o day se la iterator end
const vector<Airplane *>::iterator AirplaneRepository::undefineAirplane() {
    loadAllAirplanes();
    return m_airplanes.end();
}

// ====== Load dữ liệu từ file ======
void AirplaneRepository::loadAllAirplanes() {
    ifstream reader(PATH);
    if (!reader.is_open()) {
        cerr << "Không thể mở file airplane.txt để đọc.\n";
        return;
    }

    for (auto& plane :m_airplanes)
        delete plane;
    m_airplanes.clear();

    string line;
    while (getline(reader, line)) {
        if (line.empty())
            continue;
        stringstream spliter(line);
        string id;
        int seatCount;

        getline(spliter, id, '|');  // Tách phần ID trước dấu '|'
        vector<bool> seats;
        string strTemp;
        while (getline(spliter, strTemp, '|')) {
            seats.push_back(strTemp == "1" ? 1 : 0);
        }

        Airplane* plane = new Airplane(id, seats); // Tạo đối tượng máy bay mới
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
        writer << plane->toString() << endl;
    }

    writer.close();
}