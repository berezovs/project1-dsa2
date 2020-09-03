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


//takes a node as a parametar and returns a string representation of its path
std::string FileSystem::getPath(Node* node){
    if(!node)
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


//this function takes the name of the file to be found as a parameter and calls the findHelper() function which will recursively search for the file in the filetree.
Node *FileSystem::find(std::string name)
{
    Node *node = root;

    return findHelper(name, node);
}


//takes the name of a directory as a parameter and searches for it in the current directory. If it's found, sets the current directory to the one that's been found and returns true.
//If nothing is found, the function returns false.
bool FileSystem::changeDirectory(std::string name){
   
    if(name==".."&& current->getParent())
        {
        current=current->getParent();
        return true;
        }
        else{
            Node *node = current->getChild();
            while(node->getNext()){
                if(node->getName()==name && node->getFileType()=="D")
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

