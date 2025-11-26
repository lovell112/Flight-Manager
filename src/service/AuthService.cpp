#include "../../include/service/AuthService.h"

AuthService::AuthService() {
    m_adminRepository = new AdminRepository(); // Khoi tao admin repo
    m_currentAdmin = m_adminRepository->undefineAdmin(); // Khoi tao mac dinh khi chua dang nhap
}

AuthService::~AuthService() {
    delete m_adminRepository; // delete repo
}

Admin **AuthService::getCurrentAdmin() const {
    return m_currentAdmin;
}

bool AuthService::tryLogin(const string &username, const string &password) {
    // Lay admin hop le gan cho admin hien tai
    m_currentAdmin = m_adminRepository->getValidateAdmin(username, password);

    // Neu tai khoan khong hop le return false, nguoc lai true
    if (m_currentAdmin == m_adminRepository->undefineAdmin())
        return false;
    return true;
}

bool AuthService::tryChangePassword(const string &oldPassword, const string &newPassword) const {

    // Neu chua dang nhap thi khong the doi mat khau
    if (m_currentAdmin == m_adminRepository->undefineAdmin())
        return false;

    // Neu mat khau cu khong dung thi khong the doi mat khau
    if (!(*m_currentAdmin)->tryChangePassword(oldPassword, newPassword))
        return false;

    return true;
}

void AuthService::logout() {
    // Dang xuat thi admin hien tai se tra ve ban dau
    m_currentAdmin = m_adminRepository->undefineAdmin();
}