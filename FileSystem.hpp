#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <string>
#include "Node.hpp"

class FileSystem
{
private:
    Node *root;
    Node *current;

    Node *findHelper(std::string name, Node *node);
    void removeHelper(Node *node);
    Node *copyHelper(Node *from);

public:
    FileSystem();
    std::string getCurrentDirectory();
    bool makeDirectoryOrFile(std::string name, std::string type);
    std::string listAllFiles();
    Node *find(std::string name);
    std::string getPath(Node *node);
    bool changeDirectory(std::string name);
    bool rename(std::string from, std::string to);
    Node *searchCurrentDirectory(std::string name);
    bool removeNode(std::string name);
    bool copy(std::string from, std::string to);
    bool addDorF(Node *newNode);
};

#endif