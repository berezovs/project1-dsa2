#include <string>
#include "FileSystem.hpp"
#include "Node.hpp"

//C-TOR; initializes the filesystem by creating a root directory and sets the current directory to the root directory
FileSystem::FileSystem()
{
    this->root = new Node(nullptr, nullptr, "root", "D");
    this->current = root;
}

//this function traverses the file tree from the current directory all the way up to the root and builds a string which
//represents the path to the current directory
std::string FileSystem::printCurrentDirectory()
{
    std::string stringToReturn = "";
    Node *currentDirectory = current;

    while (currentDirectory->getParent() != nullptr)
    {
        stringToReturn.insert(0, "/" + currentDirectory->getName());
        currentDirectory = currentDirectory->getParent();
    }
    stringToReturn.insert(0, "/root");
    return stringToReturn;
}
