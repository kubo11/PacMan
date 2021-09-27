#include <SFML/Graphics.hpp>
#include <iostream>
#include "level.hpp"

int main()
{
    Level activeLevel;
    std::string path;
    std::cout << "Path to level file: ";
    std::cin >> path;
    if (activeLevel.load(path)) 
        std::cout << "Level loaded successfully";
    else
        std::cout << "Level file corrupted";

    return 0;
}