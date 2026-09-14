#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include "Transaction.h"
#include <vector>
#include <string>

// ============================================================
// 【成员B 负责】交易流水管理器（单例模式）
// 作用：记录所有交易、提供查询、文件持久化
// 与AccountManager配合完成存取款转账等核心业务
// ============================================================
class TransactionManager {
private:
    std::vector<Transaction> m_transactions;  // 交易记录容器
    static TransactionManager* m_instance;
    int m_nextSeq;  // 流水号生成序号

    TransactionManager();
    ~TransactionManager();

public:
    static TransactionManager* getInstance();

    // ===== 交易操作 =====
    // 记录一笔交易
    void recordTransaction(std::string fromAccount, std::string toAccount,
                           double amount, int type, int status, std::string remark);
    // 按账号查询交易记录（付款或收款方匹配）
    std::vector<Transaction> queryByAccount(const std::string& accountNo);
    // 按交易类型查询
    std::vector<Transaction> queryByType(int type);
    // 获取所有交易
    const std::vector<Transaction>& getAllTransactions() const;

    // ===== 文件持久化 =====
    void loadFromFile();
    void saveToFile();

    // 生成唯一交易流水号
    std::string generateTransactionId();
};

#endif
