//
// Created by HP on 09/11/2025.
//

#ifndef FLIGHTMANAGER_DATETIME_H
#define FLIGHTMANAGER_DATETIME_H
#include <ranges>
#include "../datastructures/List.hpp"
using namespace std;


class DateTime {
    int m_iDay;
    int m_iMonth;
    int m_iYear;
public:
    /**********************************************************
    * @Description Constructor mặc định
    * @return  Pointer trỏ đến DateTime vừa tạo
    **********************************************************/
    DateTime() = default;

    /**********************************************************
    * @Description Constructor từ chuỗi "dd/mm/yyyy"
    * @param const string& date
    * @return  Pointer trỏ đến DateTime vừa tạo
    **********************************************************/
    DateTime(const string&);

    /**********************************************************
    * @Description Destructor
    * @return  Không
    **********************************************************/
    ~DateTime() = default;

    /**********************************************************
    * @Description Lấy ngày
    * @return  int ngày
    **********************************************************/
    [[nodiscard]] int getDay() const;

    /**********************************************************
    * @Description Lấy tháng
    * @return  int tháng
    **********************************************************/
    [[nodiscard]] int getMonth() const;

    /**********************************************************
    * @Description Lấy năm
    * @return  int năm
    **********************************************************/
    [[nodiscard]] int getYear() const;

    /**********************************************************
    * @Description Cập nhật ngày
    * @param int day
    * @return  Không
    **********************************************************/
    void setDay(int);

    /**********************************************************
    * @Description Cập nhật tháng
    * @param int month
    * @return  Không
    **********************************************************/
    void setMonth(int);

    /**********************************************************
    * @Description Cập nhật năm
    * @param int year
    * @return  Không
    **********************************************************/
    void setYear(int);

    /**********************************************************
    * @Description Cập nhật toàn bộ ngày/tháng/năm từ chuỗi
    * @param const string& date
    * @return  Không
    **********************************************************/
    void set(const string&);

    /**********************************************************
    * @Description Tách chuỗi "dd/mm/yyyy" thành List<int> {day, month, year}
    * @param const string& date
    * @return  List<int> {day, month, year}
    **********************************************************/
    static List<int> split(const string&);

    /**********************************************************
    * @Description Chuyển DateTime thành chuỗi "dd/mm/yyyy"
    * @return  string
    **********************************************************/
    string toString() const; // dd/mm/yyyy

    /**********************************************************
    * @Description So sánh hai DateTime
    * @param const DateTime& firstArg, const DateTime& secondArg
    * @return  true nếu bằng nhau, false nếu khác
    **********************************************************/
    friend bool operator==(const DateTime &, const DateTime &);
};


#endif //FLIGHTMANAGER_DATETIME_H