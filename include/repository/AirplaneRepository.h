#ifndef FLIGHTMANAGER_AIRPLANEREPOSITORY_H
#define FLIGHTMANAGER_AIRPLANEREPOSITORY_H

#include "../core/Airplane.h"
#include <string>
#include <fstream>
#include <filesystem>
#include "../datastructures/List.hpp"
#include <sstream>
#include <iostream>
using namespace std;

/**********************************************************
 * @Class       AirplaneRepository
 * @Description Quản lý danh sách máy bay: thêm, xóa, tìm,
 *              lưu file và tải dữ liệu từ file airplane.txt.
 **********************************************************/
class AirplaneRepository {
    List<Airplane*> m_airplanes; // Danh sách máy bay quản lý
    const string PATH = "../data/airplane.txt"; // Đường dẫn file dữ liệu
public:
    /**********************************************************
     * @Description Constructor - load dữ liệu máy bay
     **********************************************************/
    AirplaneRepository();

    /**********************************************************
     * @Description Destructor - giải phóng toàn bộ object
     **********************************************************/
    ~AirplaneRepository();

    // ================== CRUD ==================

    /**********************************************************
     * @Description Thêm máy bay mới
     **********************************************************/
    void add(const Airplane&);

    /**********************************************************
     * @Description Xóa máy bay theo ID
     **********************************************************/
    void remove(const string&);

    /**********************************************************
     * @Description Tìm máy bay theo ID
     * @return      Pointer đến pointer Airplane (Iterator kiểu thô)
     **********************************************************/
    Airplane** findByID(const string&);

    /**********************************************************
     * @Description Lấy danh sách trạng thái ghế của máy bay
     * @return      List<int> (0 = trống, 1 = đặt)
     **********************************************************/
    List<int> getSeatList(const string&);

    /**********************************************************
     * @return Danh sách toàn bộ máy bay (tham chiếu)
     **********************************************************/
    List<Airplane*>& getAll();

    /**********************************************************
     * @Description Trả về Airplane** không xác định (rỗng)
     * @attention   Dùng khi không tìm thấy máy bay
     **********************************************************/
    [[nodiscard]] Airplane** undefineAirplane();

    // ================== File I/O ==================

    /**********************************************************
     * @Description Load toàn bộ máy bay từ file
     **********************************************************/
    void loadAllAirplanes();

   /**********************************************************
    * @Description Lưu toàn bộ máy bay ra file
    **********************************************************/
    void saveAllAirplanes() const;
};


#endif //FLIGHTMANAGER_AIRPLANEREPOSITORY_H
