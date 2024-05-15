

    std::vector<FormDataPart> parts = parseMultipartData(requestBody, boundary);

    // 打印解析结果
    for (const auto& part : parts) {
        std::cout << "Headers:\n" << part.headers << "\nData:\n" << part.data << std::endl;
    }

    return 0;
}

