#include "../../include/repository/AirplaneRepository.h"

/**********************************************************
* @Description Constructor AirplaneRepository
* @return  Pointer trỏ đến AirplaneRepository vừa tạo
* @attention  Load toàn bộ dữ liệu máy bay từ file
**********************************************************/
AirplaneRepository::AirplaneRepository() {
    loadAllAirplanes();
}

/**********************************************************
* @Description Destructor AirplaneRepository
* @return  Không
* @attention  Giải phóng bộ nhớ các máy bay
* @attention  Lưu dữ liệu trước khi hủy
**********************************************************/
AirplaneRepository::~AirplaneRepository() {
    loadAllAirplanes(); // cap nhat du lieu moi nhat
    saveAllAirplanes(); // auto save

    // Giải phóng bộ nhớ để tránh leak
    for (const auto airplane : m_airplanes)
        delete airplane;
    m_airplanes.clear();
}

/**********************************************************
* @Description Thêm máy bay vào danh sách
* @param Airplane& airplane
* @return  Không
* @attention  Load trước và save sau khi thêm
**********************************************************/
void AirplaneRepository::add(const Airplane& airplane) {
    loadAllAirplanes();
    m_airplanes.add(new Airplane(airplane));
    saveAllAirplanes();
    loadAllAirplanes();
}

/**********************************************************
* @Description Xóa máy bay theo ID
* @param string& id
* @return  Không
* @attention  Nếu ID không tồn tại sẽ không làm gì
**********************************************************/
void AirplaneRepository::remove(const string& id) {
    loadAllAirplanes();
    auto it = findByID(id);
    if (it != undefineAirplane()) {
        delete *it;
        m_airplanes.remove(it);
    }
    saveAllAirplanes();
    loadAllAirplanes();
}

/**********************************************************
* @Description Tìm máy bay theo ID
* @param string& id
* @return  Pointer trỏ đến Airplane hoặc undefineAirplane() nếu không tìm thấy
**********************************************************/
Airplane **AirplaneRepository::findByID(const string &id) {
    loadAllAirplanes();
    for (auto it = m_airplanes.begin(); it != m_airplanes.end(); ++it) {
        if ((*it)->getID() == id)
            return it;
    }
    return undefineAirplane();
}

/**********************************************************
* @Description Lấy danh sách ghế của máy bay
* @param string& id
* @return  List<int> danh sách ghế: 0 = trống, 1 = đã đặt
**********************************************************/
List<int> AirplaneRepository::getSeatList(const string &id) {
    loadAllAirplanes();
    const auto it = findByID(id);
    List<int> result;

    if (it != undefineAirplane()) {
        auto seats = (*it)->getSeatList();
        for (const bool s : seats)
            result.add(s ? 1 : 0);
    }
    return result;
}

/**********************************************************
* @Description Lấy toàn bộ danh sách máy bay
* @return  Tham chiếu đến List<Airplane*>
**********************************************************/
List<Airplane *> &AirplaneRepository::getAll() {
    loadAllAirplanes();
    return m_airplanes;
}

/**********************************************************
* @Description Trả về iterator không tồn tại
* @return  Pointer trỏ đến end() của vector
**********************************************************/
Airplane **AirplaneRepository::undefineAirplane() {
    loadAllAirplanes();
    return m_airplanes.end();
}

/**********************************************************
* @Description Load toàn bộ dữ liệu máy bay từ file
* @return  Không
* @attention  Xóa dữ liệu cũ trước khi load
* @attention  Nếu file không mở được sẽ in lỗi ra cerr
**********************************************************/
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
        List<bool> seats;
        string strTemp;
        while (getline(spliter, strTemp, '|')) {
            seats.add(strTemp == "1" ? 1 : 0);
        }

        auto plane = new Airplane(id, seats); // Tạo đối tượng máy bay mới
        m_airplanes.add(plane); // Lưu con trỏ vào vector
    }

    reader.close();
}

/**********************************************************
* @Description Lưu toàn bộ dữ liệu máy bay ra file
* @return  Không
* @attention  Nếu file không mở được sẽ in lỗi ra cerr
**********************************************************/
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