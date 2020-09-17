#include <string>
#include <iostream>
#include "FileSystem.hpp"
#include "Node.hpp"

//C-TOR; initializes the filesystem by creating a root directory and sets the current directory to the root directory
FileSystem::FileSystem()
{
    this->root = new Node(nullptr, nullptr,nullptr, "root", "D");
    this->current = root;
}

//this function calls getPath() and returns a string representation of the current directory's path
std::string FileSystem::getCurrentDirectory()
{
    return this->getPath(current);
}

//takes a node as a parameter and returns a string representation of its path
std::string FileSystem::getPath(Node *node)
{
    if (!node)
        return "File/Directory doesn't exist.";

    std::string stringToReturn = "";

    while (node->getParent() != nullptr)
    {
        stringToReturn.insert(0, "/" + node->getName());
        node = node->getParent();
    }
    stringToReturn.insert(0, "/root");
    return stringToReturn;
}

//This function calls addDorF(Node *newNode) helper function that creates a new file/directory in the current directory.
//The function will return true if the file/directory has been created successfully or false if the file/directory with the specified name already exists.
bool FileSystem::makeDirectoryOrFile(std::string name, std::string type)
{

    if (this->searchCurrentDirectory(name))
        return false;
    Node *newNode = new Node(nullptr, current,nullptr, name, type);

    if (this->addDorF(newNode))
        return true;
    return false;
}

//helper function that adds a file or directory to the current directory
bool FileSystem::addDorF(Node *newNode)
{

    Node *node = current->getChild();
    if (!node)
    {
        current->addChild(newNode);
        return true;
    }
    else if (node && newNode->getName() < node->getName())
    {
        newNode->setNext(node);
        current->addChild(newNode);
        return true;
    }
    else
    {
        while (node->getNext())
        {
            if (node->getNext()->getName() < newNode->getName())
            {
                node = node->getNext();
                continue;
            }
            else
            {
                break;
            }
        }
        newNode->setNext(node->getNext());
        node->setNext(newNode);
        return true;
    }
    return false;
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

//this function takes the name of the file to be found as a parameter and calls the findHelper() function which will recursively search for the file in the filetree.
Node *FileSystem::find(std::string name)
{
    Node *node = root;

    return findHelper(name, node);
}

//takes the name of a directory as a parameter and searches for it in the current directory. If it's found, sets the current directory to the one that's been found and returns true.
//If nothing is found, the function returns false.
bool FileSystem::changeDirectory(std::string name)
{

    if (name == ".." && current->getParent())
    {
        current = current->getParent();
        return true;
    }
    else
    {
        Node *node = this->searchCurrentDirectory(name);

        if (node && node->getFileType() == "D")
        {
            current = node;
            return true;
        }
    }
    return false;
}

//this function takes in the name of the file to be found and searches the filetree for the required file/directory.
//the function returns a nullptr if no file with the specified name is found.
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

//renames node
bool FileSystem::rename(std::string from, std::string to)
{
    if (this->searchCurrentDirectory(to))
        return false;
    Node *node = this->searchCurrentDirectory(from);
    if (node)
    {
        node->setName(to);
        return true;
    }
    return false;
}

//searches current directory for a node whose name matches the string passed in as a parameter.
Node *FileSystem::searchCurrentDirectory(std::string name)
{
    Node *node = current->getChild();
    if (!node)
        return nullptr;
    if (node->getName() == name)
    {
        return node;
    }
    while (node)
    {
        if (node->getName() == name)
        {
            return node;
        }
        node = node->getNext();
    }
    return nullptr;
}

//takes the name of the node that needs to be removed, searches for it in the current directory and removes it.
bool FileSystem::removeNode(std::string name)
{
    Node *node = current->getChild();
    Node *prev = nullptr;
    while (node->getNext())
    {

        if (node->getName() == name)
        {
            current->addChild(node->getNext());
            node->setNext(nullptr);
            removeHelper(node);
            return true;
        }
        else if (node->getNext()->getName() == name)
        {
            prev = node;
            node = node->getNext();
            prev->setNext(node->getNext());
            node->setNext(nullptr);
            removeHelper(node);
            return true;
        }
        node = node->getNext();
    }

    return false;
}

//recursively removes file/directory/subtree passed in as a parameter
void FileSystem::removeHelper(Node *node)
{
    if (!node)
    {
        return;
    }
    removeHelper(node->getChild());
    removeHelper(node->getNext());
    if (node)
    {
        delete node;
    }
}

//creates a copy of a file/directory/subtree and adds the copy to the filesystem while preserving the alphabetical order
bool FileSystem::copy(std::string from, std::string to)
{

    if (this->searchCurrentDirectory(to))
    {
        return false;
    }
    else
    {
        Node *copyFrom = this->searchCurrentDirectory(from);
        Node *copy = new Node(nullptr, this->current,nullptr, to, copyFrom->getFileType());
        copy->addChild(copyHelper(copyFrom->getChild()));
        this->addDorF(copy);
    }
    return true;
}

//receives a subtree as  a parameter and creates a copy of it using recursion
Node *FileSystem::copyHelper(Node *from)
{
    if (from != nullptr)
    {

        if (from != nullptr)
        {
            Node *copy = new Node(copyHelper(from->getChild()), from->getParent(), copyHelper(from->getNext()), from->getName(), from->getFileType());
            return copy;
        }
    }
    return nullptr;
}