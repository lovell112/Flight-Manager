/**
* @file AuthService.h
 * @brief Khai báo lớp AuthService
 * @details Quản lí các chứ năng đăng nhập, đăng xuất, dổi mật khẩu và truy xuất thông tin admin
 */

#ifndef AIRPLANEMANAGER_AUTHSERVICE_H
#define AIRPLANEMANAGER_AUTHSERVICE_H
#include "../repository/AdminRepository.h"

/******************************************************************************
 * @class AuthService
 * @brief Cung cấp chức năng quản lý dịch vụ xác thực.
 * @details
 * Quản lý các chức năng xác thực như đăng nhập, đăng xuất,
 * đổi mật khẩu và truy xuất thông tin admin hiện tại.
 ******************************************************************************/
class AuthService {
    AdminRepository* m_adminRepository;
    Admin** m_currentAdmin;
public:
    
    /******************************************************************************
     * @brief Constructor
     * @details
     * @attention Khởi tạo admin repository
     * @attention account mặc định khi chưa đăng nhập sẽ là AdminRepository::undefineAdmin()
     ******************************************************************************/
    AuthService();
    
    /******************************************************************************
     * @brief Destructor
     * @details
     * @attention Delete admin repository tránh leak memory
     ******************************************************************************/
    ~AuthService();
    
    /******************************************************************************
     * @brief Lấy ra account hiện tại
     * @details
     * @return 2 pointer trỏ của account hiện tại nằm trong repository
     ******************************************************************************/
    Admin **getCurrentAdmin() const;
    
    /******************************************************************************
     * @brief Thử đăng nhập với username và password
     * @details
     * @return boolean value, true/false
     * @attention lấy ra từ repository tài khoản với username và password được truyền vào
     * @attention nếu tồn tại account trong repository thì return true
     * @attention nếu không tồn tại account trong repository thì return false
     ******************************************************************************/
    bool tryLogin(const string&, const string&);
    
    /******************************************************************************
     * @brief Thử đổi password
     * @details
     * @return boolean value, true/false
     * @attention Nếu chưa đăng nhập thì return false (không thể đổi)
     * @attention return hàm AdminRepository::tryChangePassword(string, string)
     ******************************************************************************/
    bool tryChangePassword(const string&, const string&) const;
    
    /******************************************************************************
     * @brief Đăng xuất tài khoản
     * @details
     * @attention Đưa account hiện tại về AdminRepository::undefineAdmin()
     ******************************************************************************/
    void logout();
};


#endif //AIRPLANEMANAGER_AUTHSERVICE_H