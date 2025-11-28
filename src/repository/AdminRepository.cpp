#include "../../include/repository/AdminRepository.h"

AdminRepository::AdminRepository() {
    loadAllAdmins();
}

AdminRepository::~AdminRepository() {

    loadAllAdmins();
    saveAllAdmins();
    for (const auto& admin : m_admins) {
        delete admin;
    }

    m_admins.clear();
}

void AdminRepository::loadAllAdmins() {
    ifstream reader(PATH);

    if (!reader.is_open()) {
        cerr << "Khong doc duoc file\n";
        return;
    }

    for (auto& admin : m_admins)
        delete admin;
    m_admins.clear();

    // Doc 1 dong, sau do tach du lieu tu dong doc duoc
    string line;
    while (getline(reader, line)) {
        if (line.empty())
            continue;
        stringstream spliter(line);
        string username, password;
        getline(spliter, username, '|'); // tach username
        getline(spliter, password, '|'); // Tach password
        m_admins.add(new Admin(username, password)); // add admin vao repo
    }
    reader.close();
}

void AdminRepository::saveAllAdmins() const {
    ofstream writer(PATH);

    if (!writer.is_open()) {
        cerr << "Khong viet duoc file";
        return;
    }

    for (const auto& admin : m_admins) {
        writer << admin->toString() << endl;
    }
    writer.close();
}

Admin** AdminRepository::getValidateAdmin(const string &username, const string &password) {
    loadAllAdmins();
    // Su dung iterator de duyet cac admin va kiem tra, neu ton tai, return 1 iterator cua admin do
    for (auto admin = m_admins.begin(); admin != m_admins.end(); admin++) {
        if ((*admin)->tryLogin(username, password))
            return admin;
    }

    return undefineAdmin();
}

Admin** AdminRepository::undefineAdmin() {
    loadAllAdmins();
    return m_admins.end();
}
