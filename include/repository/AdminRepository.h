#ifndef FLIGHTMANAGER_ADMINREPOSITORY_H
#define FLIGHTMANAGER_ADMINREPOSITORY_H
#include "../core/Admin.h"
#include <string>
#include <fstream>
#include <sstream>
#include "../datastructures/List.hpp"
using namespace std;

class AdminRepository {
    List<Admin*> m_admins;
    const string PATH = "../data/admin.txt";
public:
    AdminRepository();
    ~AdminRepository();
    void loadAllAdmins();
    void saveAllAdmins() const;
    Admin** getValidateAdmin(const string&, const string&);
    Admin** begin();
    Admin** undefineAdmin();
};


#endif //FLIGHTMANAGER_ADMINREPOSITORY_H