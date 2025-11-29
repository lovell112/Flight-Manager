#include "../../include/core/Airplane.h"

#include <list>

// =========================================================
//                     CONSTRUCTOR
// =========================================================

/**********************************************************
 * @Description Constructor mặc định – khởi tạo máy bay rỗng
 **********************************************************/
Airplane::Airplane() {
    m_strID = "";
    m_iSeatCount = 0;
    m_iEmptySeatCount = 0;
    m_seatList = List<bool>(); // danh sách ghế trống rỗng
}

/**********************************************************
 * @Description Constructor khởi tạo với ID và danh sách ghế
 * @param id        Mã số máy bay
 * @param seats     Danh sách trạng thái ghế
 **********************************************************/
Airplane::Airplane(const string& id, const List<bool>& seats) : m_strID(id), m_seatList(seats) {
    m_iSeatCount = m_seatList.size();
    m_iEmptySeatCount = m_iSeatCount;
    for (const auto seat : m_seatList)
        if (seat)
            m_iEmptySeatCount--;
}

// =========================================================
//                     DESTRUCTOR
// =========================================================

/**********************************************************
 * @Description Destructor – không cần xử lý đặc biệt
 **********************************************************/
Airplane::~Airplane() {}

// =========================================================
//                          GETTER
// =========================================================

/**********************************************************
 * @return Mã số máy bay
 **********************************************************/
string Airplane::getID() const {
    return m_strID;
}

/**********************************************************
 * @return Tổng số ghế
 **********************************************************/
int Airplane::getSeatCount() const {
    return m_iSeatCount;
}

/**********************************************************
 * @return Tham chiếu danh sách ghế
 **********************************************************/
List<bool>& Airplane::getSeatList() {
    return m_seatList;
}

// =========================================================
//                          SETTER
// =========================================================

/**********************************************************
 * @Description Cập nhật tổng số ghế và đồng bộ danh sách ghế
 * @attention   Nếu tăng số ghế → thêm ghế trống (false)
 *              Nếu giảm → cắt bớt phần thừa
 **********************************************************/
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

/**********************************************************
 * @Description Đặt một ghế
 * @attention   seatNumber bắt đầu từ 1, ghế phải trống
 **********************************************************/
void Airplane::bookSeat(const int seatNumber) {
    if (seatNumber-1 < 0 || seatNumber-1 >= m_seatList.size() || m_seatList[seatNumber-1])
        return;

    m_seatList[seatNumber-1] = true;
    m_iEmptySeatCount--;
}

/**********************************************************
 * @Description Hủy đặt ghế
 * @attention   seatNumber hợp lệ và ghế phải đang được đặt
 **********************************************************/
void Airplane::cancelSeat(const int seatNumber) {
    if (seatNumber-1 < 0 || seatNumber-1 >= m_seatList.size() || !m_seatList[seatNumber-1])
        return;

    m_seatList[seatNumber-1] = false;
    m_iEmptySeatCount++;
}


// =========================================================
//                         LOGIC METHODS
// =========================================================

/**********************************************************
 * @return Chuỗi mô tả máy bay và trạng thái ghế, dạng:
 *         ID|1|0|1|0|...
 **********************************************************/
string Airplane::toString() const {
    string info = m_strID;

    for (const bool seat : m_seatList)
        info += "|" + string(seat ? "1" : "0");
    return info;
}

/**********************************************************
 * @Description Kiểm tra ghế có trống hay không
 * @return true nếu ghế hợp lệ và đang trống
 **********************************************************/
bool Airplane::isSeatAvailable(const int seatNumber) const {
    if (seatNumber < 0 || seatNumber-1 >= m_seatList.size())
        return false;
    return !m_seatList[seatNumber-1];
}

/**********************************************************
 * @Description In toàn bộ thông tin máy bay
 **********************************************************/
void Airplane::printAirplaneInfo() const {
    cout << toString() << endl;
}
