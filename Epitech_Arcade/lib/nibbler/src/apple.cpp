/*
** EPITECH PROJECT, 2024
** nibbler
** File description:
** Created by benedikt,
*/

#include "../include/apple.hpp"

Apple::Apple(void *regularSprite)
{
    _regularSprite = regularSprite;

    for (int i = 0; i < 1200; i+= 80) {
        for (int j = 0; j < 960; j += 80) {
            possibleSpawns[std::make_pair(i, j)] = true;
        }
    }
}


std::pair<int, int> Apple::getPosition()
{
    return _position;
}

void Apple::updatePossibleSpawns(std::vector<std::pair<int, int>> takenSpaces)
{
    for (auto & possibleSpawn : possibleSpawns) {
        for (auto taken_it = takenSpaces.begin(); taken_it != takenSpaces.end(); taken_it++) {
            if (SnakeSegments::isCollision(possibleSpawn.first, *taken_it, false)) {
                possibleSpawn.second = false;
                break;
            } else {
                possibleSpawn.second = true;
            }
        }
    }
}

void Apple::spawn()
{
    std::vector<std::pair<int, int>> allowedSpawns;
    for (auto & possibleSpawn : possibleSpawns) {
        if (possibleSpawn.second)
            allowedSpawns.push_back(possibleSpawn.first);
    }
    _position = allowedSpawns[std::rand() % allowedSpawns.size()];
}

void Apple::drawAll(IGraphics *lib)
{
    lib->draw(_regularSprite, _position.first, _position.first + 80, _position.second, _position.second + 80);
}
