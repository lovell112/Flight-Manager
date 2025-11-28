/******************************************************************************
 * @file TicketQueueRepository.h
 * @brief Quản lý hàng đợi vé (ticket queue) — lưu trữ và xử lý dữ liệu vé chờ
 ******************************************************************************/

#ifndef FLIGHTMANAGER_TICKETQUEUE_H
#define FLIGHTMANAGER_TICKETQUEUE_H

#include "../core/Ticket.h"
#include "../datastructures/Queue.hpp"
#include <vector>
using namespace std;

/**
 * @class TicketQueueRepository
 * @brief Repository quản lý hàng đợi vé (Ticket Queue)
 * @details Chịu trách nhiệm nạp, lưu, thêm, lấy và xoá vé trong hàng đợi
 */
class TicketQueueRepository {

    /**************************************************************************
     * @variable m_tickets
     * @brief Hàng đợi chứa danh sách vé đang chờ xử lý
     **************************************************************************/
    Queue<Ticket*> m_tickets;

    /**************************************************************************
     * @variable PATH
     * @brief Đường dẫn đến file lưu trữ ticket queue
     **************************************************************************/
    const string PATH = "../data/ticket_queue.txt";

public:

    /*********************************************************
     * @brief Constructor
     * @details Khởi tạo repository và load dữ liệu từ file
     *********************************************************/
    TicketQueueRepository();

    /*********************************************************
     * @brief Destructor
     * @details Giải phóng tài nguyên nếu cần
     *********************************************************/
    ~TicketQueueRepository();

    /*********************************************************
     * @brief Thêm một vé vào hàng đợi
     * @param ticket Vé cần thêm
     * @attention Vé được push vào cuối queue
     *********************************************************/
    void push(const Ticket& ticket);

    /*********************************************************
     * @brief Xoá vé đầu tiên khỏi hàng đợi
     * @attention Nếu queue rỗng → không làm gì
     *********************************************************/
    void pop();

    /*********************************************************
     * @brief Lấy vé ở đầu hàng đợi
     * @return con trỏ Ticket đầu tiên
     * @attention trả về nullptr nếu queue rỗng
     *********************************************************/
    [[nodiscard]] Ticket* front();

    /*********************************************************
     * @brief Lấy toàn bộ queue
     * @return Queue<Ticket*>&
     *********************************************************/
    Queue<Ticket*>& getAll();

    /*********************************************************
     * @brief Lấy danh sách vé dưới dạng vector
     * @return vector<Ticket*>
     * @details hỗ trợ hiển thị hoặc xử lý ngoài queue
     *********************************************************/
    vector<Ticket*> getList();

    /*********************************************************
     * @brief Lấy đối tượng Ticket không xác định
     * @return const Ticket*
     * @attention Dùng làm giá trị NULL object
     *********************************************************/
    const Ticket* undefineTicket();

    /*********************************************************
     * @brief Load toàn bộ ticket queue từ file
     * @details Parse dữ liệu từ file vào Queue<Ticket*>
     *********************************************************/
    void loadAllTickets();

    /*********************************************************
     * @brief Lưu toàn bộ ticket queue xuống file
     * @details Ghi queue ra file theo định dạng toString()
     *********************************************************/
    void saveAllTickets() const;
};

#endif //FLIGHTMANAGER_TICKETQUEUE_H
