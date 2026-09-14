#include "Admin.h"
#include <iostream>

// ============================================================
// 【成员C 负责】管理员类实现
// ============================================================

Admin::Admin(std::string username, std::string password, std::string employeeId,
             std::string branch, std::string realName, std::string createTime)
    : Employee(username, password, 3, employeeId, branch, realName, createTime) {}  // role=3 管理员

void Admin::showMenu() {
    std::cout << "\n========== 管理员功能菜单 ==========" << std::endl;
    std::cout << "  欢迎您，" << m_realName << "（管理员）" << std::endl;
    std::cout << "  1. 用户管理（新增/删除/冻结用户）" << std::endl;
    std::cout << "  2. 账户管理（查看所有账户/销户）" << std::endl;
    std::cout << "  3. 查看所有交易流水" << std::endl;
    std::cout << "  4. 系统设置（利率调整）" << std::endl;
    std::cout << "  5. 修改密码" << std::endl;
    std::cout << "  0. 退出登录" << std::endl;
    std::cout << "====================================" << std::endl;
}

std::string Admin::getRoleName() const { return "管理员"; }
