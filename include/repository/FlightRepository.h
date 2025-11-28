/**
 * @file FlightRepository.h
 * @brief Hứng data được load từ flight.txt và thao tác với dữ liệu chuyến bay
 */

#ifndef FLIGHTMANAGER_FLIGHTREPOSITORY_H
#define FLIGHTMANAGER_FLIGHTREPOSITORY_H

#include "../../include/core/Flight.h"
#include <string>
#include <fstream>
#include <sstream>
#include "../datastructures/List.hpp"
#include <iostream>
using namespace std;

/**
 * @class FlightRepository
 * @brief Hứng dữ liệu được lưu trữ trong file flight.txt
 * @details Lưu trữ Flight* vào List<Flight*>
 * @details Cung cấp các method để thao tác dữ liệu chuyến bay
 */
class FlightRepository {

    /**
     * @variable m_flights
     * @brief Danh sách các object Flight được lưu trữ trong repository.
     * @details Sử dụng cấu trúc List<Flight*> để quản lý dữ liệu các chuyến bay.
     * @details Toàn bộ dữ liệu được load từ file flight.txt sẽ được gán vào danh sách này.
     */
    List<Flight*> m_flights;

    /**
     * @variable PATH
     * @brief Đường dẫn đến file lưu trữ dữ liệu của Flight.
     * @details Dùng để xác định vị trí flight.txt – nơi chứa danh sách các chuyến bay.
     * @details Quan trọng trong quá trình load và save dữ liệu từ/đến file.
     */
    const string PATH = "../data/flight.txt";

public:

    /**
     * @brief Constructor, load toàn bộ dữ liệu từ flight.txt
     * @details Khởi tạo repository và tự động gọi loadAllFlights()
     */
    FlightRepository();

    /**
     * @brief Destructor, save lại tất cả dữ liệu và dọn bộ nhớ
     * @attention saveAllFlights() trước khi hủy
     * @attention delete toàn bộ Flight* trong danh sách
     * @attention clear List<Flight*>
     */
    ~FlightRepository();

    /**
     * @brief Thêm một chuyến bay vào repository
     * @details Copy dữ liệu từ Flight truyền vào, sau đó push vào List
     * @attention Không thêm nếu chuyến bay đã tồn tại (trùng ID)
     */
    void add(const Flight&);

    /**
     * @brief Xóa một chuyến bay theo mã ID
     * @details Tìm Flight theo ID, xóa object khỏi memory và danh sách
     * @attention Không làm gì nếu không tìm thấy chuyến bay
     */
    void remove(const string&);

    /**
     * @brief Cập nhật trạng thái chuyến bay
     * @details Tìm Flight theo ID và thay đổi trạng thái
     * @attention Không thay đổi gì nếu ID không tồn tại
     */
    void setFlightStatus(const string&, const FlightStatus&);

    /**
     * @brief Tìm chuyến bay theo ID
     * @return 2-level pointer trỏ vào phần tử chứa Flight* trong List
     * @attention return FlightRepository::undefineFlight() nếu không tìm thấy
     */
    Flight **findByID(const string &);

    /**
     * @brief Tìm danh sách chuyến bay theo ngày
     * @return List<Flight*> danh sách kết quả
     * @attention Chỉ trả về những chuyến bay có cùng ngày (string so sánh)
     */
    List<Flight*> findByDate(const string&);

    /**
     * @brief Tìm danh sách chuyến bay theo điểm đến
     * @return List<Flight*> danh sách các chuyến bay hợp lệ
     */
    List<Flight*> findByDestination(const string&);

    /**
     * @brief Tìm danh sách chuyến bay theo mã máy bay
     * @return List<Flight*> danh sách các chuyến bay của máy bay đó
     */
    List<Flight*> findByAirplane(const string&);

    /**
     * @brief Object không tồn tại trong repository
     * @details Dùng làm kết quả trả về khi không tìm thấy Flight
     * @attention Chỉ trả về con trỏ null pointer dạng Flight**
     */
    [[nodiscard]] Flight **undefineFlight();

    /**
     * @brief Lấy toàn bộ danh sách chuyến bay
     * @return List<Flight*>& danh sách hiện có trong repository
     */
    List<Flight*>& getAll();

    /**
     * @brief Load toàn bộ dữ liệu từ file flight.txt
     * @attention Xóa dữ liệu cũ trước khi load mới
     * @attention return nếu file không tồn tại hoặc đường dẫn sai
     * @details Định dạng dữ liệu phụ thuộc Flight::toString()
     */
    void loadAllFlights();

    /**
     * @brief Lưu toàn bộ danh sách chuyến bay vào flight.txt
     * @attention return nếu file không tồn tại/sai đường dẫn
     * @details Ghi từng Flight theo format của Flight::toString()
     */
    void saveAllFlights();
};

#endif //FLIGHTMANAGER_FLIGHTREPOSITORY_H
