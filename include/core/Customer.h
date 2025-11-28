/**
 * ************************************************************
 * @file Customer.h
 * @class Customer
 * @description Lớp đại diện cho một khách hàng trong hệ thống
 *              Lưu trữ thông tin cơ bản: số thứ tự, họ tên, ID
 *              Cung cấp các phương thức getter/setter và in thông tin
 *
 * @attention Sử dụng [[nodiscard]] để cảnh báo nếu bỏ qua giá trị trả về
 * @attention Destructor mặc định vì không cấp phát bộ nhớ động
 * ************************************************************
 */
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;
/**
 * @class Customer
 * @brief Xây dựng mô hình dữ liệu cho khách hàng
 */
class Customer {
private:
    int m_iNumber;
    string m_strFullName;
    string m_strID;

public:
    /**
     * @description Constructor mặc định
     *              Khởi tạo khách hàng với giá trị mặc định
     *              m_iNumber = 0, m_strFullName = "", m_strID = ""
     */
    Customer();
/**
     * @description Constructor có tham số
     *              Khởi tạo khách hàng với dữ liệu cụ thể
     * @param number Số thứ tự của khách hàng
     * @param fullName Họ tên đầy đủ của khách hàng
     * @param id ID (CMND) của khách hàng
     */
    Customer(int, const string&, const string&);
    /**
     * @description Destructor mặc định
     *              Không cần giải phóng bộ nhớ vì không cấp phát động
     */
    ~Customer() = default;
/**
     * @description Lấy ID của khách hàng
     * @return Tham chiếu const tới chuỗi chứa ID
     * @attention [[nodiscard]]: Cảnh báo nếu bỏ qua kết quả trả về
     */

    [[nodiscard]] const string& getCustomerID() const;
 /**
     * @description Lấy họ tên đầy đủ của khách hàng
     * @return Tham chiếu const tới chuỗi chứa họ tên
     * @attention [[nodiscard]]: Cảnh báo nếu bỏ qua kết quả trả về
     */
    [[nodiscard]] const string& getFullName() const;
    /**
     * @description Lấy số thứ tự của khách hàng
     * @return Giá trị int là số thứ tự
     * @attention [[nodiscard]]: Cảnh báo nếu bỏ qua kết quả trả về
     */
    [[nodiscard]] int getNumber() const;
    /**
     * @description Đặt số thứ tự cho khách hàng
     * @param int Số thứ tự cần đặt
     * @attention Không kiểm tra giá trị hợp lệ, gọi hàm validation khác nếu cần
     */
    void setNumber(int);
     /**
     * @description Đặt họ tên cho khách hàng
     * @param const string& Tham chiếu tới chuỗi họ tên cần đặt
     * @attention Không kiểm tra chuỗi rỗng, gọi hàm validation khác nếu cần
     */
    void setFullname(const string&);
    /**
     * @description Đặt ID cho khách hàng
     * @param customerID ID (CMND) cần đặt
     * @attention Không kiểm tra ID hợp lệ, gọi hàm validation khác nếu cần
     * @attention ID nên là duy nhất trong hệ thống
     */
    void setCustomerID(const string&);
    /**
     * @description Chuyển đối tượng Customer thành chuỗi
     *              Định dạng: "ID|Họ tên|Số thứ tự" hoặc tương tự
     * @return Chuỗi đại diện cho thông tin khách hàng
     * @attention [[nodiscard]]: Cảnh báo nếu bỏ qua kết quả trả về
     * @attention Dùng để lưu vào file hoặc debug
     */
    [[nodiscard]] string toString() const;
    /**
     * @description In thông tin chi tiết của khách hàng ra console
     *              Hiển thị: Số thứ tự, Họ tên, ID
     * @attention Sử dụng cout để in ra màn hình
     * @attention Hữu ích cho debug và kiểm tra dữ liệu
     * @attention Gọi toString() để lấy chuỗi rồi in
     */
    void printCustomerInfo() const;
};

#endif
