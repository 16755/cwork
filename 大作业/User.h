#ifndef USER_H
#define USER_H

#include <string>

// ============================================================
// 【成员C 负责】用户基类
// 继承体系：User → Customer / Employee → BankTeller / Admin
// 这是整个用户权限体系的根类，体现封装与继承
// ============================================================
class User {
protected:
    std::string m_username;    // 用户名（登录账号）
    std::string m_password;    // 密码（明文存储）
    int m_role;                // 角色：1-客户 2-柜员 3-管理员
    std::string m_createTime;  // 账号创建时间

public:
    // 构造函数
    User(std::string username, std::string password, int role, std::string createTime = "");
    virtual ~User();  // 虚析构函数，保证派生类正确析构

    // ===== 纯虚函数：派生类必须重写，体现多态 =====
    // 显示该角色的功能菜单，不同角色菜单不同
    virtual void showMenu() = 0;
    // 获取角色名称字符串
    virtual std::string getRoleName() const = 0;

    // ===== 通用方法 =====
    bool verifyPassword(const std::string& inputPwd) const;  // 验证密码
    bool changePassword(const std::string& oldPwd, const std::string& newPwd);  // 修改密码

    // ===== Getter方法 =====
    std::string getUsername() const;
    int getRole() const;
    std::string getCreateTime() const;
    std::string getPassword() const;  // 用于文件存储
};

#endif
