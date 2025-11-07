#include "../../include/core/Admin.h"

Admin::Admin(const string& username, const string& password) : m_strUsername(username), m_strPassword(password) {}

Admin::~Admin() {}

bool Admin::tryLogin(const string &username, const string &password) const {
    if (username == m_strUsername && password == m_strPassword)
        return true;
    return false;
}

// Neu thoa man cac dieu kien thi doi mat khau, return true; nguoc lai khong doi, return false
bool Admin::tryChangePassword(const string &oldPassword, const string &newPassword) {
    if (oldPassword != m_strPassword || oldPassword == newPassword)
        return false;
    m_strPassword = newPassword;
    return true;
}

string Admin::toString() const {
    return m_strUsername + "|" + m_strPassword;
}

void Admin::printAdminInfo() const {
    cout << m_strUsername << " " << m_strPassword << endl;
}