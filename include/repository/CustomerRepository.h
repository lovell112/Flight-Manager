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
     * @description Constructor, Khởi tạo CustomerRepository
     *              Gọi loadAllCustomers() để tải dữ liệu từ file  
     */
    CustomerRepository();
     /**
     * @description Destructor, Cập nhật dữ liệu mới nhất, lưu vào file
     *              Giải phóng bộ nhớ của tất cả đối tượng Customer
     *              Xóa sạch danh sách
     */
    ~CustomerRepository();
    /**
     * @description Thêm một khách hàng mới vào danh sách
     * @param const Customer& Tham chiếu tới đối tượng khách hàng cần thêm
     * @attention Tải dữ liệu từ file trước khi thêm
     * @attention Sao chép dữ liệu khách hàng vào danh sách (cấp phát động)
     * @attention Lưu dữ liệu vào file sau khi thêm
     */

    void add(const Customer&);
    /**
     * @description Xóa khách hàng khỏi danh sách theo ID
     * @param const string& ID của khách hàng cần xóa
     * @attention Tải dữ liệu từ file trước khi xóa
     * @attention Tìm khách hàng theo ID rồi giải phóng bộ nhớ
     * @attention Không có gì xảy ra nếu ID không tồn tại
     * @attention Lưu dữ liệu vào file sau khi xóa
     */
    void remove(const string&);
    /**
     * @description Tìm kiếm khách hàng theo ID
     * @param const string& ID của khách hàng cần tìm
     * @return Con trỏ đến con trỏ Customer (Customer**)
     *         Trả về iterator end nếu không tìm thấy
     * @attention Tải dữ liệu từ file trước khi tìm
     * @attention Duyệt qua danh sách và so sánh ID
     * @attention Sử dụng con trỏ kép để có thể cập nhật tham chiếu
     */
    Customer **findByID(const string &);
    /**
     * @description Lấy tham chiếu tới danh sách tất cả khách hàng
     * @return Tham chiếu tới List chứa con trỏ Customer
     * @attention Tải dữ liệu từ file trước khi lấy
     * @attention Trả về tham chiếu, không phải bản sao
     * @attention Có thể dùng để duyệt qua tất cả khách hàng
     */
    List<Customer *> &getAll();
    /**
     * @description Lấy iterator cuối (end) của danh sách khách hàng
     * @return Con trỏ đến iterator end (phần tử không hợp lệ)
     * @attention Tải dữ liệu từ file trước
     * @attention Dùng để kiểm tra kết quả tìm kiếm (nếu == end thì không tìm thấy)
     */

    Customer **undefineCustomer();
    /**
     * @description Tải tất cả dữ liệu khách hàng từ file
     *              Đọc từ file ../data/customer.txt (định dạng: số|tên|ID)
     *              Khởi tạo các đối tượng Customer từ dữ liệu trong file
     * @attention Xóa dữ liệu cũ và giải phóng bộ nhớ trước
     * @attention Đọc từng dòng, tách dữ liệu bằng ký tự '|'
     * @attention Bỏ qua dòng trống
     * @attention In lỗi nếu file không tồn tại hoặc không đọc được
     */
    
    void loadAllCustomers();
/**
     * @description Lưu tất cả dữ liệu khách hàng vào file
     *              Ghi toàn bộ danh sách khách hàng vào file
     *              ../data/customer.txt dưới định dạng văn bản
     * @attention Ghi đè nội dung file cũ
     * @attention Ghi từng khách hàng trên một dòng (sử dụng toString())
     * @attention In lỗi nếu file không thể ghi được
     */
    void saveAllCustomers() const;
};

#endif //FLIGHTMANAGER_CUSTOMERREPOSITORY_H
