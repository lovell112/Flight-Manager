#ifndef AIRPLANEMANAGER_ADMIN_H
#define AIRPLANEMANAGER_ADMIN_H
#include <string>
#include <iostream>
using namespace std;

class Admin {
    string m_strUsername;
    string m_strPassword;
public:
    Admin(const string&, const string&);
    ~Admin();
    bool tryLogin(const string&, const string&) const;
    bool tryChangePassword(const string&, const string&);
    string toString() const;
    void printAdminInfo() const;
};


#endif //AIRPLANEMANAGER_ADMIN_H