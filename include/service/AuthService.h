#ifndef AIRPLANEMANAGER_AUTHSERVICE_H
#define AIRPLANEMANAGER_AUTHSERVICE_H
#include "../repository/AdminRepository.h"


class AuthService {
    AdminRepository* m_adminRepository;
    Admin** m_currentAdmin;
public:
    AuthService();
    ~AuthService();

    Admin **getCurrentAdmin() const;
    bool tryLogin(const string&, const string&);
    bool tryChangePassword(const string&, const string&) const;
    void logout();
};


#endif //AIRPLANEMANAGER_AUTHSERVICE_H