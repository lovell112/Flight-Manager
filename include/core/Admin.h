/******************************************************************************
 * @file Admin.h
 * @brief Xây dựng các mô hình dữ liệu cho admin account
 ******************************************************************************/

#ifndef AIRPLANEMANAGER_ADMIN_H
#define AIRPLANEMANAGER_ADMIN_H
#include <string>
#include <iostream>
using namespace std;

/**
 * @class Admin
 * @brief Xây dựng mô hình dữ liệu cho admin account
 */
class Admin {
    string m_strUsername;
    string m_strPassword;
public:
    /*********************************************************
     * @brief Constructor
     * @details Khởi tạo các giá trị cho admin
     *********************************************************/
    Admin(const string&, const string&);

    /***********************************************************************************************************
     * @brief Destructor = default
     * @details Mặc định
     ***********************************************************************************************************/
    ~Admin();

    /************************************************************************
     * @brief Thử đăng nhập
     * @return boolean value, true/false
     * @details Nhận argument và kiểm tra tính hợp lệ
     * @attention trả về true nếu tài khoản admin tồn tại
     * @attention trả về false nếu không tồn tại tài khoản admin
     ************************************************************************/
    [[nodiscard]] bool tryLogin(const string&, const string&) const;

    /***********************************************************************************************************
     * @brief Thử đổi password
     * @details Nhận argument và kiểm tra tính hợp lệ
     * @return boolean value, true/false
     * @attention true nếu oldpassword khớp với password hiện tại, và newpassword không trùng với oldpassword
     * @attention false nếu oldpassword không khớp với password hiện tại, hoặc newpassword trùng với oldpassword
     ***********************************************************************************************************/
    bool tryChangePassword(const string&, const string&);

    /***********************************************************************************************************
     * @brief: chuyển data của 1 object thành chuỗi
     * @details
     * @attention định dạng <ten_dang_nhap>|<mat_khau>
     ***********************************************************************************************************/
    [[nodiscard]] string toString() const;

    /***********************************************************************************************************
     * @brief: xuất ra data của object, chủ yếu sử dụng cho quá trình debug
     * @details
     ***********************************************************************************************************/
    void printAdminInfo() const;
};


#endif //AIRPLANEMANAGER_ADMIN_H