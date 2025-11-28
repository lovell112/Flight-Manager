/**
 * ************************************************************
 * @file CustomerRepository.h
 * @class CustomerRepository
 * @description Lớp repository quản lý dữ liệu khách hàng
 *              Cung cấp các phương thức để thêm, xóa, tìm kiếm
 *              và lưu/tải dữ liệu khách hàng từ file
 *
 * @attention Đường dẫn file: ../data/customer.txt
 * @attention Phải gọi loadAllCustomers() sau khởi tạo để tải dữ liệu
 * @attention Gọi saveAllCustomers() để lưu thay đổi vào file
 * ************************************************************
 */
#ifndef FLIGHTMANAGER_CUSTOMERREPOSITORY_H
#define FLIGHTMANAGER_CUSTOMERREPOSITORY_H

#include "../core/Customer.h"
#include <string>
#include <fstream>
#include <sstream>
#include "../datastructures/List.hpp"
using namespace std;

/**
 * @class CustomerRepository
 * @brief Hứng data được lưu trữ trong file customer.txt
 * @details Lưu trữ data vào List<Customer*>
 * @details Cung cấp các method để thao tác với dữ liệu
 * @attention Phải gọi loadAllCustomers() sau khởi tạo để tải dữ liệu
 * @attention Gọi saveAllCustomers() để lưu thay đổi vào file
 */
class CustomerRepository {
private:
    List<Customer*> m_customers;
    const string PATH = "../data/customer.txt";

public:
     /**
     * @description Khởi tạo CustomerRepository Cấp phát bộ nhớ cho danh sách khách hàng
     */
    CustomerRepository();
     /**
     * @description Giải phóng bộ nhớ của tất cả đối tượng Customer Xóa sạch danh sách khách hàng
     */
    ~CustomerRepository();
    /**
     * @description Thêm một khách hàng mới vào danh sách
     * @param const Customer& Tham chiếu tới đối tượng khách hàng cần thêm
     * @attention Sao chép dữ liệu khách hàng vào danh sách
     * @attention Cần gọi saveAllCustomers() để lưu vào file
     */

    void add(const Customer&);
    /**
     * @description Xóa khách hàng khỏi danh sách theo ID
     * @param const string& ID của khách hàng cần xóa
     * @attention Giải phóng bộ nhớ của khách hàng bị xóa
     * @attention Không có gì xảy ra nếu ID không tồn tại
     * @attention Cần gọi saveAllCustomers() để lưu thay đổi vào file
     */
    void remove(const string&);
    /**
     * @description Tìm kiếm khách hàng theo ID
     * @param const string& ID của khách hàng cần tìm
     * @return Con trỏ đến con trỏ Customer (Customer**)
     *         Trả về NULL nếu không tìm thấy
     * @attention Sử dụng con trỏ kép để có thể cập nhật tham chiếu
     */
    Customer **findByID(const string &);
    /**
     * @description Lấy tham chiếu tới danh sách tất cả khách hàng
     * @return Tham chiếu tới List chứa con trỏ Customer
     * @attention Trả về tham chiếu, không phải bản sao
     * @attention Có thể dùng để duyệt qua tất cả khách hàng
     */
    List<Customer *> &getAll();
    /**
     * @description Khôi phục khách hàng (tính năng dự bị)
     * @return Con trỏ đến mảng khách hàng chưa xác định
     * @attention Chỉ dùng trong trường hợp khôi phục dữ liệu đặc biệt
     */

    Customer **undefineCustomer();
    /**
     * @description Tải tất cả dữ liệu khách hàng từ file
     *              Đọc từ file ../data/customer.txt
     *              Khởi tạo các đối tượng Customer từ dữ liệu trong file
     * @attention Phải gọi sau khi khởi tạo để nạp dữ liệu ban đầu
     * @attention Xóa dữ liệu cũ trước khi tải dữ liệu mới
     * @attention Trả về lỗi nếu file không tồn tại hoặc không đọc được
     */
    
    void loadAllCustomers();
/**
     * @description Lưu tất cả dữ liệu khách hàng vào file
     *              Ghi toàn bộ danh sách khách hàng vào file
     *              ../data/customer.txt dưới định dạng văn bản
     * @attention Ghi đè nội dung file cũ
     * @attention Thực hiện sau mỗi lần thêm/xóa khách hàng
     * @attention Trả về lỗi nếu file không thể ghi được
     */
    void saveAllCustomers() const;
};

#endif //FLIGHTMANAGER_CUSTOMERREPOSITORY_H
