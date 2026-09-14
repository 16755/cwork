#include "Account.h"
#include <ctime>
#include <sstream>
#include <iomanip>

// ============================================================
// 【成员A 负责】账户基类实现
// ============================================================

Account::Account(std::string accountNo, std::string ownerName, std::string idCard,
                 std::string phone, double balance, std::string ownerUsername,
                 std::string createTime, int status)
    : m_accountNo(accountNo), m_ownerName(ownerName), m_idCard(idCard),
      m_phone(phone), m_balance(balance), m_ownerUsername(ownerUsername),
      m_status(status) {
    if (createTime.empty()) {
        // 自动获取当前日期
        const time_t now = time(nullptr);
        tm localTime{};
#ifdef _WIN32
        localtime_s(&localTime, &now);
#else
        localtime_r(&now, &localTime);
#endif
        std::stringstream ss;
        ss << 1900 + localTime.tm_year << "-"
           << std::setw(2) << std::setfill('0') << 1 + localTime.tm_mon << "-"
           << std::setw(2) << std::setfill('0') << localTime.tm_mday;
        m_createTime = ss.str();
    } else {
        m_createTime = createTime;
    }
}

Account::~Account() {}

// 存款：所有账户类型规则相同，直接增加余额
void Account::deposit(double amount) {
    if (amount > 0 && m_status == 0) {
        m_balance += amount;
    }
}

bool Account::isFrozen() const { return m_status == 1; }
void Account::freeze() { if (m_status == 0) m_status = 1; }
void Account::unfreeze() { if (m_status == 1) m_status = 0; }
void Account::closeAccount() { m_status = 2; m_balance = 0; }

// ===== Getter实现 =====
std::string Account::getAccountNo() const { return m_accountNo; }
std::string Account::getOwnerName() const { return m_ownerName; }
std::string Account::getIdCard() const { return m_idCard; }
std::string Account::getPhone() const { return m_phone; }
double Account::getBalance() const { return m_balance; }
std::string Account::getCreateTime() const { return m_createTime; }
int Account::getStatus() const { return m_status; }
std::string Account::getOwnerUsername() const { return m_ownerUsername; }

std::string Account::getStatusText() const {
    switch (m_status) {
        case 0: return "正常";
        case 1: return "冻结";
        case 2: return "已销户";
        default: return "未知";
    }
}

void Account::setPhone(const std::string& phone) { m_phone = phone; }
