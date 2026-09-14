#ifndef FIXEDDEPOSITACCOUNT_H
#define FIXEDDEPOSITACCOUNT_H

#include "Account.h"

// ============================================================
// 【成员A 负责】定期存款账户（继承自Account）
// 特点：有固定存期，到期按定期利率计息，提前支取按活期计息
// 重写 withdraw() 和 settleInterest() 体现多态
// ============================================================
class FixedDepositAccount : public Account {
private:
    int m_termMonths;       // 存期（月）：3/6/12/24/36
    double m_fixedRate;     // 定期年利率
    double m_demandRate;    // 提前支取时的活期利率
    bool m_isExpired;       // 是否已到期
    bool m_interestPaid;    // 是否已结息

public:
    FixedDepositAccount(std::string accountNo, std::string ownerName, std::string idCard,
                        std::string phone, double balance, std::string ownerUsername,
                        std::string createTime = "", int status = 0,
                        int termMonths = 12, double fixedRate = 0.0195,
                        double demandRate = 0.0035);

    // 重写纯虚函数
    bool withdraw(double amount) override;       // 定期取款：到期全额取，提前取按活期
    void settleInterest() override;              // 定期结息：到期一次性结息
    std::string getAccountType() const override; // 返回"定期存款"

    // 定期特有方法
    int getTermMonths() const;
    double getFixedRate() const;
    bool isExpired() const;
    void checkExpired();  // 检查是否到期（根据开户时间和存期计算）
};

#endif
