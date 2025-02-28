#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <filesystem>
#include <fstream>
#include <openssl/sha.h>  // For hashing (using OpenSSL SHA256)
#include <future>  // For async operations

namespace fs = std::filesystem;
using namespace std;

class FileHandler {
private:
    string directoryPath;
    size_t chunkSize;  // Size of chunks for splitting files
    mutex fileMutex;  // Mutex for thread safety when working with file-related data

    // Helper function to hash data (SHA256)
    string hashData(const string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, data.c_str(), data.size());
        SHA256_Final(hash, &sha256);
        return string(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH);
    }

    // Hash a single chunk of data from a file
    string hashFileChunk(const string& filePath, size_t offset, size_t length) {
        ifstream file(filePath, ios::binary);
        file.seekg(offset, ios::beg);
        string buffer(length, '\0');
        file.read(&buffer[0], length);
        if (file.fail()) {
            cerr << "Error reading file: " << filePath << endl;
            return "";
        }
        return hashData(buffer);
    }

    // Read and hash the entire file in chunks using multiple threads
    vector<string> hashChunks(const string& filePath) {
        vector<string> chunkHashes;
        ifstream file(filePath, ios::binary | ios::ate); // Open file in binary and move to the end
        size_t fileSize = file.tellg();
        size_t chunkCount = (fileSize / chunkSize) + (fileSize % chunkSize != 0);  // Handle remaining chunk

        vector<future<string>> futures;
        for (size_t i = 0; i < chunkCount; ++i) {
            size_t offset = i * chunkSize;
            size_t length = (i == chunkCount - 1) ? fileSize - offset : chunkSize;

            // Launch each chunk hash calculation asynchronously
            futures.push_back(async(launch::async, &FileHandler::hashFileChunk, this, filePath, offset, length));
        }

        // Collect results from all threads
        for (auto& fut : futures) {
            string chunkHash = fut.get();
            if (!chunkHash.empty()) {
                chunkHashes.push_back(chunkHash);
            }
        }

        return chunkHashes;
    }

public:
    FileHandler() : chunkSize(1024 * 1024) {}  // Default chunk size of 1MB

    void setDirectoryPath(const string& path) {
        directoryPath = path;
    }

    vector<string> listFiles() {
        vector<string> files;
        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry.status())) { // checks if entry is directory or file
                files.push_back(entry.path().string());
            }
        }
        return files;
    }

    vector<pair<string, size_t>> getFileSizes(const vector<string>& files) {
        vector<pair<string, size_t>> fileSizes;
        vector<future<void>> futures;

        for (const auto& file : files) {
            futures.push_back(async(launch::async, [&file, &fileSizes]() {
                ifstream fileStream(file, ios::ate);  // Open file at end to get size
                size_t size = fileStream.tellg();
                fileSizes.push_back({file, size});
            }));
        }

        // Wait for all threads to finish
        for (auto& fut : futures) {
            fut.get();
        }

        return fileSizes;
    }

    // Method to hash all files
    vector<string> hashAllFiles(const vector<string>& files) {
        vector<string> allHashes;
        vector<future<vector<string>>> futures;

        for (const auto& file : files) {
            // Launch each file's chunk hashing in parallel
            futures.push_back(async(launch::async, &FileHandler::hashChunks, this, file));
        }

        // Collect hashes from all files
        for (auto& fut : futures) {
            vector<string> fileHashes = fut.get(); // blocks till this thread is completed
            allHashes.insert(allHashes.end(), fileHashes.begin(), fileHashes.end());
        }

        return allHashes;
    }

    // Optional: Method to split a file into chunks based on the chunk size
    vector<string> splitFileIntoChunks(const string& filePath) {
        vector<string> chunkHashes;
        ifstream file(filePath, ios::binary);
        string buffer(chunkSize, '\0');

        while (file.read(&buffer[0], chunkSize)) {
            chunkHashes.push_back(hashData(buffer));
        }

        // For the last chunk (if it's smaller than chunkSize)
        if (file.gcount() > 0) {
            buffer.resize(file.gcount());
            chunkHashes.push_back(hashData(buffer));
        }

        return chunkHashes;
    }
};
