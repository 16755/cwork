#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <string>

// ============================================================
// 【成员C 负责】客户类（继承自User）
// 角色：普通银行客户，只能操作自己的账户
// 重写showMenu()体现多态
// ============================================================
class Customer : public User {
private:
    std::string m_realName;    // 真实姓名
    std::string m_idCard;      // 身份证号
    std::string m_phone;       // 手机号

public:
    Customer(std::string username, std::string password, std::string realName,
             std::string idCard, std::string phone, std::string createTime = "");

    // 重写纯虚函数
    void showMenu() override;           // 显示客户功能菜单
    std::string getRoleName() const override;  // 返回"客户"

    // 客户特有方法
    std::string getRealName() const;
    std::string getIdCard() const;
    std::string getPhone() const;
    void setPhone(const std::string& phone);
};

#endif
