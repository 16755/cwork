#include "TransactionManager.h"
#include "FileUtils.h"
#include <ctime>
#include <sstream>
#include <iomanip>

// ============================================================
// 【成员B 负责】交易流水管理器实现
// ============================================================

TransactionManager* TransactionManager::m_instance = nullptr;

static tm getLocalTime(time_t time) {
    tm result{};
#ifdef _WIN32
    localtime_s(&result, &time);
#else
    localtime_r(&time, &result);
#endif
    return result;
}

TransactionManager::TransactionManager() : m_nextSeq(1) {}

TransactionManager::~TransactionManager() {}

TransactionManager* TransactionManager::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new TransactionManager();
    }
    return m_instance;
}

// 生成交易流水号：TX + 年月日 + 6位序号
std::string TransactionManager::generateTransactionId() {
    const time_t now = time(nullptr);
    const tm localTime = getLocalTime(now);
    std::stringstream ss;
    ss << "TX" << 1900 + localTime.tm_year
       << std::setw(2) << std::setfill('0') << 1 + localTime.tm_mon
       << std::setw(2) << std::setfill('0') << localTime.tm_mday
       << std::setw(6) << std::setfill('0') << m_nextSeq++;
    return ss.str();
}

// 获取当前时间字符串
static std::string currentTime() {
    const time_t now = time(nullptr);
    const tm localTime = getLocalTime(now);
    std::stringstream ss;
    ss << 1900 + localTime.tm_year << "-"
       << std::setw(2) << std::setfill('0') << 1 + localTime.tm_mon << "-"
       << std::setw(2) << std::setfill('0') << localTime.tm_mday << " "
       << std::setw(2) << std::setfill('0') << localTime.tm_hour << ":"
       << std::setw(2) << std::setfill('0') << localTime.tm_min << ":"
       << std::setw(2) << std::setfill('0') << localTime.tm_sec;
    return ss.str();
}

// 记录一笔交易
void TransactionManager::recordTransaction(std::string fromAccount, std::string toAccount,
                                            double amount, int type, int status,
                                            std::string remark) {
    std::string id = generateTransactionId();
    std::string time = currentTime();
    Transaction tx(id, time, fromAccount, toAccount, amount, type, status, remark);
    m_transactions.push_back(tx);
    FileUtils::appendLine("transactions.txt", tx.serialize());  // 实时追加写入
}

// 按账号查询交易记录
std::vector<Transaction> TransactionManager::queryByAccount(const std::string& accountNo) {
    std::vector<Transaction> result;
    for (const auto& tx : m_transactions) {
        if (tx.getFromAccount() == accountNo || tx.getToAccount() == accountNo) {
            result.push_back(tx);
        }
    }
    return result;
}

// 按交易类型查询
std::vector<Transaction> TransactionManager::queryByType(int type) {
    std::vector<Transaction> result;
    for (const auto& tx : m_transactions) {
        if (tx.getType() == type) {
            result.push_back(tx);
        }
    }
    return result;
}

const std::vector<Transaction>& TransactionManager::getAllTransactions() const {
    return m_transactions;
}

// 从文件加载交易记录
void TransactionManager::loadFromFile() {
    auto lines = FileUtils::readLines("transactions.txt");
    for (const auto& line : lines) {
        try {
            Transaction tx = Transaction::deserialize(line);
            m_transactions.push_back(tx);
            // 更新序号
            int seq = std::stoi(tx.getTransactionId().substr(10));
            if (seq >= m_nextSeq) m_nextSeq = seq + 1;
        } catch (...) {
            // 跳过格式错误的行
        }
    }
}

// 全量保存（一般不需要，因为recordTransaction已经实时追加）
void TransactionManager::saveToFile() {
    std::vector<std::string> lines;
    for (const auto& tx : m_transactions) {
        lines.push_back(tx.serialize());
    }
    FileUtils::writeLines("transactions.txt", lines);
}
