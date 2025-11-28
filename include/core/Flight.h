//
// Created by HP on 05/11/2025.
//

#ifndef FLIGHTMANAGER_FLIGHT_H
#define FLIGHTMANAGER_FLIGHT_H

#include <string>
#include "../datastructures/List.hpp"
#include <iostream>
#include "../../include/core/FlightStatus.h"
#include "../../include/core/Ticket.h"
#include "../../include/core/DateTime.h"

using namespace std;

/**
 * @class Flight
 * @brief Xây dựng mô hình dữ liệu cho chuyến bay
 */
class Flight {
private:
    string m_strFlightID;
    string m_strAirplaneID;
    string m_strDestinationAirport;
    DateTime* m_departureDate;
    FlightStatus m_status;
    List<string> m_tickets;

public:

    /*********************************************************
     * @brief Constructor mặc định
     * @details Tạo đối tượng Flight với các giá trị rỗng
     *********************************************************/
    Flight() = default;

    /*********************************************************
     * @brief Constructor đầy đủ tham số
     * @details Khởi tạo đầy đủ thông tin cho chuyến bay
     * @attention departure là chuỗi và sẽ được chuyển sang DateTime
     *********************************************************/
    Flight(const string &flightID,
           const string &airplaneID,
           const string &destination,
           const string &departure,
           const FlightStatus &status,
           const List<string> &tickets);

    /*********************************************************
     * @brief Destructor
     * @details Giải phóng vùng nhớ của DateTime*
     *********************************************************/
    ~Flight();

    /*********************************************************
     * @brief Lấy mã chuyến bay
     * @return const string& mã chuyến bay
     * @details Sử dụng để định danh chuyến bay
     *********************************************************/
    [[nodiscard]] const string& getFlightID() const;

    /*********************************************************
     * @brief Lấy mã máy bay
     * @return const string& mã máy bay
     *********************************************************/
    [[nodiscard]] const string& getAirplaneID() const;

    /*********************************************************
     * @brief Lấy sân bay đến
     * @return const string& mã sân bay
     *********************************************************/
    [[nodiscard]] const string& getDestinationAirport() const;

    /*********************************************************
     * @brief Lấy ngày khởi hành
     * @return const DateTime& ngày giờ khởi hành
     *********************************************************/
    [[nodiscard]] const DateTime& getDepartureDate() const;

    /*********************************************************
     * @brief Lấy trạng thái chuyến bay
     * @return const FlightStatus& trạng thái chuyến bay
     *********************************************************/
    [[nodiscard]] const FlightStatus& getStatus() const;

    /*********************************************************
     * @brief Lấy danh sách mã vé
     * @return List<string>& danh sách mã vé
     *********************************************************/
    List<string>& getTickets();

    /*********************************************************
     * @brief Gán mã chuyến bay
     * @details Gán giá trị mới cho FlightID
     *********************************************************/
    void setFlightID(const string&);

    /*********************************************************
     * @brief Gán mã máy bay
     * @details Phải là mã máy bay hợp lệ trong hệ thống
     *********************************************************/
    void setAirplaneID(const string&);

    /*********************************************************
     * @brief Gán sân bay đến
     * @details Gán giá trị mới cho DestinationAirport
     *********************************************************/
    void setDestinationAirport(const string&);

    /*********************************************************
     * @brief Gán ngày khởi hành
     * @details Chuỗi ngày giờ sẽ được parse sang DateTime
     *********************************************************/
    void setDepartureDate(const string&) const;

    /*********************************************************
     * @brief Gán trạng thái chuyến bay
     * @details Ready, Pending, Flying, Cancelled...
     *********************************************************/
    void setFlightStatus(const FlightStatus&);

    /*********************************************************
     * @brief Thêm vé cho chuyến bay
     * @details Chỉ thêm nếu mã vé chưa tồn tại
     *********************************************************/
    void addTicket(const string&);

    /*********************************************************
     * @brief Xóa vé khỏi chuyến bay
     * @details Không làm gì nếu không tìm thấy mã vé
     *********************************************************/
    void removeTicket(const string&);

    /*********************************************************
     * @brief Chuyển dữ liệu chuyến bay thành chuỗi
     * @return string chứa thông tin chuyến bay
     * @details Dùng cho ghi file hoặc debug
     *********************************************************/
    [[nodiscard]] string toString() const;

    /*********************************************************
     * @brief In thông tin chuyến bay ra console
     * @details Sử dụng để debug
     *********************************************************/
    void printFlightInfo() const;
};

#endif // FLIGHTMANAGER_FLIGHT_H
