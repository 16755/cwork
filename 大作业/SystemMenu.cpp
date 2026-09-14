#include "SystemMenu.h"
#include "UserManager.h"
#include "AccountManager.h"
#include "TransactionManager.h"
#include "Customer.h"
#include "BankTeller.h"
#include "Admin.h"
#include <iostream>
#include <limits>

// ============================================================
// 【成员C 负责】系统菜单实现
// 这是整合三个子系统的核心文件
// ============================================================

SystemMenu::SystemMenu() : m_running(true) {}

SystemMenu::~SystemMenu() {}

// 系统启动：加载所有数据
void SystemMenu::start() {
    std::cout << "========================================" << std::endl;
    std::cout << "   银行综合账户管理系统 v1.0" << std::endl;
    std::cout << "========================================" << std::endl;

    // 加载数据（三个Manager分别加载自己的数据文件）
    UserManager::getInstance()->loadFromFile();
    AccountManager::getInstance()->loadFromFile();
    TransactionManager::getInstance()->loadFromFile();

    std::cout << "[系统] 数据加载完成" << std::endl;

    // 如果没有任何用户，创建默认管理员
    if (UserManager::getInstance()->getAllUsers().empty()) {
        UserManager::getInstance()->registerEmployee(
            "admin", "admin123", 3, "EMP001", "总行", "系统管理员");
        std::cout << "[系统] 已创建默认管理员账号: admin / admin123" << std::endl;
    }

    while (m_running) {
        showMainMenu();
    }
}

// 显示主菜单（登录/注册）
void SystemMenu::showMainMenu() {
    std::cout << "\n========== 欢迎使用银行系统 ==========" << std::endl;
    std::cout << "  1. 用户登录" << std::endl;
    std::cout << "  2. 客户注册" << std::endl;
    std::cout << "  0. 退出系统" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "请选择: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1: handleLogin(); break;
        case 2: handleRegister(); break;
        case 0: shutdown(); break;
        default: std::cout << "无效选择，请重新输入！" << std::endl;
    }
}

// 客户注册
void SystemMenu::handleRegister() {
    std::string username, password, realName, idCard, phone;
    std::cout << "\n--- 客户注册 ---" << std::endl;
    std::cout << "用户名: "; std::cin >> username;
    std::cout << "密码: "; std::cin >> password;
    std::cout << "真实姓名: "; std::cin >> realName;
    std::cout << "身份证号: "; std::cin >> idCard;
    std::cout << "手机号: "; std::cin >> phone;

    if (UserManager::getInstance()->registerCustomer(username, password, realName, idCard, phone)) {
        std::cout << "[成功] 注册成功，请登录！" << std::endl;
    } else {
        std::cout << "[失败] 用户名已存在！" << std::endl;
    }
}

// 用户登录
void SystemMenu::handleLogin() {
    std::string username, password;
    std::cout << "\n--- 用户登录 ---" << std::endl;
    std::cout << "用户名: "; std::cin >> username;
    std::cout << "密码: "; std::cin >> password;

    if (UserManager::getInstance()->login(username, password)) {
        User* user = UserManager::getInstance()->getCurrentUser();
        std::cout << "[成功] 登录成功！欢迎 " << user->getUsername()
                  << "（" << user->getRoleName() << "）" << std::endl;

        // 根据角色跳转不同菜单（多态：不同角色showMenu()不同）
        int role = user->getRole();
        if (role == 1) handleCustomerMenu();
        else if (role == 2) handleBankTellerMenu();
        else if (role == 3) handleAdminMenu();
    } else {
        std::cout << "[失败] 用户名或密码错误！" << std::endl;
    }
}

// ===== 客户菜单处理 =====
void SystemMenu::handleCustomerMenu() {
    Customer* customer = dynamic_cast<Customer*>(UserManager::getInstance()->getCurrentUser());
    if (!customer) return;

    while (true) {
        customer->showMenu();  // 多态调用客户菜单
        std::cout << "请选择: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: showMyAccounts(); break;
            case 2: doDeposit(); break;
            case 3: doWithdraw(); break;
            case 4: doTransfer(); break;
            case 5: {
                auto accounts = AccountManager::getInstance()->findAccountsByUsername(customer->getUsername());
                if (!accounts.empty()) {
                    showTransactionHistory(accounts[0]->getAccountNo());
                } else {
                    std::cout << "您还没有账户！" << std::endl;
                }
                break;
            }
            case 6: changePassword(); break;
            case 0:
                UserManager::getInstance()->logout();
                std::cout << "已退出登录" << std::endl;
                return;
            default: std::cout << "无效选择！" << std::endl;
        }
    }
}

