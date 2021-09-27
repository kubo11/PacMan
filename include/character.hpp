#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Character{
    char direction;
    unsigned short speed;
    unsigned short posX;
    unsigned short posY;
    std::vector<sf::Texture> textureFramesUP;
    std::vector<sf::Texture> textureFramesDOWN;
    std::vector<sf::Texture> textureFramesLEFT;
    std::vector<sf::Texture> textureFramesRIGHT;
public:
    const static unsigned short baseSpeed = 32;     // pixles per second
    Character();
    bool loadFromMemory(const void *data, std::size_t size);
};

class Player: public Character{
public:
    Player();
};

class Ghost: public Character{
public:
    Ghost();
};

bool loadFrames(std::stringstream &buffer, const std::size_t &numOfFrames, std::vector<sf::Texture> &target);