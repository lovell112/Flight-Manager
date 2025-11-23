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
    DateTime() = default;
    DateTime(const string&);
    ~DateTime() = default;

    [[nodiscard]] int getDay() const;
    [[nodiscard]] int getMonth() const;
    [[nodiscard]] int getYear() const;

    void setDay(int);
    void setMonth(int);
    void setYear(int);
    void set(const string&);

    static List<int> split(const string&);

    string toString() const; // dd/mm/yyyy

    friend bool operator==(const DateTime &, const DateTime &);
};


#endif //FLIGHTMANAGER_DATETIME_H