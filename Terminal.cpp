#include <iostream>
#include <fstream>
#include <sstream>
#include "Terminal.hpp"
#include "FileSystem.hpp"

//C-TOR; initializes the filesystem
Terminal::Terminal(std::string filename)
{
    this->filename = filename;
    fileSystem = new FileSystem();
    
}

//calls the function that reads commands.txt
void Terminal::run(){
    this->loadCommandsFromFile();
}


//reads commands.txt and calls the function that executes the command
void Terminal::loadCommandsFromFile()
{
    std::string line, command, argument;

    this->commandFile.open(this->filename);
    while (getline(commandFile, line))
    {
        command = "";
        argument = "";
        std::istringstream ss(line);
        getline(ss, command, ' ');
        getline(ss, argument);

        this->executeCommand(command, argument);
    }
}


//executes commands read from commands.txt
void Terminal::executeCommand(std::string command, std::string argument)
{
    if (command == "ls")
    {
        std::cout << "$ " << command << " " << std::endl;
        std::cout << fileSystem->listAllFiles() << std::endl;
    }
    else if (command == "pwd")
    {
        std::cout << "$ " << command << " " << std::endl;
        std::cout << fileSystem->getCurrentDirectory() << std::endl;
    }
    else if (command == "mkdir")
    {
        std::cout << "$ " << command << " " << argument << std::endl;
        if (fileSystem->makeDirectoryOrFile(argument, "D"))
        {
            std::cout << "Directory " << argument << " created!" << std::endl;
        }
        else
        {
            std::cout << "Directory " << argument << " already exists!" << std::endl;
        }
    }
    else if (command == "addf")
    {
        std::cout << "$ " << command << " " << argument << std::endl;
        if (fileSystem->makeDirectoryOrFile(argument, "F"))
        {
            std::cout << "File " << argument << " created!" << std::endl;
        }
        else
        {
            std::cout << "File " << argument << " already exists!" << std::endl;
        }
    }
    else if (command == "mv")
    {
        std::istringstream stringbuffer(argument);
        std::string from, to;
        getline(stringbuffer, from, ' ');
        getline(stringbuffer, to, ' ');

        std::cout << "$ " << command << " " << from << " " << to << std::endl;

        if (fileSystem->rename(from, to))
        {
            std::cout << "File/directory successfully renamed from " << from << " to " << to << "!" << std::endl;
        }
        else
        {
            std::cout << "File/directory " << from << " could not be renamed!" << std::endl;
        }
    }
    else if (command == "cp")
    {
        std::istringstream stringbuffer(argument);
        std::string from, to;
        getline(stringbuffer, from, ' ');
        getline(stringbuffer, to, ' ');

        std::cout << "$ " << command << " " << from << " " << to << std::endl;
        if (fileSystem->copy(from, to))
        {
            std::cout << "File/directory  " << from << " succesfully copied!" << std::endl;
        }
    }
    else if (command == "cd")
    {
        std::cout << "$ " << command << " " << argument << std::endl;
        if (fileSystem->changeDirectory(argument))
        {
            std::cout << fileSystem->getCurrentDirectory() << std::endl;
        }
        else
        {
            std::cout << "Directory could not be found." << std::endl;
        }
    }
    else if (command == "whereis")

    {
        std::cout << "$ " << command << " " << argument << std::endl;
        std::cout << fileSystem->getPath(fileSystem->find(argument)) << std::endl;
    }
    else if (command == "rm")
    {
        std::cout << "$ " << command << " " << argument << std::endl;
        if (fileSystem->removeNode(argument))
        {
            std::cout << "File/Directory " << argument << " has been successfully removed." << std::endl;
        }
        else
        {
            std::cout << "File/Directory " << argument << " does not exist!" << std::endl;
        }
    }
    else if (command == "bye")
    {
        std::cout << "$ " << command << std::endl;
        std::cout << "Exiting command line..." << std::endl;
        return;
    }
    else
    {
        std::cout << "Unknown command" << std::endl;
    }
}