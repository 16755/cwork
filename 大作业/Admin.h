#ifndef ADMIN_H
#define ADMIN_H

#include "Employee.h"

// ============================================================
// 【成员C 负责】管理员类（继承自Employee）
// 继承链：User → Employee → Admin
// 角色：系统管理员，拥有最高权限，可以管理用户、查看所有数据
// ============================================================
class Admin : public Employee {
public:
    Admin(std::string username, std::string password, std::string employeeId,
          std::string branch, std::string realName, std::string createTime = "");

    // 重写纯虚函数
    void showMenu() override;
    std::string getRoleName() const override;
};

#endif
