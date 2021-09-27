#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "character.hpp"

class Tile{
    size_t textureID;
    bool hasPoint;
    bool hasPowerUp;
    bool accessibleByGhosts;
    bool accessibleByPlayer;
public:
    const static unsigned short width = 32;
    const static unsigned short height = 32;
    Tile();
    Tile(const unsigned short &data);
};

class LevelMap{
    std::vector<Tile> layout;
    unsigned short sizeX;
    unsigned short sizeY;
public:
    LevelMap();
    bool loadFromMemory(const void *data, std::size_t size);
};

class Level{
    unsigned int pointsLeft;
    sf::Texture pointTexture;
    sf::Texture powerUpTexture;
    std::vector<sf::Texture> mapTextures;
    sf::SoundBuffer pointSound;
    sf::SoundBuffer powerUpSound;
    sf::SoundBuffer playerHitSound;
    sf::SoundBuffer ghostHitSound;
    sf::SoundBuffer winSound;
    Player player;
    std::vector<Ghost> ghosts;
    LevelMap map;
    
public:
    Level();
    bool load(std::string &path);
};