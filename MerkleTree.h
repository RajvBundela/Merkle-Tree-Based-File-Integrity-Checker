#ifndef MERKLETREE_H
#define MERKLETREE_H

#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <future>

class MerkleTree {
private:
    std::vector<std::string> leafHashes;  // Leaf level hashes (chunk hashes)
    std::vector<std::vector<std::string>> levels;  // 2D vector to store Merkle tree levels
    std::string rootHash;  // Final root hash
    mutable std::mutex treeMutex;  // Mutex for thread safety when updating tree

    // Helper function to hash data (SHA256)
    std::string hashData(const std::string& data);

    // Function to hash a pair of hashes
    std::string hashPair(const std::string& hash1, const std::string& hash2);

    // Function to verify data integrity by rebuilding the tree
    bool verifyDataIntegrity(const std::vector<std::string>& chunkHashes);

public:
    // Constructor
    MerkleTree();

    // Function to build the Merkle tree from leaf hashes
    void buildHashTree();

    // Function to add leaf hashes (file chunk hashes)
    void addLeafHashes(const std::vector<std::string>& chunkHashes);

    // Function to print the root hash (builds the tree and sets the root)
    void printRootHash();

    // Function to build the tree and set the root hash based on the provided chunk hashes
    void buildTreeAndSetRoot(const std::vector<std::string>& chunkHashes);

    // Get the Merkle root hash
    std::string getRootHash() const;
};

#endif // MERKLETREE_H
