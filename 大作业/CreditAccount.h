#ifndef CREDITACCOUNT_H
#define CREDITACCOUNT_H

#include "Account.h"

// ============================================================
// 【成员A 负责】信用卡账户（继承自Account）
// 特点：可透支，有信用额度，取现收手续费，按账单日计息
// 重写 withdraw() 和 settleInterest() 体现多态
// ============================================================
class CreditAccount : public Account {
private:
    double m_creditLimit;     // 信用额度
    double m_cashFeeRate;     // 取现手续费率（默认1%）
    double m_annualRate;      // 年化利率（默认18%）
    double m_usedCredit;      // 已用额度（透支金额）

public:
    CreditAccount(std::string accountNo, std::string ownerName, std::string idCard,
                  std::string phone, double balance, std::string ownerUsername,
                  std::string createTime = "", int status = 0,
                  double creditLimit = 10000.0, double cashFeeRate = 0.01,
                  double annualRate = 0.18);

    // 重写纯虚函数
    bool withdraw(double amount) override;       // 信用卡取现：可透支+收手续费
    void settleInterest() override;              // 信用卡结息：对未还透支部分计息
    std::string getAccountType() const override; // 返回"信用卡"

    // 信用卡特有方法
    double getAvailableCredit() const;  // 可用额度 = 信用额度 - 已用额度 + 余额
    double getCreditLimit() const;
    double getUsedCredit() const;
    void repay(double amount);          // 还款
};

#endif
