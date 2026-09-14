#ifndef SYSTEMMENU_H
#define SYSTEMMENU_H

#include <string>

// ============================================================
// 【成员C 负责】系统总菜单与入口
// 作用：整合账户管理、资金交易、用户安全三个子系统
// 负责登录注册、角色菜单跳转、业务功能调用
// 这是整个系统的交互层，调用三个Manager完成业务
// ============================================================
class SystemMenu {
private:
    bool m_running;  // 系统运行标志

    // ===== 各角色菜单处理 =====
    void handleCustomerMenu();   // 客户菜单处理
    void handleBankTellerMenu(); // 柜员菜单处理
    void handleAdminMenu();      // 管理员菜单处理

    // ===== 通用业务功能 =====
    void doDeposit();    // 存款
    void doWithdraw();   // 取款
    void doTransfer();   // 转账
    void showAccountInfo(const std::string& accountNo);  // 显示账户信息
    void showMyAccounts();  // 客户查看自己的账户
    void showTransactionHistory(const std::string& accountNo);  // 交易记录
    void changePassword();  // 修改密码

public:
    SystemMenu();
    ~SystemMenu();

    // 系统启动：加载数据 + 显示主菜单
    void start();
    // 显示登录/注册主菜单
    void showMainMenu();
    // 处理用户注册
    void handleRegister();
    // 处理用户登录
    void handleLogin();
    // 系统退出：保存数据
    void shutdown();
};

#endif
