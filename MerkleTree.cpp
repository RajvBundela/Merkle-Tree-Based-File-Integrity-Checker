#include<iostream>
#include<vector>
#include<string>
using namespace std;

class MerkleTree{

    vector<string> leafHashes; // Store the hashes of chunks.
    vector<vector<string>> levels; // A 2D vector representing levels of the Merkle tree.
    string rootHash; // Stores the final Merkle root.

    void addLeafHashes(const vector<string>& chunkHashes){
    /*
        Adds the hash of chunks to the leaf level.
        Input: 
            -A list of chunk hashes (leaf nodes).
    */
    }

    void buildHashTree(){
    /*
        Constructs the Merkle tree from the leafHashes.
        Calculates hashes at each level until the root is computed.
    */
    }

    string hashPair(const string& hash1, const string& hash2){
    /*
        Combines two hashes and calculates the hash of their concatenation.
        Uses SHA256 or any hashing function.
        Input: 
            -hash1: hash of one or more chunks
            -hash2: hash of one or more chunks
        Returns: Hash of concatenated inputs.
    */
    }

    string getRootHash() const{
    /*
        Useful for verifying the integrity of the tree.
        Returns: Root hash of merkle tree
    */
    }

    bool verifyDataIntegrity(const vector<string>& chunkHashes){
    /*
        Recomputes the tree from chunkHashes and verifies that 
        the new root hash matches the original.
        Input: 
            -New chunk hashes.
        Returns: true if the integrity is intact, else false.
    */
    }

};