/**
 * @file MenuController.h
 * @brief Khai báo lớp MenuController
 * @details Móc nối UI với Data thông các Manager và Service
 */

#ifndef AIRPLANEMANAGER_MENUCONTROLLER_H
#define AIRPLANEMANAGER_MENUCONTROLLER_H
#include "../service/AuthService.h"
#include "../service/CustomerService.h"
#include "../service/TicketManager.h"
#include "../service/FlightManager.h"

/**
 * @class MenuController
 * @brief Móc nối UI với Data thông các Manager và Service
 */
class MenuController {
    /**
     * @brief Đọc dữ liệu từ file admin.txt lưu vào List<Admin*>
     * @note Chuỗi cho phím tắt ESC trên bàn phím
     */
    static string ESCAPE;

    /**
     * @brief Cung cấp dịch vụ cho khách hàng
     */
    CustomerService* m_customerService;

    /**
     * @brief Cung cấp dịch vụ cho admin
     */
    AuthService* m_authService;

    /**
     * @brief Cung cấp các thao tác chuyến bay
     */
    FlightManager* m_flightManager;

    /**
     * @brief Cung cấp các thao tác quản lí vé
     */
    TicketManager* m_ticketManager;

    /******************************************************************************
     * @brief Menu Tại màn hình chính Application
     * @attention Clear màn hình trước khi render UI
     * @details Hiển thị Menu
     ******************************************************************************/
    static void mainMenu();

    /******************************************************************************
     * @brief hiển thị tất cả các chuyến bay
     * @attention Clear màn hình trước khi render UI
     * @details Cố định kích thước cho các cột
     * @details Hiển thị các chuyến bay từ FlightManager::FlightRepository theo dạng bảng
     ******************************************************************************/
    void flightListMenu() const;

    /******************************************************************************
     * @brief Giao diện đặt vé cho khách hàng
     * @attention Clear màn hình trước khi render UI
     * @attention Hiển thị tất cả các chuyến bay cho khách hàng dễ chọn
     * @attention Thoát giao diện nếu nhấn ESC từ bàn phím bắt kì lúc nào
     * @details Nhập vào thông tin cần thiết cho việc đặt vé
     * @details Kiểm tra nghiêm ngặt cho dữ liệu đầu vào
     * @attention Hiển thị lỗi nếu sai thông tin
     ******************************************************************************/
    void bookTicketMenu() const;

    /******************************************************************************
     * @brief Giao diện quản lí dành cho admin
     * @attention Clear màn hình trước khi render UI
     * @attention Hiển thị Menu quản lí
     * @attention Thoát giao diện nếu nhấn ESC từ bàn phím bắt kì lúc nào
     * @details Nhập vào option
     * @details Kiểm tra nghiêm ngặt cho dữ liệu đầu vào
     * @attention Hiển thị lỗi nếu thông tin không phải số
     * @attention Hiển thị ra giao diện quản lí ứng với option đã nhập
     ******************************************************************************/
    void manageMenu() const;

    /******************************************************************************
     * @brief hiển thị tất cả các vé bay đang đợi để duyệt
     * @attention Clear màn hình trước khi render UI
     * @details Cố định kích thước cho các cột
     * @details Hiển thị các vé từ TicketManager::TicketQueueRepository theo dạng bảng
     ******************************************************************************/
    void showAllTicketQueue() const;

    /******************************************************************************
     * @brief hiển thị tất cả các vé chính thức của chuyến bay
     * @attention Clear màn hình trước khi render UI
     * @details Cố định kích thước cho các cột
     * @details Hiển thị các chuyến bay từ TicketManager::TicketRepository theo dạng bảng
     ******************************************************************************/
    void showAllTicket() const;

    /******************************************************************************
     * @brief hiển thị tất cả các chuyến bay
     * @attention Clear màn hình trước khi render UI
     * @details Cố định kích thước cho các cột
     * @details Hiển thị các chuyến bay từ FlightManager::FlightRepository theo dạng bảng
     ******************************************************************************/
    void showTicketByFlightID(const string&) const;

    /******************************************************************************
     * @brief hiển thị tất cả các ghế hợp lệ của mã chuyến bay được truyền vào
     * @attention Clear màn hình trước khi render UI
     * @details Hiển thị các ghế từ FlightManager::FlightRepository theo thành từng dòng
     ******************************************************************************/
    void showAvailableSeatOfFlight(const string&) const;

    /******************************************************************************
     * @brief hiển thị tất cả các chuyến bay mà máy bay có id được truyền vào đã thực hiện
     * @attention Clear màn hình trước khi render UI
     * @details Cố định kích thước cho các cột
     * @details Hiển thị các chuyến bay từ FlightManager::FlightRepository theo dạng bảng
     ******************************************************************************/
    void showFlightQuantityOfAirplane(const string&) const;

