#include "FileHandler.h"
#include "MerkleTree.h"
using namespace std;

int main() {
    // Step 1: Create FileHandler object
    FileHandler fileHandler;
    fileHandler.setDirectoryPath("");

    // Step 2: Get list of files
    vector<string> files = fileHandler.listFiles();

    // Step 3: Generate hashes for each file
    vector<string> fileHashes = fileHandler.hashAllFiles(files);

    // Step 4: Create MerkleTree object
    MerkleTree merkleTree;

    // Step 5: Add leaf hashes (file hashes)
    merkleTree.addLeafHashes(fileHashes);

    // Step 6: Build the Merkle Tree
    merkleTree.buildHashTree();

    // Step 7: Retrieve and display the root hash
    string rootHash = merkleTree.getRootHash();
    cout << "Merkle Root Hash: " << rootHash << endl;

    return 0;
}
