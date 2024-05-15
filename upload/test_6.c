partData.substr(partHeaders.length() + 4); // +4 为了跳过"\r\n\r\n"

        FormDataPart part;
        part.headers = partHeaders;
        part.data = partContent;
        parts.push_back(part);

        pos = nextPos;
    }

    return parts;
}

int main() {
    // 示例请求体数据，通常从HTTP请求中获取
    std::string requestBody = "------Boundary\r\n"
                              "Content-Disposition: form-data; name=\"field1\"\r\n"
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
