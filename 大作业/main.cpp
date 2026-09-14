// ============================================================
// 银行综合账户管理系统 - 程序入口
// 编译命令（MinGW/g++）:
//   g++ -std=c++17 *.cpp -o BankSystem.exe
// 运行:
//   BankSystem.exe
// ============================================================

#include "SystemMenu.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // 设置控制台代码页为 UTF-8，保证中文正常显示与输入
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    SystemMenu system;
    system.start();  // 启动系统（加载数据 -> 显示菜单 -> 处理交互）
    return 0;
}
//这是一个测试
