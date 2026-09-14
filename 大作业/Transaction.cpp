#include "Transaction.h"
#include "FileUtils.h"

// ============================================================
// 【成员B 负责】交易记录实体类实现
// ============================================================

Transaction::Transaction(std::string id, std::string time, std::string from,
                         std::string to, double amount, int type, int status,
                         std::string remark)
    : m_transactionId(id), m_time(time), m_fromAccount(from), m_toAccount(to),
      m_amount(amount), m_type(type), m_status(status), m_remark(remark) {}

// ===== Getter实现 =====
std::string Transaction::getTransactionId() const { return m_transactionId; }
std::string Transaction::getTime() const { return m_time; }
std::string Transaction::getFromAccount() const { return m_fromAccount; }
std::string Transaction::getToAccount() const { return m_toAccount; }
double Transaction::getAmount() const { return m_amount; }
int Transaction::getType() const { return m_type; }
int Transaction::getStatus() const { return m_status; }
std::string Transaction::getRemark() const { return m_remark; }

std::string Transaction::getTypeText() const {
    switch (m_type) {
        case 1: return "存款";
        case 2: return "取款";
        case 3: return "转账";
        case 4: return "结息";
        case 5: return "还款";
        default: return "未知";
    }
}

std::string Transaction::getStatusText() const {
    return m_status == 0 ? "成功" : "失败";
}

// 序列化为文件存储格式
std::string Transaction::serialize() const {
    return m_transactionId + "," + m_time + "," + m_fromAccount + "," +
           m_toAccount + "," + std::to_string(m_amount) + "," +
           std::to_string(m_type) + "," + std::to_string(m_status) + "," + m_remark;
}

// 从文件行反序列化
Transaction Transaction::deserialize(const std::string& line) {
    auto fields = FileUtils::splitLine(line);
    // 确保至少有8个字段
    while (fields.size() < 8) fields.push_back("");
    return Transaction(
        fields[0], fields[1], fields[2], fields[3],
        std::stod(fields[4]), std::stoi(fields[5]),
        std::stoi(fields[6]), fields[7]
    );
}
