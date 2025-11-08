//
// Created by HP on 09/11/2025.
//

#include "../../include/core/DateTime.h"

#include <sstream>

DateTime::DateTime(const string &date) {
    auto itemList = split(date);
    m_iDay = itemList[0];
    m_iMonth = itemList[1];
    m_iYear = itemList[2];
}

int DateTime::getDay() const {
    return m_iDay;
}

int DateTime::getMonth() const {
    return m_iMonth;
}

int DateTime::getYear() const {
    return m_iYear;
}

void DateTime::setDay(int day) {
    m_iDay = day;
}

void DateTime::setMonth(int month) {
    m_iMonth = month;
}

void DateTime::setYear(int year) {
    m_iYear = year;
}

void DateTime::set(const string &date) {
    auto itemList = split(date);
    setDay(itemList[0]);
    setMonth(itemList[1]);
    setYear(itemList[2]);
}

// tach chuoi date ra thanh ngay/thang/nam
vector<int> DateTime::split(const string& date) {

    stringstream spliter(date);
    vector<int> res(3);

    // dung stringstream de tach chuoi khi gap '/'
    string day, month, year;
    getline(spliter, day, '/');
    getline(spliter, month, '/');
    getline(spliter, year, '/');

    // chuyen chuoi thanh so nguyen va cho vao mang ket qua
    res[0] = stoi(day);
    res[1] = stoi(month);
    res[2] = stoi(year);

    return res;
}

string DateTime::toString() const {
    return to_string(m_iDay) + "/" + to_string(m_iMonth) + "/" + to_string(m_iYear);
}

bool operator==(const DateTime& firstArg, const DateTime& secondArg) {
    return  firstArg.m_iDay == secondArg.m_iDay &&
            firstArg.m_iMonth == secondArg.m_iMonth &&
            firstArg.m_iYear == secondArg.m_iYear;
}