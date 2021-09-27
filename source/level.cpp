#include <fstream>
#include <sstream>
#include <vector>
#include "level.hpp"

template <class T>
bool loadData(T &destination, std::stringstream &buffer) {
    size_t length = 0;
    char *data = nullptr;
    bool returnValue;
    buffer.read(reinterpret_cast<char *>(&length), 4);
    data = new char[length];
    if (!data) return false;
    buffer.read(data, static_cast<std::streamsize>(length));
    returnValue = destination.loadFromMemory(static_cast<const void*>(data), length);
    delete data;
    return returnValue;
}

Level::Level(): 
pointsLeft{0} {
    sf::Image blankImage;
    sf::Texture missingTexture;
    blankImage.create(Tile::width, Tile::height, sf::Color(255, 255, 255));
    missingTexture.loadFromImage(blankImage);
    mapTextures.push_back(missingTexture);
}

bool Level::load(std::string &path) {
    std::ifstream file(path, std::ifstream::in | std::ifstream::binary);
    std::stringstream buffer;
    size_t num = 0;
    
    file.open(path);
    if (!file.is_open()) return false;
    buffer << file.rdbuf();
    if (buffer.str().substr(0, 8) != "\x8ALVL\x0D\x0A\x1A\x0A") return false;
    buffer.seekg(8, buffer.beg);
    if (!loadData(pointTexture, buffer)) return false;
    if (!loadData(powerUpTexture, buffer)) return false;
    buffer.read(reinterpret_cast<char *>(&num), 4);
    for (size_t i = 0; i < num; ++i) {
        mapTextures.push_back(sf::Texture());
        if (!loadData(mapTextures[i], buffer)) return false;
    }
    if (!loadData(pointSound, buffer)) return false;
    if (!loadData(powerUpSound, buffer)) return false;
    if (!loadData(playerHitSound, buffer)) return false;
    if (!loadData(ghostHitSound, buffer)) return false;
    if (!loadData(winSound, buffer)) return false;
    if (!loadData(map, buffer)) return false;
    if (!loadData(player, buffer)) return false;
    buffer.read(reinterpret_cast<char *>(&num), 4);
    for (size_t i = 0; i < num; ++i) {
        ghosts.push_back(Ghost());
        if (!loadData(ghosts[i], buffer)) return false;
    }
    if (buffer.str().substr(buffer.str().length()-8) != "\x8A""END\x0D\x0A\x1A\x0A") return false;
    file.close();
    return true;
}

LevelMap::LevelMap(): 
sizeX{0},
sizeY{0} {
}

bool LevelMap::loadFromMemory(const void *data, std::size_t size) {
    std::stringstream buffer;
    unsigned short tileData;

    buffer.write(reinterpret_cast<const char *>(data), static_cast<std::streamsize>(size));
    buffer.read(reinterpret_cast<char *>(&sizeX), 2);
    if (sizeX > 64) return false;
    buffer.read(reinterpret_cast<char *>(&sizeY), 2);
    if (sizeY > 64) return false;
    if (static_cast<size_t>(4 + 2 * sizeX * sizeY) != size) return false;
    for (size_t i = 0; i < sizeX * sizeY; ++i) {
        buffer.read(reinterpret_cast<char *>(&tileData), 2);
        layout.push_back(Tile(tileData));
    }
    return true;
}

Tile::Tile(): 
textureID{0}, 
hasPoint{false}, 
hasPowerUp{false}, 
accessibleByGhosts{false}, 
accessibleByPlayer{false} {  
}

Tile::Tile(const unsigned short &data) {
    unsigned short mask = 32768;
    hasPowerUp = data & mask;
    hasPoint = data & (mask << 1);
    accessibleByGhosts = data & (mask << 2);
    accessibleByPlayer = data & (mask << 3);
    textureID = static_cast<size_t>(data & ((mask << 3) - 1));
}