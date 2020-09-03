
#include<iostream>
#include <string>
#include "FileSystem.hpp"
#include "Node.hpp"

int main(){
   
   FileSystem *filesystem = new FileSystem();
   std::cout<<"$ "<<filesystem->getCurrentDirectory();
   filesystem->makeDirectoryOrFile("directory1", "D");
   filesystem->makeDirectoryOrFile("directory2", "D");
   filesystem->makeDirectoryOrFile("directory3", "D");
   filesystem->makeDirectoryOrFile("file1", "F");
   filesystem->makeDirectoryOrFile("File2", "F");
   std::cout<<std::endl;
   std::cout<<filesystem->listAllFiles();
   Node* node = filesystem->find("dir1");
   if(node)
   std::cout<<node->getName()<<std::endl;
   else
   {
       std::cout<<"Null result!"<<std::endl;
   }
   std::cout<<filesystem->getPath(node);

   filesystem->changeDirectory("directory2");
   std::cout<<"$ "<<filesystem->getCurrentDirectory();
   filesystem->changeDirectory("..");
   std::cout<<"$ "<<filesystem->getCurrentDirectory();

   
return 0;

}