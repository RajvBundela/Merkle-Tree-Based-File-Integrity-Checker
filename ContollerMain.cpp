#include "FileHandler.h"
#include "MerkleTree.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Step 1: Create FileHandler object
    FileHandler fileHandler;
    fileHandler.setDirectoryPath("path_to_your_directory");  // Set the path of the directory to scan

    // Step 2: Get list of files in the directory
    vector<string> files = fileHandler.listFiles();

    // Step 3: Generate hashes for each file (by hashing file chunks)
    vector<string> fileHashes = fileHandler.hashAllFiles(files);

    // Step 4: Create MerkleTree object
    MerkleTree merkleTree;

    // Step 5: Add leaf hashes (file hashes)
    merkleTree.addLeafHashes(fileHashes);

    // Step 6: Build the Merkle Tree from the leaf hashes
    merkleTree.buildHashTree();

    // Step 7: Retrieve and display the root hash of the Merkle tree
    string rootHash = merkleTree.getRootHash();
    cout << "Merkle Root Hash: " << rootHash << endl;

    return 0;
}
