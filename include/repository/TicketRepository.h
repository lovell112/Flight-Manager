/*******************************************************************************
 * @file TicketRepository.h
 * @brief Khai báo lớp TicketRepository – quản lý dữ liệu vé máy bay
 *******************************************************************************/

#ifndef FLIGHTMANAGER_TICKETREPOSITORY_H
#define FLIGHTMANAGER_TICKETREPOSITORY_H

#include "../core/Ticket.h"
#include "../datastructures/List.hpp"
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>

using namespace std;

/**
 * @class TicketRepository
 * @brief Quản lý danh sách vé (Ticket), hỗ trợ thêm, xoá, tìm kiếm, lưu và tải dữ liệu
 */
class TicketRepository {

    /***************************************************************************
     * @brief Danh sách chứa toàn bộ con trỏ Ticket
     * @details Sử dụng cấu trúc List tự cài đặt
     ***************************************************************************/
    List<Ticket*> m_tickets;

    /***************************************************************************
     * @brief Thư mục chứa dữ liệu các file vé
     * @attention Mỗi file tương ứng một vé
     ***************************************************************************/
    const string FOLDER_PATH = "../data/tickets";

public:

    /*********************************************************
     * @brief Constructor
     * @details Khởi tạo repository, chuẩn bị cho việc load dữ liệu vé
     *********************************************************/
    TicketRepository();

    /***********************************************************************************************************
     * @brief Destructor
     * @details Giải phóng bộ nhớ toàn bộ các Ticket* đang được quản lý
     ***********************************************************************************************************/
    ~TicketRepository();

    /************************************************************************
     * @brief Thêm một vé vào repository
     * @param ticket - tham chiếu đến Ticket cần thêm
     * @return void
     * @attention Sao chép dữ liệu ticket và lưu vào danh sách m_tickets
     ************************************************************************/
    void add(const Ticket& ticket);

    /************************************************************************
     * @brief Xoá vé bằng TicketID
     * @param ticketID - mã vé cần xoá
     * @attention Nếu không tìm thấy TicketID → không xoá gì
     ************************************************************************/
    void remove(const string& ticketID);

    /************************************************************************
     * @brief Kiểm tra xem repository có chứa vé này không
     * @param ticket - con trỏ Ticket cần kiểm tra
     * @return boolean value, true/false
     * @attention true nếu đã tồn tại trong danh sách
     * @attention false nếu chưa tồn tại
     ************************************************************************/
    [[nodiscard]] bool contains(Ticket* ticket) const;

    /************************************************************************
     * @brief Tìm vé theo TicketID
     * @param id - mã vé cần tìm
     * @return Ticket** - con trỏ đến phần tử Ticket* trong List
     * @attention trả về nullptr nếu không tìm thấy
     ************************************************************************/
    Ticket** findByID(const string& id);

    /************************************************************************
     * @brief Tìm tất cả vé theo FlightID
     * @param flightID - mã chuyến bay
     * @return List<Ticket*> - danh sách các vé thuộc chuyến bay này
     ************************************************************************/
    [[nodiscard]] List<Ticket*> findByFlightID(const string& flightID) const;

    /************************************************************************
     * @brief Lấy toàn bộ danh sách vé
     * @return List<Ticket*>& - tham chiếu đến danh sách m_tickets
     ************************************************************************/
    List<Ticket*>& getAll();

    /************************************************************************
     * @brief Tạo ra một vé “không xác định”
     * @return Ticket** - con trỏ đến Ticket* mới được khởi tạo
     * @attention sử dụng khi xảy ra lỗi load dữ liệu
     ************************************************************************/
    Ticket** undefineTicket();

    /************************************************************************
     * @brief Load toàn bộ dữ liệu vé từ thư mục FOLDER_PATH
     * @details Mỗi file được đọc và convert thành một Ticket
     ************************************************************************/
    void loadAllTickets();

    /************************************************************************
     * @brief Lưu toàn bộ vé từ m_tickets ra thư mục FOLDER_PATH
     * @details Mỗi vé được ghi ra 1 file riêng
     ************************************************************************/
    void saveAllTickets() const;
};

#endif //FLIGHTMANAGER_TICKETREPOSITORY_H
