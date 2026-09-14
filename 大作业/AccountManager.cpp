#include "AccountManager.h"
#include "FileUtils.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// ============================================================
// 【成员A 负责】账户管理器实现
// ============================================================

AccountManager* AccountManager::m_instance = nullptr;

AccountManager::AccountManager() : m_nextAccountSeq(1) {}

AccountManager::~AccountManager() {
    // 释放所有账户对象内存
    for (auto acc : m_accounts) {
        delete acc;
    }
    m_accounts.clear();
}

// 单例模式：获取唯一实例
AccountManager* AccountManager::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new AccountManager();
    }
    return m_instance;
}

// 生成10位唯一账号，格式：6222 + 6位序号
std::string AccountManager::generateAccountNo() {
    std::stringstream ss;
    ss << "6222" << std::setw(6) << std::setfill('0') << m_nextAccountSeq++;
    return ss.str();
}

// 开户：根据类型创建不同的派生类对象
// type: 1-活期 2-信用卡 3-定期
std::string AccountManager::openAccount(int type, std::string ownerName,
                                        std::string idCard, std::string phone,
                                        double initialDeposit, std::string ownerUsername) {
    std::string accountNo = generateAccountNo();
    Account* acc = nullptr;

    switch (type) {
        case 1:  // 活期储蓄
            acc = new SavingsAccount(accountNo, ownerName, idCard, phone,
                                     initialDeposit, ownerUsername);
            break;
        case 2:  // 信用卡
            acc = new CreditAccount(accountNo, ownerName, idCard, phone,
                                    initialDeposit, ownerUsername);
            break;
        case 3:  // 定期存款
            acc = new FixedDepositAccount(accountNo, ownerName, idCard, phone,
                                          initialDeposit, ownerUsername);
            break;
        default:
            return "";
    }

    m_accounts.push_back(acc);
    saveToFile();  // 开户后立即保存
    return accountNo;
}

bool AccountManager::closeAccount(const std::string& accountNo) {
    Account* acc = findAccount(accountNo);
    if (!acc) return false;
    acc->closeAccount();
    saveToFile();
    return true;
}

Account* AccountManager::findAccount(const std::string& accountNo) {
    for (auto acc : m_accounts) {
        if (acc->getAccountNo() == accountNo) return acc;
    }
    return nullptr;
}

std::vector<Account*> AccountManager::findAccountsByUsername(const std::string& username) {
    std::vector<Account*> result;
    for (auto acc : m_accounts) {
        if (acc->getOwnerUsername() == username) {
            result.push_back(acc);
        }
    }
    return result;
}

const std::vector<Account*>& AccountManager::getAllAccounts() const {
    return m_accounts;
}

bool AccountManager::freezeAccount(const std::string& accountNo) {
    Account* acc = findAccount(accountNo);
    if (!acc) return false;
    acc->freeze();
    saveToFile();
    return true;
}

bool AccountManager::unfreezeAccount(const std::string& accountNo) {
    Account* acc = findAccount(accountNo);
    if (!acc) return false;
    acc->unfreeze();
    saveToFile();
    return true;
}

// 从文件加载账户数据
// 文件格式：账号,户名,身份证,电话,余额,类型,状态,开户时间,所属用户,扩展参数
void AccountManager::loadFromFile() {
    auto lines = FileUtils::readLines("accounts.txt");
    for (const auto& line : lines) {
        auto f = FileUtils::splitLine(line);
        if (f.size() < 9) continue;

        std::string accountNo = f[0];
        std::string ownerName = f[1];
        std::string idCard = f[2];
        std::string phone = f[3];
        double balance = std::stod(f[4]);
        int type = std::stoi(f[5]);
        int status = std::stoi(f[6]);
        std::string createTime = f[7];
        std::string ownerUsername = f[8];

        Account* acc = nullptr;
        switch (type) {
            case 1:
                acc = new SavingsAccount(accountNo, ownerName, idCard, phone,
                                         balance, ownerUsername, createTime, status);
                break;
            case 2:
                acc = new CreditAccount(accountNo, ownerName, idCard, phone,
                                        balance, ownerUsername, createTime, status);
                break;
            case 3:
                acc = new FixedDepositAccount(accountNo, ownerName, idCard, phone,
                                              balance, ownerUsername, createTime, status);
                break;
        }
        if (acc) m_accounts.push_back(acc);

        // 更新账号序号，避免重复
        int seq = std::stoi(accountNo.substr(4));
        if (seq >= m_nextAccountSeq) m_nextAccountSeq = seq + 1;
    }
}

// 保存所有账户到文件
void AccountManager::saveToFile() {
    std::vector<std::string> lines;
    for (auto acc : m_accounts) {
        // 确定账户类型编号
        int type = 0;
        if (dynamic_cast<SavingsAccount*>(acc)) type = 1;
        else if (dynamic_cast<CreditAccount*>(acc)) type = 2;
        else if (dynamic_cast<FixedDepositAccount*>(acc)) type = 3;

        std::string line = acc->getAccountNo() + "," + acc->getOwnerName() + "," +
                           acc->getIdCard() + "," + acc->getPhone() + "," +
                           std::to_string(acc->getBalance()) + "," +
                           std::to_string(type) + "," +
                           std::to_string(acc->getStatus()) + "," +
                           acc->getCreateTime() + "," + acc->getOwnerUsername();
        lines.push_back(line);
    }
    FileUtils::writeLines("accounts.txt", lines);
}
