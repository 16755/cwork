#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include "Customer.h"
#include "Employee.h"
#include "BankTeller.h"
#include "Admin.h"
#include <vector>
#include <string>

// ============================================================
// 【成员C 负责】用户统一管理器（单例模式）
// 作用：管理所有用户账号，提供注册、登录、权限校验、文件持久化
// 内部用 vector<User*> 存储，利用多态统一处理不同角色
// ============================================================
class UserManager {
private:
    std::vector<User*> m_users;  // 用户对象容器（基类指针）
    static UserManager* m_instance;
    User* m_currentUser;         // 当前登录用户

    UserManager();
    ~UserManager();

public:
    static UserManager* getInstance();

    // ===== 用户操作 =====
    // 客户注册
    bool registerCustomer(std::string username, std::string password,
                          std::string realName, std::string idCard, std::string phone);
    // 员工注册（柜员/管理员，由管理员调用）
    bool registerEmployee(std::string username, std::string password, int role,
                          std::string employeeId, std::string branch, std::string realName);
    // 登录验证，成功返回true并设置当前用户
    bool login(std::string username, std::string password);
    // 登出
    void logout();
    // 按用户名查找
    User* findUser(const std::string& username);
    // 删除用户
    bool deleteUser(const std::string& username);
    // 获取所有用户
    const std::vector<User*>& getAllUsers() const;
    // 获取当前登录用户
    User* getCurrentUser() const;
    // 检查用户名是否已存在
    bool usernameExists(const std::string& username) const;

    // ===== 文件持久化 =====
    void loadFromFile();
    void saveToFile();
};

#endif
