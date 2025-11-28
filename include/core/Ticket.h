#ifndef AIRPLANEMANAGER_TICKET_H
#define AIRPLANEMANAGER_TICKET_H

#include <iostream>
#include <string>
using namespace std;

/************************************************************
 * @Description  Lớp Ticket đại diện cho một vé máy bay.
 *               Bao gồm thông tin: mã vé, mã chuyến bay,
 *               mã khách hàng, tên khách hàng và số ghế.
 ************************************************************/
class Ticket {
    string m_strTicketID;
    string m_strFlightID;
    string m_strCustomerID;
    string m_strCustomerName;
    int m_iSeatNumber;

public:

    /********************************************************
     * @Description  Khởi tạo đối tượng Ticket
     *
     * @attention    Tất cả tham số truyền vào phải hợp lệ
     ********************************************************/
    Ticket(const string&, const string&, const string&, const string&, int);

    /********************************************************
     * @Description  Destructor giải phóng tài nguyên (nếu có)
     ********************************************************/
    ~Ticket();

    /********************************************************
     * @Description  Lấy mã vé
     * @return       Chuỗi mã vé
     ********************************************************/
    [[nodiscard]] const string& getTicketID() const;

    /********************************************************
     * @Description  Lấy mã chuyến bay
     * @return       Chuỗi mã chuyến bay
     ********************************************************/
    [[nodiscard]] const string& getFlightID() const;

    /********************************************************
     * @Description  Lấy mã khách hàng
     * @return       Chuỗi mã khách hàng
     ********************************************************/
    [[nodiscard]] const string& getCustomerID() const;

    /********************************************************
     * @Description  Lấy tên khách hàng
     * @return       Chuỗi tên khách hàng
     ********************************************************/
    [[nodiscard]] const string& getCustomerName() const;

    /********************************************************
     * @Description  Lấy số ghế
     * @return       Số ghế (int)
     ********************************************************/
    [[nodiscard]] int getSeatNumber() const;

    /********************************************************
     * @Description  Gán mã vé mới
     ********************************************************/
    void setTicketID(const string&);

    /********************************************************
     * @Description  Gán mã chuyến bay mới
     ********************************************************/
    void setFlightID(const string&);

    /********************************************************
     * @Description  Gán mã khách hàng mới
     ********************************************************/
    void setCustomerID(const string&);

    /********************************************************
     * @Description  Gán tên khách hàng mới
     ********************************************************/
    void setCustomerName(const string&);

    /********************************************************
     * @Description  Gán số ghế mới
     ********************************************************/
    void setSeatNumber(int);

    /********************************************************
     * @Description  Trả về thông tin vé dạng chuỗi để lưu file
     * @return       Chuỗi chứa dữ liệu dạng: ID|Flight|Customer|Name|Seat
     ********************************************************/
    [[nodiscard]] string toString() const;

    /********************************************************
     * @Description  In thông tin vé theo định dạng bảng
     ********************************************************/
    void printTicketInfo() const;

    /********************************************************
     * @Description  So sánh hai vé (so sánh theo TicketID)
     * @return       true nếu trùng mã vé, ngược lại false
     ********************************************************/
    bool operator==(const Ticket &) const;
};

#endif //AIRPLANEMANAGER_TICKET_H
