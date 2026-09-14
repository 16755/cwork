#include "FileUtils.h"
#include <filesystem>
#include <fstream>
#include <sstream>

// ============================================================
// 【成员C 负责】文件工具类实现
// ============================================================

std::vector<std::string> FileUtils::readLines(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file("data/" + filename);
    if (!file.is_open()) return lines;  // 文件不存在时返回空
    std::string line;
    bool isFirstLine = true;
    while (std::getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false;
            // 去掉 UTF-8 BOM（本系统写入文件时添加，避免干扰第一个字段）
            if (line.size() >= 3 &&
                static_cast<unsigned char>(line[0]) == 0xEF &&
                static_cast<unsigned char>(line[1]) == 0xBB &&
                static_cast<unsigned char>(line[2]) == 0xBF) {
                line.erase(0, 3);
            }
        }
        if (!line.empty()) lines.push_back(line);
    }
    file.close();
    return lines;
}

bool FileUtils::writeLines(const std::string& filename, const std::vector<std::string>& lines) {
    ensureDataDir();
    std::ofstream file("data/" + filename, std::ios::trunc);  // 覆盖写入
    if (!file.is_open()) return false;
    file.write("\xEF\xBB\xBF", 3);  // 写入 UTF-8 BOM，便于记事本/Excel 识别中文
    for (const auto& line : lines) {
        file << line << "\n";
    }
    file.close();
    return true;
}

bool FileUtils::appendLine(const std::string& filename, const std::string& line) {
    ensureDataDir();
    // 文件不存在时，首次写入需添加 UTF-8 BOM
    std::ifstream probe("data/" + filename);
    bool fileExists = probe.good();
    probe.close();

    std::ofstream file("data/" + filename, std::ios::app);  // 追加写入
    if (!file.is_open()) return false;
    if (!fileExists) {
        file.write("\xEF\xBB\xBF", 3);
    }
    file << line << "\n";
    file.close();
    return true;
}

std::vector<std::string> FileUtils::splitLine(const std::string& line, char delimiter) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, delimiter)) {
        fields.push_back(field);
    }
    return fields;
}

void FileUtils::ensureDataDir() {
    std::error_code error;
    std::filesystem::create_directories("data", error);
}
