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
std::string printCurrentDirectory();
bool makeDirectoryOrFile(std::string name, std::string type);
std::string listAllFiles();

};

#endif