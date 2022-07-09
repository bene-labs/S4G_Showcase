/*
** EPITECH PROJECT, 2024
** nibbler
** File description:
** Created by benedikt,
*/

#ifndef NIBBLER_SNAKESEGMENTS_HPP
#define NIBBLER_SNAKESEGMENTS_HPP

#include <utility>
#include <map>
#include <vector>
#include "../../../lib_include/gfx_interface.hpp"

class SnakeSegments {
    public:
    enum Direction {
        LEFT,
        UP,
        RIGHT,
        DOWN
    };
    enum Type {
        HEAD,
        BODY,
        CORNER,
        TAIL
    };

    SnakeSegments(std::pair<int, int> position, Type type = HEAD,
        Direction direction = RIGHT, int toBeAdded = 1
    );
    ~SnakeSegments();


    void updateDirections();
    void move();
    void draw(void *baseSprites[4][4], IGraphics *lib,
        std::map<std::pair<SnakeSegments::Direction, SnakeSegments::Direction>, int> CornerCases);

    static bool isCollision(std::pair<int, int> position1, std::pair<int, int> position2,  bool checkForCompleteCollision);
    bool isAnyCollision(std::pair<int, int> position, bool checkForCompleteCollision = false);
    bool isSelfCollision();

    void add_new_segment();

    Direction getDirection();
    void setDirections(Direction direction);
    std::pair<int, int> getPosition();
    std::vector<std::pair<int, int>> getAllPositions();

    private:

    SnakeSegments *next = nullptr;

    Direction _direction = RIGHT;
    Type _type = HEAD;

    std::pair<int, int> _position;
};

#endif //NIBBLER_SNAKESEGMENTS_HPP
