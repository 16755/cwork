#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"
#include <string>

// ============================================================
// 【成员C 负责】员工基类（继承自User）
// 这是第二层继承：User → Employee → BankTeller / Admin
// 柜员和管理员都属于员工，共享员工编号、所属网点等属性
// ============================================================
class Employee : public User {
protected:
    std::string m_employeeId;   // 员工编号
    std::string m_branch;       // 所属网点
    std::string m_realName;     // 真实姓名

public:
    Employee(std::string username, std::string password, int role,
             std::string employeeId, std::string branch, std::string realName,
             std::string createTime = "");

    // 员工通用方法
    std::string getEmployeeId() const;
    std::string getBranch() const;
    std::string getRealName() const;
};

#endif
