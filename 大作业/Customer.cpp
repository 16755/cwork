#include "Customer.h"
#include <iostream>

// ============================================================
// 【成员C 负责】客户类实现
// ============================================================

Customer::Customer(std::string username, std::string password, std::string realName,
                   std::string idCard, std::string phone, std::string createTime)
    : User(username, password, 1, createTime),  // role=1 表示客户
      m_realName(realName), m_idCard(idCard), m_phone(phone) {}

// 客户菜单：只能操作自己的账户
void Customer::showMenu() {
    std::cout << "\n========== 客户功能菜单 ==========" << std::endl;
    std::cout << "  欢迎您，" << m_realName << "（客户）" << std::endl;
    std::cout << "  1. 查看我的账户" << std::endl;
    std::cout << "  2. 存款" << std::endl;
    std::cout << "  3. 取款" << std::endl;
    std::cout << "  4. 转账" << std::endl;
    std::cout << "  5. 查询交易记录" << std::endl;
    std::cout << "  6. 修改密码" << std::endl;
    std::cout << "  0. 退出登录" << std::endl;
    std::cout << "==================================" << std::endl;
}

std::string Customer::getRoleName() const { return "客户"; }

std::string Customer::getRealName() const { return m_realName; }
std::string Customer::getIdCard() const { return m_idCard; }
std::string Customer::getPhone() const { return m_phone; }
void Customer::setPhone(const std::string& phone) { m_phone = phone; }
