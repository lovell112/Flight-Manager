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

class AirplaneRepository {
    List<Airplane*> m_airplanes;
    const string PATH = "../data/airplane.txt";
public:
    AirplaneRepository();
    ~AirplaneRepository();

    //CRUD
    void add(const Airplane&);
    void remove(const string&);

    // Tìm máy bay theo ID, trả Iterator
    Airplane** findByID(const string&);

    // Lấy danh sách trạng thái ghế (0 = trống, 1 = đặt)
    List<int> getSeatList(const string&);

    // // Truy cập toàn bộ danh sách
    List<Airplane*>& getAll();

    // undefine object
    [[nodiscard]] Airplane** undefineAirplane();

    // Load / Save dữ liệu
    void loadAllAirplanes();
    void saveAllAirplanes() const;
};


#endif //FLIGHTMANAGER_AIRPLANEREPOSITORY_H
