#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <vector>
#include <string>

class FileHandler {
private:
    std::string directoryPath;
    size_t chunkSize;

public:
    void setDirectoryPath(const std::string& path);
    std::vector<std::string> listFiles();
    std::vector<std::pair<std::string, size_t>> getFileSizes(const std::vector<std::string>& files);
    std::vector<std::string> splitFileIntoChunks(const std::string& filePath);
    std::vector<std::string> hashChunks(const std::string& filePath);
    std::vector<std::string> hashAllFiles(const std::vector<std::string>& files);
};

#endif
