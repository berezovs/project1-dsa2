
#include <iostream>
#include <string>
#include "FileSystem.hpp"
#include "Node.hpp"

int main()
{

    FileSystem *filesystem = new FileSystem();
    std::cout << "$ " << filesystem->getCurrentDirectory();
    filesystem->makeDirectoryOrFile("directory1", "D");
    filesystem->makeDirectoryOrFile("directory2", "D");
    filesystem->makeDirectoryOrFile("directory3", "D");
    filesystem->makeDirectoryOrFile("file1", "F");
    filesystem->makeDirectoryOrFile("File2", "F");
    std::cout << std::endl;
    filesystem->changeDirectory("directory2");
     filesystem->makeDirectoryOrFile("f1", "F");
    filesystem->makeDirectoryOrFile("F2", "F"); 
    filesystem->changeDirectory("..");
    std::cout<<filesystem->removeNode("directory1")<<std::endl;

    //std::cout<<filesystem->listAllFiles()<<std::endl;
   std::cout<< filesystem->copy("directory2", "dir3")<<std::endl;
    
 //std::cout<<filesystem->changeDirectory("dir3");
 //std::cout<<filesystem->listAllFiles()<<std::endl;
    



    return 0;
}