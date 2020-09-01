
#include<iostream>
#include <string>
#include "FileSystem.hpp"

int main(){
   
   FileSystem *filesystem = new FileSystem();
   std::cout<<"$ "<<filesystem->printCurrentDirectory();
   filesystem->makeDirectoryOrFile("directory1", "D");
   filesystem->makeDirectoryOrFile("directory2", "D");
   filesystem->makeDirectoryOrFile("directory3", "D");
   filesystem->makeDirectoryOrFile("file1", "F");
   filesystem->makeDirectoryOrFile("File2", "F");
   std::cout<<std::endl;
   std::cout<<filesystem->listAllFiles();
return 0;

}