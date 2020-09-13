#include <iostream>
#include<fstream>
#include<sstream>
#include "Terminal.hpp"
#include "FileSystem.hpp"

Terminal::Terminal(std::string filename){
    this->filename = filename;
    fileSystem = new FileSystem();
    this->loadCommandsFromFile();
  
    
}
void Terminal::loadCommandsFromFile(){
    std::string line, command, argument;

    this->commandFile.open(this->filename);
    while(getline(commandFile, line)){
        command = "";
        argument= "";
        std::istringstream ss(line);
        getline(ss, command, ' ');
        getline(ss, argument);

        this->executeCommand(command, argument);
    }

   
}

 void Terminal::executeCommand(std::string command, std::string argument){
        if(command=="ls"){
            std::cout<<"$ "<<command<<" "<<std::endl;
            std::cout<<fileSystem->listAllFiles()<<std::endl;
        }
        else if(command =="pwd"){
            std::cout<<"$ "<<command<<" "<<std::endl;
             std::cout<<fileSystem->getCurrentDirectory()<<std::endl;
        }
        else if(command=="mkdir"){
            std::cout<<"$ "<<command<<" "<<std::endl;
           if( fileSystem->makeDirectoryOrFile(argument, "D")){
               std::cout<<"Directory "<<argument<<" created!"<<std::endl;
           }
           std::cout<<"Directory "<<argument<<" already exists!"<<std::endl;
        }
        else if(command=="addf"){

        }
        else if(command=="mv"){

        }
        else if(command=="cp"){

        }
        else if(command=="cd"){

        }
        else if (command=="whereis"){

        }
        else if(command=="rm"){

        }
        else if(command=="bye"){
            return;
        }
    }