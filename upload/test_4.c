orm-data; name=\"field1\"\r\n"
                              "\r\n"
                              "Value1\r\n"
                              "------Boundary\r\n"
                              "Content-Disposition: form-data; name=\"file\"; filename=\"example.txt\"\r\n"
                              "Content-Type: text/plain\r\n"
                              "\r\n"
                              "File content goes here.\r\n"
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
struct Form