    /******************************************************************************
     * @brief thực hiện thao tác xử lí những vé được khách đặt
     * @attention Clear màn hình trước khi render UI
     * @details Lấy Data từ TicketManager::TicketQueueRepository để xử lí
     * @details Hiển thị tất cả vé đang trong hàng chờ xử lí
     * @details chọn option
     * @attention Kiểm tra tính hợp lệ của option đã nhập
     * @attention Nhấn ESC sẽ thoát Giao diện
     * @attention Nếu option hợp lệ thì thực hiện thêm hoặc xóa trong queue
     ******************************************************************************/
    void handleTicketBooking() const;

    /******************************************************************************
     * @brief thực hiện thao tác xử lí huy những vé đã đặt thành công
     * @attention Clear màn hình trước khi render UI
     * @details Lấy Data từ TicketManager::TicketRepository để xử lí
     * @details Hiển thị tất cả vé đang trong kho
     * @details chọn option
     * @attention Kiểm tra tính hợp lệ của option đã nhập
     * @attention Nhấn ESC sẽ thoát Giao diện
     * @attention Nếu option hợp lệ thì thực hiện nhập mã vé cần hủy
     * @attention Kiểm tra tính hợp lệ của mã vé
     * @attention Nếu mã vé hợp lệ thì xóa ra khỏi danh sách vé trong kho vé
     ******************************************************************************/
    void handleTicketCancelation() const;

    /******************************************************************************
     * @brief Hiện thị Menu thao tác thống kê
     * @attention Clear màn hình trước khi render UI
     * @details Hiển thị Menu
     * @details chọn option
     * @attention Kiểm tra tính hợp lệ của option đã nhập
     * @attention Nhấn ESC sẽ thoát Giao diện
     * @attention Nếu option hợp lệ thì thực hiện chức năng thống kê tường ứng
     ******************************************************************************/
    void showStatistics() const;

    /******************************************************************************
     * @brief Hiển thị logo của giao diện login
     ******************************************************************************/
    static void displayLoginLogo();

    /******************************************************************************
     * @brief thực hiện thao tác nhập password từ bàn phím của user
     * @return chuỗi input được nhập từ bàn phím
     * @details Bắt từng phím được nhấn, push back vào string
     * @details Hiển thị kí tự '*' thay vì phím mà user nhập
     * @attention Nếu phát hiện phím được nhấn là ESC thì return ESCAPE
     ******************************************************************************/
    static string inputHiddenPassword();

    /******************************************************************************
     * @brief thực hiện thao tác nhập input từ bàn phím của user
     * @return chuỗi input được nhập từ bàn phím
     * @details Bắt từng phím được nhấn, push back vào string
     * @details Hiển thị phím mà user nhập
     * @attention Nếu phát hiện phím được nhấn là ESC thì return ESCAPE
     ******************************************************************************/
    static string input();

    /******************************************************************************
     * @brief Hiển thị giao diện Login
     * @details Nhập username, password
     * @attention Nếu phát hiện phím được nhấn là ESC thì return ESCAPE
     * @attention Thực hiện login bằng AuthService::tryLogin(string, string)
     * @attention Nếu tài khoản không hợp lệ, cảnh báo
     * @attention Nếu cảnh báo 3 lần thoát giao diện đăng nhập
     * @attention Nếu đăng nhập thành công thì hiển thị giao diện quản lí
     ******************************************************************************/
    void showLogin() const;
public:

    /******************************************************************************
     * @brief Constructor
     * @details Khởi tạo CustomerService
     * @details Khởi tạo AuthService
     * @details Khởi tạo FlightManager
     * @details Khởi tạo TicketManager
     ******************************************************************************/
    MenuController();

    /******************************************************************************
     * @brief Destructor
     * @details Giải phóng CustomerService
     * @details Giải phóng AuthService
     * @details Giải phóng FlightManager
     * @details Giải phóng TicketManager
     ******************************************************************************/
    ~MenuController();

    /******************************************************************************
     * @brief Thực hiện chạy chương trình
     * @details Hiển thị logo, option
     * @details Nhập vào option
     * @attention Nếu phát hiện phím được nhấn là ESC thì return ESCAPE
     * @attention Kiểm tra độ hợp lệ của option
     * @attention Option hợp lệ, thực hiện các chức năng tương ứng
     * @attention Option không hợp lệ, hiện thị thông báo lỗi
     ******************************************************************************/
    void run() const;
};
#endif //AIRPLANEMANAGER_MENUCONTROLLER_H