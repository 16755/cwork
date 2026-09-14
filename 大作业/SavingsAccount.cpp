#include "SavingsAccount.h"

// ============================================================
// 【成员A 负责】活期储蓄账户实现
// ============================================================

SavingsAccount::SavingsAccount(std::string accountNo, std::string ownerName,
                               std::string idCard, std::string phone, double balance,
                               std::string ownerUsername, std::string createTime,
                               int status, double interestRate)
    : Account(accountNo, ownerName, idCard, phone, balance, ownerUsername, createTime, status),
      m_interestRate(interestRate) {}

// 活期取款规则：账户正常 + 余额 >= 取款金额 才能成功
bool SavingsAccount::withdraw(double amount) {
    if (m_status != 0) return false;       // 账户冻结或销户
    if (amount <= 0) return false;         // 金额非法
    if (m_balance < amount) return false;  // 余额不足
    m_balance -= amount;
    return true;
}

// 活期结息：按月计算利息（年利率/12），利息加入余额
// 实际银行按日计息，这里简化为按月
void SavingsAccount::settleInterest() {
    if (m_status != 0) return;
    double monthlyInterest = m_balance * m_interestRate / 12.0;
    m_balance += monthlyInterest;
}

std::string SavingsAccount::getAccountType() const { return "活期储蓄"; }
double SavingsAccount::getInterestRate() const { return m_interestRate; }
void SavingsAccount::setInterestRate(double rate) { m_interestRate = rate; }
