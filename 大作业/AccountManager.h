#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "Account.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include "FixedDepositAccount.h"
#include <vector>
#include <string>

// ============================================================
// 【成员A 负责】账户统一管理器（单例模式）
// 作用：统一管理所有账户对象，提供增删改查、文件持久化
// 内部用 vector<Account*> 存储，利用多态统一处理不同账户类型
// ============================================================
class AccountManager {
private:
    std::vector<Account*> m_accounts;  // 账户对象容器（基类指针，体现多态）
    static AccountManager* m_instance; // 单例实例
    int m_nextAccountSeq;              // 账号生成序号

    AccountManager();  // 私有构造函数（单例模式）
    ~AccountManager();

public:
    // 获取单例实例
    static AccountManager* getInstance();

    // ===== 账户操作 =====
    // 开户：根据类型创建不同账户对象，返回账号
    std::string openAccount(int type, std::string ownerName, std::string idCard,
                            std::string phone, double initialDeposit, std::string ownerUsername);
    // 销户
    bool closeAccount(const std::string& accountNo);
    // 按账号查找账户
    Account* findAccount(const std::string& accountNo);
    // 按用户名查找所有账户
    std::vector<Account*> findAccountsByUsername(const std::string& username);
    // 获取所有账户
    const std::vector<Account*>& getAllAccounts() const;
    // 冻结/解冻账户
    bool freezeAccount(const std::string& accountNo);
    bool unfreezeAccount(const std::string& accountNo);

    // ===== 文件持久化 =====
    void loadFromFile();   // 从 accounts.txt 加载
    void saveToFile();     // 保存到 accounts.txt

    // 生成唯一账号（10位数字）
    std::string generateAccountNo();
};

#endif
