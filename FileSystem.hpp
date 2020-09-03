#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <string>
#include "Node.hpp"

class FileSystem{
private:
Node *root;
Node *current;

public:
FileSystem();
void addFile(std::string name);
std::string getCurrentDirectory();
bool makeDirectoryOrFile(std::string name, std::string type);
std::string listAllFiles();
Node* find(std::string name);
Node* findHelper(std::string name, Node* node);
std::string getPath(Node* node);
bool changeDirectory(std::string name);
bool rename(std::string from, std::string to);
Node* searchCurrentDirectory(std::string name);
};

#endif