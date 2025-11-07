#ifndef FLIGHTMANAGER_ADMINREPOSITORY_H
#define FLIGHTMANAGER_ADMINREPOSITORY_H
#include "../core/Admin.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class AdminRepository {
    vector<Admin*> m_admins;
    const string PATH = "../data/admin.txt";
public:
    AdminRepository();
    ~AdminRepository();
    void loadAllAdmins();
    void saveAllAdmins() const;
    vector<Admin*>::iterator getValidateAdmin(const string&, const string&);
    vector<Admin*>::iterator begin();
    vector<Admin*>::iterator invalidAdmin();
};


#endif //FLIGHTMANAGER_ADMINREPOSITORY_H