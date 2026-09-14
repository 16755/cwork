#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>
#include <vector>

// ============================================================
// 【成员C 负责】文件读写工具类
// 作用：封装通用的文件读写操作，供三个Manager统一调用
// 所有数据文件都放在 data/ 目录下，用逗号分隔字段
// ============================================================
class FileUtils {
public:
    // 读取文件全部内容，按行返回字符串数组
    // 参数：filename - 相对于 data/ 目录的文件名
    // 返回：每一行内容组成的vector
    static std::vector<std::string> readLines(const std::string& filename);

    // 将字符串数组按行写入文件（覆盖模式）
    // 参数：filename - 文件名，lines - 要写入的行内容
    static bool writeLines(const std::string& filename, const std::vector<std::string>& lines);

    // 追加一行到文件末尾
    static bool appendLine(const std::string& filename, const std::string& line);

    // 按逗号分割一行字符串，返回字段数组
    // 例如 "张三,123456,1" 分割为 ["张三", "123456", "1"]
    static std::vector<std::string> splitLine(const std::string& line, char delimiter = ',');

    // 检查data目录是否存在，不存在则创建
    static void ensureDataDir();
};

#endif
