#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>
#include<fstream>
#include "FileSystem.hpp"

class Terminal{
    private:
    std::string filename;
    std::ifstream commandFile;
    FileSystem *fileSystem;

    
    public:
    Terminal(std::string filename);
    void loadCommandsFromFile();
    void executeCommand(std::string command, std::string argument);
};

#endif