//
// Created by HP on 05/11/2025.
//

#include "../../include/core/Admin.h"

bool Admin::login(const string &username, const string &password) const {
    if (username == m_strUsername && password == m_strPassword)
        return true;
    return false;
}

bool Admin::changePassword(const string &oldPassword, const string &newPassword) {
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