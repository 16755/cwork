#include "UserManager.h"
#include "FileUtils.h"

// ============================================================
// 【成员C 负责】用户管理器实现
// ============================================================

UserManager* UserManager::m_instance = nullptr;

UserManager::UserManager() : m_currentUser(nullptr) {}

UserManager::~UserManager() {
    for (auto user : m_users) {
        delete user;
    }
    m_users.clear();
}

UserManager* UserManager::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new UserManager();
    }
    return m_instance;
}

// 客户注册
bool UserManager::registerCustomer(std::string username, std::string password,
                                   std::string realName, std::string idCard,
                                   std::string phone) {
    if (usernameExists(username)) return false;
    Customer* customer = new Customer(username, password, realName, idCard, phone);
    m_users.push_back(customer);
    saveToFile();
    return true;
}

// 员工注册（柜员/管理员）
bool UserManager::registerEmployee(std::string username, std::string password, int role,
                                   std::string employeeId, std::string branch,
                                   std::string realName) {
    if (usernameExists(username)) return false;
    if (role != 2 && role != 3) return false;  // 只能是柜员或管理员
    Employee* emp = nullptr;
    if (role == 2) {
        emp = new BankTeller(username, password, employeeId, branch, realName);
    } else {
        emp = new Admin(username, password, employeeId, branch, realName);
    }
    m_users.push_back(emp);
    saveToFile();
    return true;
}

// 登录验证
bool UserManager::login(std::string username, std::string password) {
    User* user = findUser(username);
    if (!user) return false;
    if (user->verifyPassword(password)) {
        m_currentUser = user;
        return true;
    }
    return false;
}

void UserManager::logout() {
    m_currentUser = nullptr;
}

User* UserManager::findUser(const std::string& username) {
    for (auto user : m_users) {
        if (user->getUsername() == username) return user;
    }
    return nullptr;
}

bool UserManager::deleteUser(const std::string& username) {
    for (auto it = m_users.begin(); it != m_users.end(); ++it) {
        if ((*it)->getUsername() == username) {
            if (m_currentUser == *it) m_currentUser = nullptr;
            delete *it;
            m_users.erase(it);
            saveToFile();
            return true;
        }
    }
    return false;
}

const std::vector<User*>& UserManager::getAllUsers() const {
    return m_users;
}

User* UserManager::getCurrentUser() const {
    return m_currentUser;
}

bool UserManager::usernameExists(const std::string& username) const {
    for (auto user : m_users) {
        if (user->getUsername() == username) return true;
    }
    return false;
}

// 从文件加载用户数据
// 文件格式：用户名,密码,角色,创建时间,扩展字段(真实姓名/身份证/电话/员工编号/网点)
void UserManager::loadFromFile() {
    auto lines = FileUtils::readLines("users.txt");
    for (const auto& line : lines) {
        auto f = FileUtils::splitLine(line);
        if (f.size() < 4) continue;

        std::string username = f[0];
        std::string password = f[1];
        int role = std::stoi(f[2]);
        std::string createTime = f[3];

        User* user = nullptr;
        if (role == 1 && f.size() >= 7) {
            // 客户：用户名,密码,1,创建时间,真实姓名,身份证,电话
            user = new Customer(username, password, f[4], f[5], f[6], createTime);
        } else if (role == 2 && f.size() >= 7) {
            // 柜员：用户名,密码,2,创建时间,员工编号,网点,真实姓名
            user = new BankTeller(username, password, f[4], f[5], f[6], createTime);
        } else if (role == 3 && f.size() >= 7) {
            // 管理员：用户名,密码,3,创建时间,员工编号,网点,真实姓名
            user = new Admin(username, password, f[4], f[5], f[6], createTime);
        }
        if (user) m_users.push_back(user);
    }
}

// 保存所有用户到文件
void UserManager::saveToFile() {
    std::vector<std::string> lines;
    for (auto user : m_users) {
        std::string line;
        int role = user->getRole();
        line = user->getUsername() + "," + user->getPassword() + "," +
               std::to_string(role) + "," + user->getCreateTime();

        if (role == 1) {
            Customer* c = dynamic_cast<Customer*>(user);
            if (c) line += "," + c->getRealName() + "," + c->getIdCard() + "," + c->getPhone();
        } else {
            Employee* e = dynamic_cast<Employee*>(user);
            if (e) line += "," + e->getEmployeeId() + "," + e->getBranch() + "," + e->getRealName();
        }
        lines.push_back(line);
    }
    FileUtils::writeLines("users.txt", lines);
}
