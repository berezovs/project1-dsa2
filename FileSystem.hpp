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
void addDirectory(std::string name);
std::string printCurrentDirectory();

};

#endif