#include "FixedDepositAccount.h"
#include <ctime>
#include <sstream>

// ============================================================
// 【成员A 负责】定期存款账户实现
// ============================================================

FixedDepositAccount::FixedDepositAccount(std::string accountNo, std::string ownerName,
                                         std::string idCard, std::string phone,
                                         double balance, std::string ownerUsername,
                                         std::string createTime, int status,
                                         int termMonths, double fixedRate, double demandRate)
    : Account(accountNo, ownerName, idCard, phone, balance, ownerUsername, createTime, status),
      m_termMonths(termMonths), m_fixedRate(fixedRate),
      m_demandRate(demandRate), m_isExpired(false), m_interestPaid(false) {}

// 定期取款规则：
// 1. 定期账户只能全额支取（简化处理）
// 2. 到期支取：按定期利率计息
// 3. 提前支取：按活期利率计息，损失利息
bool FixedDepositAccount::withdraw(double amount) {
    if (m_status != 0) return false;
    if (amount <= 0) return false;
    if (amount != m_balance) return false;  // 定期只能全额取（简化）

    if (!m_interestPaid) {
        settleInterest();  // 取款前先结息
    }
    m_balance = 0;
    m_status = 2;  // 销户
    return true;
}

// 定期结息：
// - 已到期：按定期利率计算全部存期利息
// - 未到期：按活期利率计算已存时间利息（简化为按比例）
void FixedDepositAccount::settleInterest() {
    if (m_status != 0 || m_interestPaid) return;

    double interest;
    if (m_isExpired) {
        // 到期：定期利息 = 本金 × 年利率 × 存期年数
        interest = m_balance * m_fixedRate * (m_termMonths / 12.0);
    } else {
        // 提前支取：按活期利率（简化为存了一半时间）
        interest = m_balance * m_demandRate * (m_termMonths / 24.0);
    }
    m_balance += interest;
    m_interestPaid = true;
}

// 检查是否到期（简化：根据开户时间+存期与当前时间比较）
void FixedDepositAccount::checkExpired() {
    // 实际实现需要解析日期字符串计算月份差
    // 这里简化处理，第一版暂不自动判断，由系统手动标记
    // TODO: 实现完整的日期比较逻辑
}

int FixedDepositAccount::getTermMonths() const { return m_termMonths; }
double FixedDepositAccount::getFixedRate() const { return m_fixedRate; }
bool FixedDepositAccount::isExpired() const { return m_isExpired; }
std::string FixedDepositAccount::getAccountType() const { return "定期存款"; }
