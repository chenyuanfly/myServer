#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 辅助结构体，用于存储解析出的每个部分的元数据和数据
struct FormDataPart {
    std::string headers; // 部分的头部信息
    std::string data;    // 部分的数据
};

// 解析multipart/form-data中的单个数据块
// 参数：
// - data: 请求体数据
// - boundary: 边界字符串
// 返回值：包含头部和数据的向量
std::vector<FormDataPart> parseMultipartData(const std::string& data, const std::string& boundary) {
    std::vector<FormDataPart> parts;
    std::string delimiter = "--" + boundary;
    size_t pos = 0;
    size_t nextPos;
    std::string partData;

    while ((pos = data.find(delimiter, pos)) != std::string::npos) {
        // 找到边界，提取部分数据
        nextPos = data.find(delimiter, pos + delimiter.length() + 2); // +2 为了跳过CRLF
        if (nextPos == std::string::npos) {
            break;
        }

        partData = data.substr(pos + delimiter.leng