// ===== 柜员菜单处理 =====
void SystemMenu::handleBankTellerMenu() {
    BankTeller* teller = dynamic_cast<BankTeller*>(UserManager::getInstance()->getCurrentUser());
    if (!teller) return;

    while (true) {
        teller->showMenu();  // 多态调用柜员菜单
        std::cout << "请选择: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                // 开户
                std::string ownerName, idCard, phone, ownerUsername;
                int type;
                double initialDeposit;
                std::cout << "户名: "; std::cin >> ownerName;
                std::cout << "身份证: "; std::cin >> idCard;
                std::cout << "电话: "; std::cin >> phone;
                std::cout << "所属用户名: "; std::cin >> ownerUsername;
                std::cout << "账户类型(1-活期 2-信用卡 3-定期): "; std::cin >> type;
                std::cout << "初始存款: "; std::cin >> initialDeposit;
                std::string accNo = AccountManager::getInstance()->openAccount(
                    type, ownerName, idCard, phone, initialDeposit, ownerUsername);
                if (!accNo.empty()) {
                    std::cout << "[成功] 开户成功，账号: " << accNo << std::endl;
                } else {
                    std::cout << "[失败] 开户失败！" << std::endl;
                }
                break;
            }
            case 2: doDeposit(); break;
            case 3: doWithdraw(); break;
            case 4: doTransfer(); break;
            case 5: {
                std::string accNo;
                std::cout << "请输入账号: "; std::cin >> accNo;
                showAccountInfo(accNo);
                break;
            }
            case 6: {
                std::string accNo;
                int op;
                std::cout << "请输入账号: "; std::cin >> accNo;
                std::cout << "操作(1-冻结 2-解冻): "; std::cin >> op;
                if (op == 1) {
                    AccountManager::getInstance()->freezeAccount(accNo);
                    std::cout << "账户已冻结" << std::endl;
                } else {
                    AccountManager::getInstance()->unfreezeAccount(accNo);
                    std::cout << "账户已解冻" << std::endl;
                }
                break;
            }
            case 7: changePassword(); break;
            case 0:
                UserManager::getInstance()->logout();
                std::cout << "已退出登录" << std::endl;
                return;
            default: std::cout << "无效选择！" << std::endl;
        }
    }
}

// ===== 管理员菜单处理 =====
void SystemMenu::handleAdminMenu() {
    Admin* admin = dynamic_cast<Admin*>(UserManager::getInstance()->getCurrentUser());
    if (!admin) return;

    while (true) {
        admin->showMenu();  // 多态调用管理员菜单
        std::cout << "请选择: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                // 用户管理
                std::cout << "\n--- 用户列表 ---" << std::endl;
                for (auto user : UserManager::getInstance()->getAllUsers()) {
                    std::cout << "  " << user->getUsername() << " ("
                              << user->getRoleName() << ") 注册于 "
                              << user->getCreateTime() << std::endl;
                }
                std::cout << "\n输入要删除的用户名(0返回): ";
                std::string username;
                std::cin >> username;
                if (username != "0") {
                    if (UserManager::getInstance()->deleteUser(username)) {
                        std::cout << "用户已删除" << std::endl;
                    } else {
                        std::cout << "删除失败" << std::endl;
                    }
                }
                break;
            }
            case 2: {
                // 账户管理
                std::cout << "\n--- 所有账户 ---" << std::endl;
                for (auto acc : AccountManager::getInstance()->getAllAccounts()) {
                    std::cout << "  " << acc->getAccountNo() << " | "
                              << acc->getOwnerName() << " | "
                              << acc->getAccountType() << " | 余额:"
                              << acc->getBalance() << " | "
                              << acc->getStatusText() << std::endl;
                }
                break;
            }
            case 3: {
                // 查看所有交易流水
                std::cout << "\n--- 交易流水 ---" << std::endl;
                for (const auto& tx : TransactionManager::getInstance()->getAllTransactions()) {
                    std::cout << "  " << tx.getTime() << " | "
                              << tx.getTypeText() << " | "
                              << tx.getAmount() << "元 | "
                              << tx.getStatusText() << std::endl;
                }
                break;
            }
            case 4:
                std::cout << "[提示] 利率设置功能开发中..." << std::endl;
                break;
            case 5: changePassword(); break;
            case 0:
                UserManager::getInstance()->logout();
                std::cout << "已退出登录" << std::endl;
                return;
            default: std::cout << "无效选择！" << std::endl;
        }
    }
}

// ===== 通用业务功能 =====

// 存款
void SystemMenu::doDeposit() {
    std::string accNo;
    double amount;
    std::cout << "\n--- 存款 ---" << std::endl;
    std::cout << "账号: "; std::cin >> accNo;
    std::cout << "金额: "; std::cin >> amount;

    Account* acc = AccountManager::getInstance()->findAccount(accNo);
    if (!acc) {
        std::cout << "[失败] 账户不存在！" << std::endl;
        return;
    }
    if (acc->getStatus() != 0) {
        std::cout << "[失败] 账户状态异常！" << std::endl;
        return;
    }
    acc->deposit(amount);
    AccountManager::getInstance()->saveToFile();
    TransactionManager::getInstance()->recordTransaction(
        "", accNo, amount, 1, 0, "柜台存款");
    std::cout << "[成功] 存款成功！当前余额: " << acc->getBalance() << std::endl;
}

