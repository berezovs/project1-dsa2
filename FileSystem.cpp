#include <string>
#include <iostream>
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

//This function will create a file/directory in the current directory after ensuring that no files or directories with the specified name already exist
bool FileSystem::makeDirectoryOrFile(std::string name, std::string type)
{
    Node *directory = new Node(nullptr, current, name, type);

    if (!current->getChild())
    {
        current->addChild(directory);
    }
    else
    {
        Node *child = current->getChild();
        while (child->getNext())
        {

            child = child->getNext();
        }
        child->setNext(directory);
    }
    return true;
}

//This function will return a string containing the names of all the files and directories in the current directory
std::string FileSystem::listAllFiles()
{
    std::string returnString = "";
    Node *file = current->getChild();

    while (file)
    {
        returnString += file->getFileType() + "\t" + file->getName() + "\n";
        file = file->getNext();
    }
    return returnString;
}

Node *FileSystem::find(std::string name)
{
    Node *node = root;

    return findHelper(name, node);
}

Node *FileSystem::findHelper(std::string name, Node *node)
{

    if (node)
    {
        if (node->getName() == name)
        {
            return node;
        }

        else if (node->getFileType() == "D")
        {
            if (node->getChild() != nullptr)
            {
                return findHelper(name, node->getChild());
            }
            else
            {
                return findHelper(name, node->getNext());
            }
        }
        else if (node->getFileType() == "F")
        {
            return findHelper(name, node->getNext());
        }
    }

    return nullptr;
}