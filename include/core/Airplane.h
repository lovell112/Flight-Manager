#ifndef AIRPLANEMANAGER_AIRPLANE_H
#define AIRPLANEMANAGER_AIRPLANE_H
#include <iostream>
#include "../datastructures/List.hpp"
#include <string>
using namespace std;

/**********************************************************
 * @Class       Airplane
 * @Description Đại diện 1 máy bay: ID, số ghế, số ghế trống
 *              và danh sách trạng thái ghế.
 **********************************************************/
class Airplane {
    string m_strID;
    int m_iSeatCount;
    int m_iEmptySeatCount;
    List<bool> m_seatList;
public:
    /**********************************************************
     * @Description Constructor mặc định
     **********************************************************/
    Airplane();

    /**********************************************************
    * @Description Constructor khởi tạo từ ID + danh sách ghế
    **********************************************************/
    Airplane(const string&, const List<bool>&);

    /**********************************************************
    * @Description Destructor giải phóng dữ liệu
    **********************************************************/
    ~Airplane();

    // ================== Getter ==================

    /**********************************************************
     * @return ID của máy bay
     **********************************************************/
    [[nodiscard]] string getID() const;

    /**********************************************************
     * @return Tổng số ghế máy bay
     **********************************************************/
    [[nodiscard]] int getSeatCount() const;

    /**********************************************************
     * @return Danh sách trạng thái ghế (tham chiếu)
     **********************************************************/
    List<bool>& getSeatList();

    // ================== Setter ==================

    /**********************************************************
     * @Description Cập nhật số lượng ghế của máy bay
     **********************************************************/
    void setSeatCount(int);

    /**********************************************************
     * @Description Đặt ghế (đánh dấu ghế đã đặt)
     * @attention   seatIndex hợp lệ, ghế phải đang trống
     **********************************************************/
    void bookSeat(int);

    /**********************************************************
     * @Description Hủy ghế đã đặt
     * @attention   seatIndex hợp lệ
     **********************************************************/
    void cancelSeat(int);

     // ================== Logic ==================

    /**********************************************************
     * @return Chuỗi thông tin máy bay phục vụ debug / hiển thị
     **********************************************************/
    [[nodiscard]] string toString() const;

    /**********************************************************
     * @return true nếu ghế trống, false nếu đã đặt / index sai
     **********************************************************/
    [[nodiscard]] bool isSeatAvailable(int) const;

    /**********************************************************
     * @Description In thông tin máy bay ra console
     **********************************************************/
    void printAirplaneInfo() const;
};

#endif //AIRPLANEMANAGER_AIRPLANE_H