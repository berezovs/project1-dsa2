
#include <iostream>
#include <string>
#include "FileSystem.hpp"
#include "Node.hpp"
#include "Terminal.hpp"

int main()
{
    Terminal *terminal = new Terminal("commands.txt");
    terminal->run();
    return 0;
}