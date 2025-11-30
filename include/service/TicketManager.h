/*******************************************************************************
 * @file TicketManager.h
 * @brief Lớp điều phối xử lý nghiệp vụ liên quan đến vé máy bay
 *******************************************************************************/

#ifndef AIRPLANEMANAGER_TICKETMANAGER_H
#define AIRPLANEMANAGER_TICKETMANAGER_H

#include <queue>

#include "../repository/FlightRepository.h"
#include "../repository/TicketRepository.h"
#include "../repository/AirplaneRepository.h"
#include "../repository/TicketQueueRepository.h"
#include "CustomerService.h"

/**
 * @class TicketManager
 * @brief Lớp quản lý toàn bộ logic về vé: thêm, xoá, tìm kiếm, load/save dữ liệu.
 * @details Đây là tầng service sử dụng các repository để thao tác dữ liệu.
 */
class TicketManager {

    /***************************************************************************
     * @brief Con trỏ đến lớp quản lý vé
     ***************************************************************************/
    TicketRepository* m_ticketRepository;

    /***************************************************************************
     * @brief Con trỏ đến lớp quản lý chuyến bay
     ***************************************************************************/
    FlightRepository* m_flightRepository;

    /***************************************************************************
     * @brief Con trỏ đến lớp quản lý máy bay
     ***************************************************************************/
    AirplaneRepository* m_airplaneRepository;

    /***************************************************************************
     * @brief Con trỏ đến lớp quản lý queue đặt vé
     ***************************************************************************/
    TicketQueueRepository* m_ticketQueueRepository;

    /***************************************************************************
     * @brief Con trỏ đến lớp quản lý khách hàng
     ***************************************************************************/
    CustomerRepository* m_customerRepository;

    /***************************************************************************
     * @brief Lưu toàn bộ dữ liệu vào file
     * @details Gọi saveAll của từng repository
     ***************************************************************************/
    void saveData() const;

    /***************************************************************************
     * @brief Tải dữ liệu từ file
     * @details Gọi loadAll của từng repository
     ***************************************************************************/
    void loadData() const;

public:

    /*********************************************************
     * @brief Constructor
     * @details Khởi tạo các repository và load dữ liệu ban đầu
     *********************************************************/
    TicketManager();

    /*********************************************************
     * @brief Destructor
     * @details Giải phóng tất cả repository đã cấp phát động
     *********************************************************/
    ~TicketManager();

    /************************************************************************
     * @brief Thêm vé từ hàng đợi TicketQueue
     * @return boolean value: true nếu thêm thành công
     * @attention False nếu không có vé trong queue hoặc dữ liệu không hợp lệ
     ************************************************************************/
    void addTicketFromQueue() const;

    /************************************************************************
     * @brief Xoá vé đầu tiên trong TicketQueue
     * @details Đây là thao tác dequeue
     ************************************************************************/
    void removeTicketQueue() const;

    /************************************************************************
     * @brief Xoá vé theo TicketID
     * @param id - mã vé cần xoá
     * @details Tìm và xoá vé tương ứng trong TicketRepository
     ************************************************************************/
    void removeTicket(const string& id) const;

    /************************************************************************
     * @brief Tìm vé theo ngày bay
     * @param date - ngày muốn tìm (định dạng tùy bạn)
     * @return List<Ticket*> - danh sách vé khớp
     ************************************************************************/
    [[nodiscard]] List<Ticket*> findByDate(const string& date) const;

    /************************************************************************
     * @brief Tìm vé theo TicketID
     * @param id - mã vé
     * @return Ticket** - con trỏ đến phần tử trong List
     * @attention trả về nullptr nếu không tìm thấy
     ************************************************************************/
    [[nodiscard]] Ticket** findByID(const string& id) const;

    /************************************************************************
     * @brief Tìm vé theo điểm đến
     * @param destination - địa điểm hạ cánh
     * @return List<Ticket*> - danh sách vé thoả điều kiện
     ************************************************************************/
    [[nodiscard]] List<Ticket*> findByDestination(const string& destination) const;

    /************************************************************************
     * @brief Tìm vé theo FlightID
     * @param flightID - mã chuyến bay
     * @return List<Ticket*> danh sách vé thuộc chuyến bay đó
     ************************************************************************/
    [[nodiscard]] List<Ticket*> findByFlightID(const string& flightID) const;

    /************************************************************************
     * @brief Lấy repository vé
     * @return Tham chiếu TicketRepository
     ************************************************************************/
    [[nodiscard]] TicketRepository& getTicketRepository() const;

    /************************************************************************
     * @brief Lấy repository chuyến bay
     * @return Tham chiếu FlightRepository
     ************************************************************************/
    [[nodiscard]] FlightRepository& getFlightRepository() const;

    /************************************************************************
     * @brief Lấy repository máy bay
     * @return Tham chiếu AirplaneRepository
     ************************************************************************/
    [[nodiscard]] AirplaneRepository& getAirplaneRepository() const;

    /************************************************************************
     * @brief Lấy repository hàng đợi vé (TicketQueue)
     * @return Tham chiếu TicketQueueRepository
     ************************************************************************/
    [[nodiscard]] TicketQueueRepository& getTicketQueueRepository() const;
};

#endif //AIRPLANEMANAGER_TICKETMANAGER_H
