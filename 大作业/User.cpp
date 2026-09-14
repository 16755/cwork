#include "User.h"
#include <ctime>
#include <sstream>
#include <iomanip>

// ============================================================
// 【成员C 负责】用户基类实现
// ============================================================

User::User(std::string username, std::string password, int role, std::string createTime)
    : m_username(username), m_password(password), m_role(role) {
    if (createTime.empty()) {
        // 自动获取当前时间作为创建时间
        const time_t now = time(nullptr);
        tm localTime{};
#ifdef _WIN32
        localtime_s(&localTime, &now);
#else
        localtime_r(&now, &localTime);
#endif
        std::stringstream ss;
        ss << 1900 + localTime.tm_year << "-"
           << std::setw(2) << std::setfill('0') << 1 + localTime.tm_mon << "-"
           << std::setw(2) << std::setfill('0') << localTime.tm_mday;
        m_createTime = ss.str();
    } else {
        m_createTime = createTime;
    }
}

User::~User() {}

// 密码验证：直接比较输入密码与存储密码
bool User::verifyPassword(const std::string& inputPwd) const {
    return inputPwd == m_password;
}

// 修改密码：先验证旧密码，再更新
bool User::changePassword(const std::string& oldPwd, const std::string& newPwd) {
    if (!verifyPassword(oldPwd)) return false;
    m_password = newPwd;
    return true;
}

// ===== Getter实现 =====
std::string User::getUsername() const { return m_username; }
int User::getRole() const { return m_role; }
std::string User::getCreateTime() const { return m_createTime; }
std::string User::getPassword() const { return m_password; }
