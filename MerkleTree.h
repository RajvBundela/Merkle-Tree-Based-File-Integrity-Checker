#ifndef MERKLETREE_H
#define MERKLETREE_H

#include <iostream>
#include <vector>
#include <string>

class MerkleTree {
private:
    std::vector<std::string> leafHashes;
    std::vector<std::vector<std::string>> levels;
    std::string rootHash;

public:
    void addLeafHashes(const std::vector<std::string>& chunkHashes);
    void buildHashTree();
    std::string hashPair(const std::string& hash1, const std::string& hash2);
    std::string getRootHash() const;
    bool verifyDataIntegrity(const std::vector<std::string>& chunkHashes);
};

#endif
