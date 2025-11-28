/**
 * ************************************************************
 * @file CustomerService.h
 * @class CustomerService
 * @description Lớp quản lý các dịch vụ liên quan đến khách hàng như đặt vé, hủy vé, quản lý thông tin khách hàng
 *
 * @attention Cần khởi tạo tất cả repositories trước khi sử dụng
 * @attention Các method trong class là const, không sửa đổi state
 * @attention Cần giải phóng bộ nhớ trong destructor
 * ************************************************************
 */
#ifndef FLIGHTMANAGER_CUSTOMERSERVICE_H
#define FLIGHTMANAGER_CUSTOMERSERVICE_H

#include "../repository/CustomerRepository.h"
#include <vector>
#include "../repository/AirplaneRepository.h"
#include "../repository/FlightRepository.h"
#include "../repository/TicketQueueRepository.h"
#include "../repository/TicketRepository.h"

/**
 * @class TicketRepository
 * @brief Forward declaration - khai báo trước để tránh circular include
 */
class TicketRepository;
using namespace std;
/**
 * @class CustomerService
 * @brief Xây dựng mô hình service để quản lý dịch vụ khách hàng
 * @details Cung cấp các method để thao tác với khách hàng
 * @details Quản lý đặt vé, hủy vé, thông tin khách hàng
 * @attention Phải khởi tạo tất cả repositories trước khi sử dụng
 * @attention Các method là const, không thay đổi state
 */
class CustomerService {
private:
    TicketRepository* m_ticketRepository;
    CustomerRepository* m_customerRepository;
    FlightRepository* m_flightRepository;
    AirplaneRepository* m_airplaneRepository;
    TicketQueueRepository* m_ticketQueueRepository;

public:
    /**
     * @description Khởi tạo đối tượng CustomerService
     *              Cấp phát bộ nhớ cho các repositories
     * @attention Phải gọi destructor khi không dùng nữa
     */
    CustomerService();
     /**
     * @description Giải phóng bộ nhớ của tất cả repositories
     */
    ~CustomerService();
     /**
     * @description Thêm khách hàng mới vào hệ thống
     * @param const Customer& Tham chiếu đến đối tượng khách hàng cần thêm
     * @attention Kiểm tra trùng lặp trước khi thêm
     * @attention Trả về ERROR_INVALID_PARAM nếu dữ liệu không hợp lệ
     */
    void addCustomer(const Customer&) const;
    /**
     * @description Xóa khách hàng khỏi hệ thống
     * @param const string& ID của khách hàng cần xóa
     * @attention Kiểm tra tồn tại khách hàng trước khi xóa
     * @attention Trả về NULL nếu không tìm thấy khách hàng
     */
    void removeCustomer(const string&) const;
     /**
     * @description Thực hiện đặt vé cho khách hàng
     * @param const string& ID của khách hàng
     * @param const string& ID của chuyến bay
     * @param const string& Điểm đi hoặc điểm đến
     * @param int Số lượng vé cần đặt
     * @return true nếu đặt vé thành công, false nếu thất bại
     * @attention Kiểm tra sức chứa máy bay trước khi đặt
     * @attention Trả về NULL nếu có lỗi ERROR_INVALID_PARAM
     */
    bool tryBookTicket(const string&, const string&, const string&, int) const;
    /**
     * @description Tìm khách hàng theo ID
     * @param const string& ID của khách hàng cần tìm
     * @return Iterator chỉ đến khách hàng trong danh sách
     * @attention Trả về end() nếu không tìm thấy
     */

    vector<Customer*>::iterator findCustomerByID(const string&) const;
    /**
     * @description Lấy danh sách tất cả khách hàng
     * @return List chứa các con trỏ đến tất cả khách hàng
     */
    List<Customer *> getAll() const;
    /**
     * @description Khôi phục khách hàng (tính năng dự bị)
     * @return Con trỏ đến mảng khách hàng chưa xác định
     * @attention Chỉ dùng trong trường hợp đặc biệt
     */
    Customer **undefineCustomer() const;
};

#endif //FLIGHTMANAGER_CUSTOMERSERVICE_H
