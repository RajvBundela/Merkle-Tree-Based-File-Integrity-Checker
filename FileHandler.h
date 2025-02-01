#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <filesystem>
#include <future>

namespace fs = std::filesystem;

class FileHandler {
private:
    std::string directoryPath;
    size_t chunkSize;
    std::mutex fileMutex;  // Mutex for thread safety during file operations

    // Helper function to hash data (SHA256)
    std::string hashData(const std::string& data);

    // Hash a single chunk of data from a file
    std::string hashFileChunk(const std::string& filePath, size_t offset, size_t length);

    // Read and hash the entire file in chunks using multiple threads
    std::vector<std::string> hashChunks(const std::string& filePath);

public:
    // Constructor to set default chunk size (1MB)
    FileHandler();

    // Set the directory path to scan for files
    void setDirectoryPath(const std::string& path);

    // List all files in the directory and subdirectories
    std::vector<std::string> listFiles();

    // Get the file sizes of a list of files
    std::vector<std::pair<std::string, size_t>> getFileSizes(const std::vector<std::string>& files);

    // Hash all chunks of a list of files
    std::vector<std::string> hashAllFiles(const std::vector<std::string>& files);

    // Optional: Method to split a file into chunks based on the chunk size
    std::vector<std::string> splitFileIntoChunks(const std::string& filePath);
};

#endif // FILEHANDLER_H
