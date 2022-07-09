/*
** EPITECH PROJECT, 2024
** nibbler
** File description:
** Created by benedikt,
*/

#ifndef NIBBLER_APPLE_HPP
#define NIBBLER_APPLE_HPP

#include <utility>
#include <map>
#include <vector>

#include "snake.hpp"

class Apple {
    public:
    Apple(void *regularSprite = nullptr);
    ~Apple() = default;

    std::pair<int, int> getPosition();

    void updatePossibleSpawns(std::vector<std::pair<int, int>> takenSpaces);
    void spawn();
    void drawAll(IGraphics *lib);

    void *_regularSprite;

    Snake *snakeReference;

    private:
    std::pair<int, int> _position;
    std::map<std::pair<int, int>, bool> possibleSpawns;

};

#endif //NIBBLER_APPLE_HPP
