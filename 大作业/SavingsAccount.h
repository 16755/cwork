#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

// ============================================================
// 【成员A 负责】活期储蓄账户（继承自Account）
// 特点：随时存取，按活期利率按月结息
// 重写 withdraw() 和 settleInterest() 体现多态
// ============================================================
class SavingsAccount : public Account {
private:
    double m_interestRate;  // 活期年利率（默认0.35%）

public:
    SavingsAccount(std::string accountNo, std::string ownerName, std::string idCard,
                   std::string phone, double balance, std::string ownerUsername,
                   std::string createTime = "", int status = 0,
                   double interestRate = 0.0035);

    // 重写纯虚函数
    bool withdraw(double amount) override;       // 活期取款：余额充足即可
    void settleInterest() override;              // 活期结息：按月计算利息
    std::string getAccountType() const override; // 返回"活期储蓄"

    double getInterestRate() const;
    void setInterestRate(double rate);
};

#endif
