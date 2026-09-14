#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// ============================================================
// 【成员B 负责】交易记录实体类
// 作用：封装每一笔交易的完整信息，由TransactionManager统一管理
// 交易类型：1-存款 2-取款 3-转账 4-结息 5-还款
// ============================================================
class Transaction {
private:
    std::string m_transactionId;   // 交易流水号（唯一）
    std::string m_time;            // 交易时间
    std::string m_fromAccount;     // 付款账号（存款时为空）
    std::string m_toAccount;       // 收款账号（取款时为空）
    double m_amount;               // 交易金额
    int m_type;                    // 交易类型：1-存款 2-取款 3-转账 4-结息 5-还款
    int m_status;                  // 状态：0-成功 1-失败
    std::string m_remark;          // 备注

public:
    Transaction(std::string id, std::string time, std::string from, std::string to,
                double amount, int type, int status, std::string remark);

    // ===== Getter =====
    std::string getTransactionId() const;
    std::string getTime() const;
    std::string getFromAccount() const;
    std::string getToAccount() const;
    double getAmount() const;
    int getType() const;
    int getStatus() const;
    std::string getRemark() const;

    std::string getTypeText() const;   // 交易类型文字描述
    std::string getStatusText() const; // 状态文字描述

    // 序列化为文件存储格式（逗号分隔）
    std::string serialize() const;
    // 从文件行反序列化
    static Transaction deserialize(const std::string& line);
};

#endif
