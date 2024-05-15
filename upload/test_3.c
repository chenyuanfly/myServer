 delimiter = "--" + boundary;
    size_t pos = 0;
    size_t nextPos;
    std::string partData;

    while ((pos = data.find(delimiter, pos)) != std::string::npos) {
        // 找到边界，提取部分数据
        nextPos = data.find(delimiter, pos + delimiter.length() + 2); // +2 为了跳过CRLF
        if (nextPos == std::string::npos) {
            break;
        }

        partData = data.substr(pos + delimiter.length() + 2, nextPos - pos - delimiter.length() - 2);
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
                              "Content-Disposition: f
