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

    void loadCommandsFromFile();
    void executeCommand(std::string command, std::string argument);

    
    public:
    Terminal(std::string filename);
    void run();
};

#endif