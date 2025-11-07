//
// Created by HP on 05/11/2025.
//

#ifndef AIRPLANEMANAGER_ADMIN_H
#define AIRPLANEMANAGER_ADMIN_H
#include <string>
#include <iostream>
using namespace std;

class Admin {
    string m_strUsername;
    string m_strPassword;
public:
    bool login(const string&, const string&) const;
    bool changePassword(const string&, const string&);
    string toString() const;
    void printAdminInfo() const;
};


#endif //AIRPLANEMANAGER_ADMIN_H