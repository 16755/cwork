#include "Employee.h"

// ============================================================
// 【成员C 负责】员工基类实现
// ============================================================

Employee::Employee(std::string username, std::string password, int role,
                   std::string employeeId, std::string branch, std::string realName,
                   std::string createTime)
    : User(username, password, role, createTime),
      m_employeeId(employeeId), m_branch(branch), m_realName(realName) {}

std::string Employee::getEmployeeId() const { return m_employeeId; }
std::string Employee::getBranch() const { return m_branch; }
std::string Employee::getRealName() const { return m_realName; }
