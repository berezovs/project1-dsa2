
#include<iostream>
#include <string>
#include "FileSystem.hpp"

int main(){
   
   FileSystem *filesystem = new FileSystem();
   std::cout<<"$ "<<filesystem->printCurrentDirectory();
return 0;

}