// 取款（调用账户的多态withdraw方法）
void SystemMenu::doWithdraw() {
    std::string accNo;
    double amount;
    std::cout << "\n--- 取款 ---" << std::endl;
    std::cout << "账号: "; std::cin >> accNo;
    std::cout << "金额: "; std::cin >> amount;

    Account* acc = AccountManager::getInstance()->findAccount(accNo);
    if (!acc) {
        std::cout << "[失败] 账户不存在！" << std::endl;
        return;
    }
    // 多态调用：不同账户类型执行不同取款规则
    if (acc->withdraw(amount)) {
        AccountManager::getInstance()->saveToFile();
        TransactionManager::getInstance()->recordTransaction(
            accNo, "", amount, 2, 0, "柜台取款");
        std::cout << "[成功] 取款成功！当前余额: " << acc->getBalance() << std::endl;
    } else {
        TransactionManager::getInstance()->recordTransaction(
            accNo, "", amount, 2, 1, "取款失败");
        std::cout << "[失败] 取款失败（余额不足或账户异常）！" << std::endl;
    }
}

// 转账
void SystemMenu::doTransfer() {
    std::string fromAcc, toAcc;
    double amount;
    std::cout << "\n--- 转账 ---" << std::endl;
    std::cout << "付款账号: "; std::cin >> fromAcc;
    std::cout << "收款账号: "; std::cin >> toAcc;
    std::cout << "转账金额: "; std::cin >> amount;

    Account* from = AccountManager::getInstance()->findAccount(fromAcc);
    Account* to = AccountManager::getInstance()->findAccount(toAcc);
    if (!from || !to) {
        std::cout << "[失败] 账户不存在！" << std::endl;
        return;
    }
    // 多态：付款方执行取款（不同账户规则不同）
    if (from->withdraw(amount)) {
        to->deposit(amount);
        AccountManager::getInstance()->saveToFile();
        TransactionManager::getInstance()->recordTransaction(
            fromAcc, toAcc, amount, 3, 0, "转账");
        std::cout << "[成功] 转账成功！" << std::endl;
    } else {
        TransactionManager::getInstance()->recordTransaction(
            fromAcc, toAcc, amount, 3, 1, "转账失败");
        std::cout << "[失败] 转账失败（余额不足）！" << std::endl;
    }
}

// 显示账户信息
void SystemMenu::showAccountInfo(const std::string& accountNo) {
    Account* acc = AccountManager::getInstance()->findAccount(accountNo);
    if (!acc) {
        std::cout << "账户不存在！" << std::endl;
        return;
    }
    std::cout << "\n--- 账户信息 ---" << std::endl;
    std::cout << "  账号: " << acc->getAccountNo() << std::endl;
    std::cout << "  户名: " << acc->getOwnerName() << std::endl;
    std::cout << "  类型: " << acc->getAccountType() << std::endl;
    std::cout << "  余额: " << acc->getBalance() << std::endl;
    std::cout << "  状态: " << acc->getStatusText() << std::endl;
    std::cout << "  开户时间: " << acc->getCreateTime() << std::endl;
}

// 客户查看自己的所有账户
void SystemMenu::showMyAccounts() {
    User* user = UserManager::getInstance()->getCurrentUser();
    auto accounts = AccountManager::getInstance()->findAccountsByUsername(user->getUsername());
    if (accounts.empty()) {
        std::cout << "您还没有账户，请联系柜员开户！" << std::endl;
        return;
    }
    std::cout << "\n--- 我的账户 ---" << std::endl;
    for (auto acc : accounts) {
        std::cout << "  账号: " << acc->getAccountNo()
                  << " | 类型: " << acc->getAccountType()
                  << " | 余额: " << acc->getBalance()
                  << " | " << acc->getStatusText() << std::endl;
    }
}

// 显示交易记录
void SystemMenu::showTransactionHistory(const std::string& accountNo) {
    auto records = TransactionManager::getInstance()->queryByAccount(accountNo);
    if (records.empty()) {
        std::cout << "暂无交易记录" << std::endl;
        return;
    }
    std::cout << "\n--- 交易记录 ---" << std::endl;
    for (const auto& tx : records) {
        std::cout << "  " << tx.getTime() << " | "
                  << tx.getTypeText() << " | "
                  << tx.getAmount() << "元 | "
                  << tx.getStatusText() << std::endl;
    }
}

// 修改密码
void SystemMenu::changePassword() {
    User* user = UserManager::getInstance()->getCurrentUser();
    std::string oldPwd, newPwd;
    std::cout << "\n--- 修改密码 ---" << std::endl;
    std::cout << "原密码: "; std::cin >> oldPwd;
    std::cout << "新密码: "; std::cin >> newPwd;
    if (user->changePassword(oldPwd, newPwd)) {
        UserManager::getInstance()->saveToFile();
        std::cout << "[成功] 密码修改成功！" << std::endl;
    } else {
        std::cout << "[失败] 原密码错误！" << std::endl;
    }
}

// 系统退出
void SystemMenu::shutdown() {
    std::cout << "\n感谢使用银行综合账户管理系统，再见！" << std::endl;
    m_running = false;
}
