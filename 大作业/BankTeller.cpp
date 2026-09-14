#include "BankTeller.h"
#include <iostream>

// ============================================================
// 【成员C 负责】柜员类实现
// ============================================================

BankTeller::BankTeller(std::string username, std::string password, std::string employeeId,
                       std::string branch, std::string realName, std::string createTime)
    : Employee(username, password, 2, employeeId, branch, realName, createTime) {}  // role=2 柜员

void BankTeller::showMenu() {
    std::cout << "\n========== 柜员功能菜单 ==========" << std::endl;
    std::cout << "  欢迎您，" << m_realName << "（柜员）" << std::endl;
    std::cout << "  1. 开立新账户" << std::endl;
    std::cout << "  2. 办理存款" << std::endl;
    std::cout << "  3. 办理取款" << std::endl;
    std::cout << "  4. 办理转账" << std::endl;
    std::cout << "  5. 查询账户信息" << std::endl;
    std::cout << "  6. 冻结/解冻账户" << std::endl;
    std::cout << "  7. 修改密码" << std::endl;
    std::cout << "  0. 退出登录" << std::endl;
    std::cout << "==================================" << std::endl;
}

std::string BankTeller::getRoleName() const { return "柜员"; }
