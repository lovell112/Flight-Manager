#include "../../include/core/Airplane.h"

// ===== Constructor =====
Airplane::Airplane() {
    m_strID = "";
    m_iSeatCount = 0;
    m_iEmptySeatCount = 0;
    m_seatList = vector<bool>(); // danh sách ghế trống rỗng
}
Airplane::Airplane(const string& id, int seatCount) {
    m_strID = id;
    m_iSeatCount = seatCount;
    m_iEmptySeatCount = seatCount;
    //Tạo danh sách ghế trống (false = ghế trống)
    m_seatList.assign(seatCount, false);
}

// ==== Destructor =====
Airplane::~Airplane() {}

// ==== Getter ====
string Airplane::getID() const {
    return m_strID;
}

int Airplane::getSeatCount() const {
    return m_iSeatCount;
}

vector<bool>& Airplane::getSeatList() {
    return m_seatList;
}

// ===== Setter =====
void Airplane::setSeatCount(int count) {
    // Cập nhật tổng số ghế
    m_iSeatCount = count;

    // Nếu danh sách hiện tại ít ghế hơn => thêm ghế trống (false)
    if (m_seatList.size() < count) {
        m_seatList.resize(count, false);
    }
    // Nếu danh sách hiện tại nhiều ghế hơn => cắt bớt phần thừa
    else if (m_seatList.size() > count) {
        m_seatList.resize(count);
    }

    // Đếm lại số ghế trống (false)
    int emptyCount = 0;
    for (bool seat : m_seatList) {
        if (!seat) emptyCount++;  // false = ghế trống
    }
    m_iEmptySeatCount = emptyCount;
}

// ====Logic====
string Airplane::toString() const {
    string info = m_strID;

    for (bool seat : m_seatList)
        info += "|" + string(seat ? "1" : "0");
    return info;
}


void Airplane::printAirplaneInfo() const {
    cout << toString() << endl;
}
