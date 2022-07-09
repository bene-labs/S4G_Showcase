/*
** EPITECH PROJECT, 2024
** nibbler
** File description:
** Created by benedikt,
*/
#include "../include/snakeSegments.hpp"



SnakeSegments::~SnakeSegments()
{
}

SnakeSegments::SnakeSegments(std::pair<int, int> position, Type type,
    Direction direction, int toBeAdded
)
{
    _position = position;
    _direction = direction;
    _type = type;

    toBeAdded--;
    if (toBeAdded == 0)
        _type = TAIL;
    fflush(stdout);
    if (toBeAdded > 0)
        this->next = new SnakeSegments({_position.first - 80, _position.second}, BODY, RIGHT, toBeAdded);
}

void SnakeSegments::updateDirections()
{
    Direction newDirection = this->_direction;
    for (auto it = this; it->next != nullptr; it = it->next) {
        Direction saveDirection = it->next->_direction;
        it->next->_direction = newDirection;
        newDirection = saveDirection;
    }
}

SnakeSegments::Direction SnakeSegments::getDirection()
{
    return this->_direction;
}

void SnakeSegments::move()
{
    switch (this->_direction) {
    case LEFT:
        this->_position.first -= 80;
        break;
    case UP:
        this->_position.second -= 80;
        break;
    case RIGHT:
        this->_position.first += 80;
        break;
    case DOWN:
        this->_position.second += 80;
        break;
    }
    if (this->next != nullptr)
        this->next->move();
}

void SnakeSegments::add_new_segment()
{
    if (!this->next)
        return;
    auto it = this->next;
    for (; it->next != nullptr; it = it->next);

    it->_type = BODY;
    switch (it->_direction) {
    case LEFT:
        it->next = new SnakeSegments({it->_position.first + 80, it->_position.second}, it->_type, it->_direction);
        break;
    case UP:
        it->next = new SnakeSegments({it->_position.first, it->_position.second + 80}, it->_type, it->_direction);
        break;
    case RIGHT:
        it->next = new SnakeSegments({it->_position.first - 80, it->_position.second}, it->_type, it->_direction);
        break;
    case DOWN:
        it->next = new SnakeSegments({it->_position.first, it->_position.second - 80}, it->_type, it->_direction);
        break;
    }
}

void SnakeSegments::draw(void *baseSprites[4][4], IGraphics *lib,
    std::map<std::pair<SnakeSegments::Direction, SnakeSegments::Direction>, int> CornerCases
)
{
    lib->draw(baseSprites[_type][_direction], _position.first, _position.first + 80, _position.second, _position.second + 80);

    Direction prevDirection = this->_direction;
    auto it = this->next;
    if (it == nullptr || it->next == nullptr)
        return;
    for (; it->next->next; it = it->next) {
        if (prevDirection != it->_direction)
            lib->draw(baseSprites[CORNER][CornerCases[std::make_pair(it->_direction, prevDirection)]],  it->_position.first,  it->_position.first + 80,  it->_position.second,  it->_position.second + 80);
        else
            lib->draw(baseSprites[ it->_type][ it->_direction],  it->_position.first,  it->_position.first + 80,  it->_position.second,  it->_position.second + 80);
        prevDirection = it->_direction;
    }
    lib->draw(baseSprites[TAIL][prevDirection], it->_position.first, it->_position.first + 80, it->_position.second, it->_position.second + 80);
}

void SnakeSegments::setDirections(SnakeSegments::Direction direction)
{
    this->_direction = direction;
}

bool SnakeSegments::isAnyCollision(std::pair<int, int> position,  bool checkForCompleteCollision)
{

    /*if (checkForCompleteCollision) {
        if (_position.first == _position.first && _position.second == _position.second)
            return true;
    }
    else if (\
(_position.first >= _position.first && _position.first <= _position.first + 80 \
&& _position.second >= _position.second && _position.second <= _position.second + 80) \
|| (_position.first >= _position.first && _position.first <= _position.first + 80 \
&& _position.second >= _position.second && _position.second <= _position.second + 80))
        return true;*/
    if (this->next == nullptr)
        return false;
    if (SnakeSegments::isCollision(_position, position,
        checkForCompleteCollision))
        return true;
    return this->next->isAnyCollision(position, checkForCompleteCollision);
}

bool SnakeSegments::isSelfCollision()
{
    if (!this->next || !this->next->next)
        return false;
    return this->next->next->isAnyCollision(this->_position, true);
}

std::vector<std::pair<int, int>> SnakeSegments::getAllPositions()
{
    std::vector<std::pair<int, int>> res;
    for (auto it = this; it->next != nullptr; it = it->next) {
        res.push_back(it->_position);
    }
    return res;
}

bool SnakeSegments::isCollision(std::pair<int, int> position1,
    std::pair<int, int> position2, bool checkForCompleteCollision
)
{
    if (checkForCompleteCollision) {
        if (position1.first == position2.first &&
            position1.second == position2.second)
            return true;
    } else if (\
(position1.first >= position2.first && position1.first <= position2.first + 80 \
&& position1.second >= position2.second && position1.second <= position2.second + 80) \
|| (position2.first >= position1.first && position2.first <= position1.first + 80 \
&& position2.second >= position1.second && position2.second <= position1.second + 80))
            return true;
    return false;
}

std::pair<int, int> SnakeSegments::getPosition()
{
    return _position;
}


