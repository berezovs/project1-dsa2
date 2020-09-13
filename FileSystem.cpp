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

//this function traverses the file tree from the current directory all the way up to the root and builds a string
//representation of the path to the current directory
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

//This function will create a file/directory in the current directory after ensuring that no file or directory with the specified name already exists
bool FileSystem::makeDirectoryOrFile(std::string name, std::string type)
{
    Node *newNode = new Node(nullptr, current, name, type);

    if(this->addDorF(newNode))
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
        Node *node = current->getChild();
        while (node->getNext())
        {
            if (node->getName() == name && node->getFileType() == "D")
            {
                current = node;
                return true;
            }
            node = node->getNext();
        }
    }

    return false;
}

//this function takes in the name of the file to be found and recursively traverses the filetree from top to bottom in search for the required file.
//the function will return a nullptr if no file with the specified name is found.
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

bool FileSystem::rename(std::string from, std::string to)
{
    Node *node = searchCurrentDirectory(from);
    if (node)
    {
        node->setName(to);
        return true;
    }
    return false;
}

Node *FileSystem::searchCurrentDirectory(std::string name)
{
    Node *node = current->getChild();
    while (node->getNext())
    {
        if (node->getName() == name)
        {
            return node;
        }
        node = node->getNext();
    }
    return nullptr;
}

std::string FileSystem::removeNode(std::string name)
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
            return "File/Directory " + name + " deleted succesfully\n";
        }
        else if (node->getNext()->getName() == name)
        {
            prev = node;
            node = node->getNext();
            prev->setNext(node->getNext());
            node->setNext(nullptr);
            removeHelper(node);
            return "File/directory " + name + " deleted successfully!\n";
        }
        node = node->getNext();
    }

    return "The file/directory" + name + "couldn't be found!\n";
}

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

        std::cout << "Deleting: " << node->getName() << std::endl;
        delete node;
    }
}

std::string FileSystem::copy(std::string from, std::string to)
{

    if (this->searchCurrentDirectory(to))
    {
        return "This name file/directory already exists!\n";
    }
    else
    {
        Node *copyFrom = this->searchCurrentDirectory(from);
        Node *copy = new Node(nullptr, this->current, to, copyFrom->getFileType());
        copyHelper(copyFrom->getChild(), copy);
        this->addDorF(copy);
    }
    return "Successfully copied";
}

void FileSystem::copyHelper(Node *from, Node *to)
{
    if (from)
    {

        if (from->getChild())
        {
            std::cout << "Child of " << from->getChild()->getName() << std::endl;
            copyHelper(from->getChild(), to);
        }
        if (from->getNext())
        {
            std::cout << "Next to " << from->getNext()->getName() << std::endl;
            copyHelper(from->getNext(), to);
    }
          
        }
    }
