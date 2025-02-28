#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <future>
#include <openssl/sha.h> // For hashing (using OpenSSL's SHA256 for example)

using namespace std;

class MerkleTree {
private:
    vector<string> leafHashes;              // Leaf level hashes (chunk hashes).
    vector<vector<string>> levels;          // 2D vector for Merkle tree levels.
    string rootHash;                        // Final root hash.
    mutable mutex treeMutex;                        // Mutex for thread safety during updates.

    // Helper: Hash data using SHA256
    string hashData(const string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, data.c_str(), data.size());
        SHA256_Final(hash, &sha256);
        return string(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH);
    }

    // Helper: Combine and hash two hashes
    string hashPair(const string& hash1, const string& hash2) {
        return hashData(hash1 + hash2);
    }

    // Helper: Add leaf-level hashes to the tree
    void addLeafHashes(const vector<string>& chunkHashes) {
        lock_guard<mutex> lock(treeMutex); // Thread-safe
        leafHashes = chunkHashes;
        levels.push_back(leafHashes);
    }

public:
    // Core: Build the tree using multithreading
    void buildHashTree() {
        lock_guard<mutex> lock(treeMutex); // Thread-safe

        if (leafHashes.empty()) {
            throw runtime_error("No leaf hashes provided to build the tree.");
        }

        vector<string> currentLevel = leafHashes;

        // Build tree level by level
        while (currentLevel.size() > 1) {
            vector<string> nextLevel;

            // Use futures to parallelize hash pair computation
            vector<future<string>> futures;
            for (size_t i = 0; i < currentLevel.size(); i += 2) {
                if (i + 1 < currentLevel.size()) {
                    // Parallel hash combining
                    futures.push_back(async(launch::async, &MerkleTree::hashPair, this, currentLevel[i], currentLevel[i + 1]));
                } else {
                    // Odd number of elements: carry the last one over directly
                    nextLevel.push_back(currentLevel[i]);
                }
            }

            // Collect results from futures
            for (auto& fut : futures) {
                nextLevel.push_back(fut.get());
            }

            // Move to the next level
            levels.push_back(nextLevel);
            currentLevel = move(nextLevel); // Use move for efficiency
        }

        // Final root hash
        rootHash = currentLevel.empty() ? "" : currentLevel[0];
    }

    // Constructor
    MerkleTree() : rootHash("") {}

    // Public: Build tree and set root hash
    void buildTreeAndSetRoot(const vector<string>& chunkHashes) {
        addLeafHashes(chunkHashes);
        buildHashTree();
    }

    // Public: Get the Merkle root hash
    string getRootHash() const {
        lock_guard<mutex> lock(treeMutex); // Thread-safe
        return rootHash;
    }

    // Public: Verify data integrity
    bool verifyDataIntegrity(const vector<string>& chunkHashes) {
        MerkleTree rebuiltTree;
        rebuiltTree.buildTreeAndSetRoot(chunkHashes);
        return rebuiltTree.getRootHash() == getRootHash();
    }

    // Public: Print the root hash
    void printRootHash() {
        lock_guard<mutex> lock(treeMutex); // Thread-safe
        if (rootHash.empty()) {
            cout << "Tree not built yet. Building now..." << endl;
            buildHashTree();
        }
        cout << "Merkle Root Hash: " << rootHash << endl;
    }
};
