#include<iostream>
#include<vector>
#include<string>
using namespace std;


class FileHandler{
    string directoryPath; //Path to the directory to scan.
    size_t chunkSize;     //Size of each chunk

    void setDirectoryPath(const string& path){
    /*
        Sets the path to the directory.
        Input: 
            -Directory path as a string.
    */
        directoryPath = path;
    }

    vector<string> listFiles(){
    /*
        Lists all files in the given directory recursively.
        Returns: A vector of file paths.
    */
    }

    vector<pair<string, size_t>> getFileSizes(const vector<string>& files){
    /*
        Reads the sizes of each file.
        Input: 
            -List of file paths
        Returns: A vector of pairs: <filePath, fileSize>.
    */
    }

    vector<string> splitFileIntoChunks(const string& filePath){
    /*
        Splits a file into chunks based on chunkSize.
        Input: 
            -File path.
        Returns: A vector of chunk hashes.
    */
    }

    vector<string> hashChunks(const string& filePath){
    /*
        Reads a file in chunks and hashes each chunk using a hashing function.
        Input: 
            -File path.
        Returns: A vector of chunk hashes.
    */
    }

    vector<string> hashAllFiles(const vector<string>& files){
    /*
        Calls hashChunks for all files in the directory.
        Input: 
            -List of file paths
        Returns: A vector of hashes for all files
    */
    }

};