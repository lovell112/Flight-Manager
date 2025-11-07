#ifndef AIRPLANEMANAGER_AUTHSERVICE_H
#define AIRPLANEMANAGER_AUTHSERVICE_H
#include "../repository/AdminRepository.h"


class AuthService {
    AdminRepository* m_adminRepository;
    vector<Admin*>::iterator m_currentAdmin;
public:
    AuthService();
    ~AuthService();
    const vector<Admin*>::iterator& getCurrentAdmin() const;
    bool tryLogin(const string&, const string&);
    bool tryChangePassword(const string&, const string&);
    void logout();
};


#endif //AIRPLANEMANAGER_AUTHSERVICE_H