th() + 2, nextPos - pos - delimiter.length() - 2);
        std::string partHeaders = partData.substr(0, partData.find("\r\n\r\n"));
        std::string partContent = partData.substr(partHeaders.length() + 4); // +4 为了跳过"\r\n\r\n"

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
 
