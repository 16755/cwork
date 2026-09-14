#ifndef BANKTELLER_H
#define BANKTELLER_H

#include "Employee.h"

// ============================================================
// 【成员C 负责】柜员类（继承自Employee）
// 继承链：User → Employee → BankTeller
// 角色：银行柜员，可以开户、办理存取款、查询所有账户
// ============================================================
class BankTeller : public Employee {
public:
    BankTeller(std::string username, std::string password, std::string employeeId,
               std::string branch, std::string realName, std::string createTime = "");

    // 重写纯虚函数
    void showMenu() override;
    std::string getRoleName() const override;
};

#endif
