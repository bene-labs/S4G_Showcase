/*
** EPITECH PROJECT, 2024
** nibbler
** File description:
** Created by benedikt,
*/

#ifndef NIBBLER_SNAKE_HPP
#define NIBBLER_SNAKE_HPP

#include "snakeSegments.hpp"

class Snake {
    public:
    Snake(int size = 4, float speed = 1.5f);
    ~Snake();

    void move();
    void draw(IGraphics *lib);
    void increaseSize();
    void setDirection(std::string input);
    void updateSegmentDirections();
    bool isCollisionWithObject(std::pair<int, int> position,
        bool completeCollison
    );
    bool isCollisionWithSelf();
    bool isOutOfBounds();

    std::vector<std::pair<int, int>> getAllSegmentPositions();

    void *sprites[4][4];

    private:
    SnakeSegments *segments = nullptr;

    std::map<std::pair<SnakeSegments::Direction, SnakeSegments::Direction>, int> SegmentCornerCases;
};
#endif //NIBBLER_SNAKE_HPP
