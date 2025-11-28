/**
 * @file AdminRepository.h
 * @brief Hứng data được load từ Admin.txt và thao tác
 */

#ifndef FLIGHTMANAGER_ADMINREPOSITORY_H
#define FLIGHTMANAGER_ADMINREPOSITORY_H
#include "../core/Admin.h"
#include <string>
#include <fstream>
#include <sstream>
#include "../datastructures/List.hpp"
using namespace std;

/**
 * @class AdminRepository
 * @brief Hứng data được lưu trữ trong file admin.txt
 * @details Lưu trữ data vào List<Admin*>
 * @details Cung cấp các method để thao tác với dữ liệu
 */
class AdminRepository {
    /**
     * @variable m_admins
     * @brief Danh sách các object Admin được lưu trữ trong repository.
     * @details Sử dụng cấu trúc List<Admin*> để quản lý các object Admin trong bộ nhớ.
     * @details Được sử dụng để lưu trữ dữ liệu tải lên từ file admin.txt và dùng trong các thao tác quản lý dữ liệu.
     */
    List<Admin*> m_admins;

    /**
     * @variable PATH
     * @brief Đường dẫn đến file lưu trữ dữ liệu của Admin.
     * @details Được sử dụng để xác định vị trí file admin.txt, nơi chứa danh sách các object Admin.
     * @details Đóng vai trò quan trọng trong việc đọc và ghi dữ liệu từ/đến file khi tải hoặc lưu trữ thông tin Admin.
     */
    const string PATH = "../data/admin.txt";
public:
    /**
     * @brief Constructor, load data từ file admin.txt lên
     */
    AdminRepository();

    /**
     * @brief Destructor, save data vào file admin.txt, sau đó xóa các object
     * @attention load data mới nhất
     * @attention save data vào file
     * @attention delete các object
     * @attention clear List<Admin*>
     */
    ~AdminRepository();

    /**
     * @brief Đọc dữ liệu từ file admin.txt lưu vào List<Admin*>
     * @attention Nếu file admin.txt không tồn tại/sai đường dẫn thì return
     * @attention Dọn dẹp dữ liệu cũ trước khi cập nhật dữ liệu mới
     * @attention Tách dữ liệu từ file admin.txt theo định dạng của Admin::toString(): <username>|<password>
     */
    void loadAllAdmins();

    /**
     * @brief Lưu dữ liệu từ List<Admin*> vào file admin.txt
     * @attention Nếu file admin.txt không tồn tại/sai đường dẫn thì return
     * @attention Ghi dữ liệu từ List<Admin*> vào file admin.txt theo định dạng của Admin::toString(): <username>|<password>
     */
    void saveAllAdmins() const;

    /**
     * @brief Kiểm tra tài khoản, xem có tồn tại
     * @return 2 pointer trỏ vào pointer quản lí object hợp lệ trong repository
     * @attention return AdminRepositoru::undefineAdmin() nếu không tồn tại admin
     * @attention Tách dữ liệu từ file admin.txt theo định dạng của Admin::toString(): <username>|<password>
     */
    Admin** getValidateAdmin(const string&, const string&);

    /**
     * @brief object không tồn tại trong repository
     * @attention load data mới nhất
     * @return List<Admin*>::end()
     */
    Admin** undefineAdmin();
};


#endif //FLIGHTMANAGER_ADMINREPOSITORY_H