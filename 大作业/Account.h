#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

// ============================================================
// 【成员A 负责】账户基类
// 继承体系：Account → SavingsAccount / CreditAccount / FixedDepositAccount
// 这是整个账户体系的根类，withdraw()和settleInterest()是纯虚函数
// 不同账户类型重写这两个方法，体现多态
// ============================================================
class Account {
protected:
    std::string m_accountNo;    // 账号（10位数字，系统生成）
    std::string m_ownerName;    // 户名
    std::string m_idCard;       // 身份证号
    std::string m_phone;        // 联系电话
    double m_balance;           // 账户余额
    std::string m_createTime;   // 开户时间
    int m_status;               // 状态：0-正常 1-冻结 2-销户
    std::string m_ownerUsername; // 所属用户的用户名（关联User）

public:
    // 构造函数
    Account(std::string accountNo, std::string ownerName, std::string idCard,
            std::string phone, double balance, std::string ownerUsername,
            std::string createTime = "", int status = 0);
    virtual ~Account();  // 虚析构函数

    // ===== 纯虚函数：派生类必须重写，体现多态 =====
    // 取款：不同账户类型规则不同（活期直接取、信用卡可透支、定期有到期限制）
    virtual bool withdraw(double amount) = 0;
    // 结息：不同账户类型计息方式不同
    virtual void settleInterest() = 0;
    // 获取账户类型名称
    virtual std::string getAccountType() const = 0;

    // ===== 通用方法（所有账户类型共用）=====
    void deposit(double amount);           // 存款（所有账户规则相同）
    bool isFrozen() const;                 // 是否冻结
    void freeze();                         // 冻结账户
    void unfreeze();                       // 解冻账户
    void closeAccount();                   // 销户

    // ===== Getter / Setter =====
    std::string getAccountNo() const;
    std::string getOwnerName() const;
    std::string getIdCard() const;
    std::string getPhone() const;
    double getBalance() const;
    std::string getCreateTime() const;
    int getStatus() const;
    std::string getOwnerUsername() const;
    std::string getStatusText() const;  // 返回状态文字描述
    void setPhone(const std::string& phone);
};

#endif
