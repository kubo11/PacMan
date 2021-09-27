#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "character.hpp"

Character::Character() {
}

Player::Player() {
}

Ghost::Ghost() {
}

bool Character::loadFromMemory(const void* data, std::size_t size) {
    std::stringstream buffer;
    std::size_t numOfFrames = 0;

    buffer.write(reinterpret_cast<const char *>(data), static_cast<std::streamsize>(size));
    buffer.read(reinterpret_cast<char *>(&posX), 2);
    if (posX > 63) return false;
    buffer.read(reinterpret_cast<char *>(&posY), 2);
    if (posY > 63) return false;
    buffer.read(reinterpret_cast<char *>(&numOfFrames), 2);
    if (numOfFrames > 15) return false;
    if (!loadFrames(buffer, numOfFrames, textureFramesUP)) return false;
    if (!loadFrames(buffer, numOfFrames, textureFramesDOWN)) return false;
    if (!loadFrames(buffer, numOfFrames, textureFramesLEFT)) return false;
    if (!loadFrames(buffer, numOfFrames, textureFramesRIGHT)) return false;
    return true;
}

bool loadFrames(std::stringstream &buffer, const std::size_t &numOfFrames, std::vector<sf::Texture> &target) {
    char *data;
    std::size_t size = 0;
    
    for(size_t i = 0; i < numOfFrames; ++i) {
        target.push_back(sf::Texture());
        buffer.read(reinterpret_cast<char *>(&size), 4);
        data = new char[size];
        if (!data) return false;
        buffer.read(data, static_cast<std::streamsize>(size));
        if (!target[i].loadFromMemory(const_cast<const void*>(reinterpret_cast<void *>(data)), size)) {
            delete data;
            return false;
        }
        delete data;
    }
    return true;
}