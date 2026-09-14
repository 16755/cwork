#include "CreditAccount.h"

// ============================================================
// 【成员A 负责】信用卡账户实现
// ============================================================

CreditAccount::CreditAccount(std::string accountNo, std::string ownerName,
                             std::string idCard, std::string phone, double balance,
                             std::string ownerUsername, std::string createTime,
                             int status, double creditLimit, double cashFeeRate,
                             double annualRate)
    : Account(accountNo, ownerName, idCard, phone, balance, ownerUsername, createTime, status),
      m_creditLimit(creditLimit), m_cashFeeRate(cashFeeRate),
      m_annualRate(annualRate), m_usedCredit(0) {}

// 信用卡取现规则：
// 1. 账户必须正常
// 2. 可取金额 = 余额 + (信用额度 - 已用额度)
// 3. 先扣余额，余额不够再透支
// 4. 透支部分收取手续费
bool CreditAccount::withdraw(double amount) {
    if (m_status != 0) return false;
    if (amount <= 0) return false;

    double available = m_balance + (m_creditLimit - m_usedCredit);
    if (amount > available) return false;  // 超出可用额度

    double fee = 0;
    if (amount > m_balance) {
        // 需要透支的部分
        double overdraft = amount - m_balance;
        fee = overdraft * m_cashFeeRate;  // 取现手续费
        m_usedCredit += overdraft;
        m_balance = 0;
    } else {
        m_balance -= amount;
    }

    // 手续费从余额扣除（如果余额不够则增加透支）
    if (fee > 0) {
        if (m_balance >= fee) {
            m_balance -= fee;
        } else {
            m_usedCredit += (fee - m_balance);
            m_balance = 0;
        }
    }
    return true;
}

// 信用卡结息：对已用透支部分按月计息
void CreditAccount::settleInterest() {
    if (m_status != 0 || m_usedCredit <= 0) return;
    double monthlyInterest = m_usedCredit * m_annualRate / 12.0;
    m_usedCredit += monthlyInterest;  // 利息计入透支金额
}

// 还款：先还透支，多余的进余额
void CreditAccount::repay(double amount) {
    if (amount <= 0) return;
    if (amount <= m_usedCredit) {
        m_usedCredit -= amount;
    } else {
        m_balance += (amount - m_usedCredit);
        m_usedCredit = 0;
    }
}

double CreditAccount::getAvailableCredit() const {
    return m_creditLimit - m_usedCredit + m_balance;
}
double CreditAccount::getCreditLimit() const { return m_creditLimit; }
double CreditAccount::getUsedCredit() const { return m_usedCredit; }
std::string CreditAccount::getAccountType() const { return "信用卡"; }
