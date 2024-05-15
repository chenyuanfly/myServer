                             "------Boundary--";

    // 示例边界字符串，通常从Content-Type头部中解析得到
    std::string boundary = "----Boundary";

    std::vector<FormDataPart> parts = parseMultipartData(requestBody, boundary);

    // 打印解析结果
    for (const auto& part : parts) {
        std::cout << "Headers:\n" << part.headers << "\nData:\n" << part.data << std::endl;
    }

    return 0;
}

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
    std::string
