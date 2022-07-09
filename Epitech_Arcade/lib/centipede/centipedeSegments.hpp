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
#include "../../lib_include/gfx_interface.hpp"

class CentipedeSegments {
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

    enum EnemyType {
        SNAKE,
        WORM
    };

    CentipedeSegments(std::pair<int, int> position, Type type = HEAD,
        Direction direction = RIGHT, int toBeAdded = 1
    );
    ~CentipedeSegments();


    void updateDirections();
    void move();
    void draw(void *baseSprites[4][4], IGraphics *lib,
        std::map<std::pair<CentipedeSegments::Direction, CentipedeSegments::Direction>, int> CornerCases);

    static bool isCollision(std::pair<int, int> position1, std::pair<int, int> position2,  bool checkForCompleteCollision);
    bool isAnyCollision(std::pair<int, int> position, bool checkForCompleteCollision = false);
    bool isSelfCollision();

    void add_new_segment();

    Direction getDirection();
    void setDirections(Direction direction);
    std::pair<int, int> getPosition();
    std::vector<std::pair<int, int>> getAllPositions();

    std::pair<CentipedeSegments *, CentipedeSegments *> split();
    std::pair<CentipedeSegments *, CentipedeSegments *> splitFromPosition(std::pair<int, int> splitPosition);
    Direction getOppositeDirection(Direction direction);

    CentipedeSegments::Direction _turn = CentipedeSegments::Direction::LEFT;

    bool _isTurnQueued = false;
    bool spawnedBySplit = false;

    private:

    CentipedeSegments *next = nullptr;

    Direction _direction = RIGHT;
    Type _type = HEAD;

    std::pair<int, int> _position;
};

#endif //NIBBLER_SNAKESEGMENTS_HPP
