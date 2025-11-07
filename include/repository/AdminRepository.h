#ifndef FLIGHTMANAGER_ADMINREPOSITORY_H
#define FLIGHTMANAGER_ADMINREPOSITORY_H
#include <string>
#include <vector>
using namespace std;

class AdminRepository {
    vector<AdminRepository*> m_adminRepository;
    string PATH = "../../data/admin.txt";
public:
    void loadAllAdmins() const;
    void saveAllAdmins() const;
    bool validateLogin(const string&, const string&) const;
    bool changePassword(const string&, const string&);
};


#endif //FLIGHTMANAGER_ADMINREPOSITORY_H