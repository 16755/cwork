# 银行综合账户管理系统 - C++课程设计

本仓库可以在任意目录克隆和编辑：工程文件只使用相对路径，不依赖任何开发者的用户名、磁盘盘符或本机目录。

## 项目结构

```
BankSystem/
├── main.cpp                  # 程序入口
├── FileUtils.h/.cpp          # 【成员C】文件读写工具类
├── User.h/.cpp               # 【成员C】用户基类（继承根类）
├── Customer.h/.cpp           # 【成员C】客户类（继承User）
├── Employee.h/.cpp           # 【成员C】员工基类（继承User）
├── BankTeller.h/.cpp         # 【成员C】柜员类（继承Employee）
├── Admin.h/.cpp              # 【成员C】管理员类（继承Employee）
├── Account.h/.cpp            # 【成员A】账户基类（多态根类）
├── SavingsAccount.h/.cpp     # 【成员A】活期储蓄账户（继承Account）
├── CreditAccount.h/.cpp      # 【成员A】信用卡账户（继承Account）
├── FixedDepositAccount.h/.cpp # 【成员A】定期存款账户（继承Account）
├── Transaction.h/.cpp        # 【成员B】交易记录实体类
├── AccountManager.h/.cpp     # 【成员A】账户管理器（单例）
├── TransactionManager.h/.cpp # 【成员B】交易流水管理器（单例）
├── UserManager.h/.cpp        # 【成员C】用户管理器（单例）
├── SystemMenu.h/.cpp         # 【成员C】系统菜单与入口（整合三个子系统）
└── data/                     # 本机运行数据（自动创建，不提交到 Git）
    ├── users.txt             # 用户账号数据
    ├── accounts.txt          # 账户信息数据
    └── transactions.txt      # 交易流水数据
```

## 面向对象特性体现

### 1. 封装
- 所有类的数据成员设为 private/protected，通过 public 方法访问
- 每个类独立 .h + .cpp 文件，接口与实现分离

### 2. 继承（两层以上）
- 用户体系：User → Employee → BankTeller/Admin（3层）
- 账户体系：Account → SavingsAccount/CreditAccount/FixedDepositAccount（2层）

### 3. 多态
- 虚函数 `showMenu()`：不同角色登录显示不同菜单
- 纯虚函数 `withdraw()`：不同账户类型取款规则不同
- 纯虚函数 `settleInterest()`：不同账户类型计息方式不同
- 基类指针 `Account*` / `User*` 统一管理派生类对象

### 4. 设计模式
- 单例模式：三个 Manager 类全局唯一实例

## 编译运行

### 推荐：CMake（Windows / macOS / Linux）

在仓库根目录执行：

```bash
cmake -S . -B build
cmake --build build
```

运行生成的 `BankSystem`（Windows 下为 `BankSystem.exe`）。程序运行时请将工作目录设为 `大作业`，以便将本机数据保存到 `大作业/data/`。

### Visual Studio 2022

直接打开仓库根目录的 `大作业.sln`，选择 `Debug` 或 `Release` 配置后生成并运行。工程已引用项目内的相对路径；首次运行会自动创建 `data/`。

### MinGW / g++
```bash
cd 大作业
g++ -std=c++17 *.cpp -o BankSystem.exe
./BankSystem.exe
```

## 默认账号
- 管理员：admin / admin123（首次运行自动创建）

## 协作约定

- 提交 `.cpp`、`.h`、`.sln`、`.vcxproj`、`CMakeLists.txt` 与文档；不要提交 `.exe`、`x64/`、`.vs/`、`build/` 等生成文件。
- `data/` 中包含本机账号、密码和交易记录，已被 Git 忽略。若需要共享演示数据，请另建匿名的示例文件，切勿提交真实数据。
- 修改前先 `git pull`，修改后运行一次构建验证，再提交并推送。

## 作业要求对应
- [x] 类层次不少于两层（用户3层 + 账户2层）
- [x] 数据通过文件存储（三个txt文件持久化）
- [x] 用户账号管理（注册、登录、密码修改、权限控制）
- [x] 三人各负责一个子系统（账户/交易/用户安全）
- [x] 充分运用封装、继承、多态
