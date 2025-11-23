#include "../../include/core/Airplane.h"

#include <list>

// ===== Constructor =====
Airplane::Airplane() {
    m_strID = "";
    m_iSeatCount = 0;
    m_iEmptySeatCount = 0;
    m_seatList = List<bool>(); // danh sách ghế trống rỗng
}
Airplane::Airplane(const string& id, const List<bool>& seats) : m_strID(id), m_seatList(seats) {
    m_iSeatCount = m_seatList.size();
    m_iEmptySeatCount = m_iSeatCount;
    for (const auto seat : m_seatList)
        if (seat)
            m_iEmptySeatCount--;
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

List<bool>& Airplane::getSeatList() {
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
    for (const bool seat : m_seatList) {
        if (!seat) emptyCount++;  // false = ghế trống
    }
    m_iEmptySeatCount = emptyCount;
}

void Airplane::bookSeat(const int seatNumber) {
    if (seatNumber-1 < 0 || seatNumber-1 >= m_seatList.size() || m_seatList[seatNumber-1])
        return;

    m_seatList[seatNumber-1] = true;
    m_iEmptySeatCount--;
}

void Airplane::cancelSeat(const int seatNumber) {
    if (seatNumber-1 < 0 || seatNumber-1 >= m_seatList.size() || !m_seatList[seatNumber-1])
        return;

    m_seatList[seatNumber-1] = false;
    m_iEmptySeatCount++;
}


// ====Logic====
string Airplane::toString() const {
    string info = m_strID;

    for (const bool seat : m_seatList)
        info += "|" + string(seat ? "1" : "0");
    return info;
}

// neu ghe khong hop le hoac da duoc dat return false, nguoc lai true. m_seatList[0] = false = ghe thu 0 trong
bool Airplane::isSeatAvailable(const int seatNumber) const {
    if (seatNumber < 0 || seatNumber-1 >= m_seatList.size())
        return false;
    return !m_seatList[seatNumber-1];
}



void Airplane::printAirplaneInfo() const {
    cout << toString() << endl;
}
