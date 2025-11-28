/**
 * @file ConsoleUI.h
 * @brief Tương tác với người dùng bằng cửa sổ console
 */
#ifndef AIRPLANEMANAGER_CONSOLEUI_H
#define AIRPLANEMANAGER_CONSOLEUI_H
#include "MenuController.h"


/**
 * @class ConsoleUI
 * @brief Quản lý giao diện người dùng thông qua console.
 *
 * Lớp ConsoleUI tương tác với người dùng bằng cửa sổ console, xử lý các thao tác
 * và chuyển tiếp việc xử lý nhập/xuất cho MenuController được chỉ định.
 */
class ConsoleUI {
    MenuController* m_controller;
public:

    /**
     * @brief Constructor
     *
     * @attention Khởi tạo 1 MenuController
     */
    ConsoleUI();

    /**
     * @brief Destructor
     *
     * @attention Giải phóng vùng nhớ Controller được cấp phát
     */
    ~ConsoleUI();

    /**
     * @brief Chạy ứng dụng Console
     *
     * @attention Chạy MenuController::run()
     */
    void exec() const;
};


#endif //AIRPLANEMANAGER_CONSOLEUI_H