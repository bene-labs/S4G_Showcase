/*
** EPITECH PROJECT, 2024
** nibbler
** File description:
** Created by benedikt,
*/

#include "centipede.hpp"
#include "centipedeSegments.hpp"

CentipedeSegments::~CentipedeSegments()
{
}

CentipedeSegments::CentipedeSegments(std::pair<int, int> position, Type type,
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
        this->next = new CentipedeSegments({_position.first - Centipedes::ScreenData::TILE_WIDTH, _position.second}, BODY, RIGHT, toBeAdded);
}

void CentipedeSegments::updateDirections()
{
    Direction newDirection = this->_direction;
    for (auto it = this; it->next != nullptr; it = it->next) {
        Direction saveDirection = it->next->_direction;
        it->next->_direction = newDirection;
        newDirection = saveDirection;
    }
}

CentipedeSegments::Direction CentipedeSegments::getDirection()
{
    return this->_direction;
}

void CentipedeSegments::move()
{
    switch (this->_direction) {
    case LEFT:
        this->_position.first -= Centipedes::ScreenData::TILE_WIDTH;
        break;
    case UP:
        this->_position.second -= Centipedes::ScreenData::TILE_WIDTH;
        break;
    case RIGHT:
        this->_position.first += Centipedes::ScreenData::TILE_WIDTH;
        break;
    case DOWN:
        this->_position.second += Centipedes::ScreenData::TILE_WIDTH;
        break;
    }
    if (this->next != nullptr)
        this->next->move();
}

void CentipedeSegments::add_new_segment()
{
    if (!this->next)
        return;
    auto it = this->next;
    for (; it->next != nullptr; it = it->next);

    it->_type = BODY;
    switch (it->_direction) {
    case LEFT:
        it->next = new CentipedeSegments({it->_position.first + Centipedes::ScreenData::TILE_WIDTH, it->_position.second}, it->_type, it->_direction);
        break;
    case UP:
        it->next = new CentipedeSegments({it->_position.first, it->_position.second + Centipedes::ScreenData::TILE_WIDTH}, it->_type, it->_direction);
        break;
    case RIGHT:
        it->next = new CentipedeSegments({it->_position.first - Centipedes::ScreenData::TILE_WIDTH, it->_position.second}, it->_type, it->_direction);
        break;
    case DOWN:
        it->next = new CentipedeSegments({it->_position.first, it->_position.second - Centipedes::ScreenData::TILE_WIDTH}, it->_type, it->_direction);
        break;
    }
}

void CentipedeSegments::draw(void *baseSprites[4][4], IGraphics *lib,
    std::map<std::pair<CentipedeSegments::Direction, CentipedeSegments::Direction>, int> CornerCases
)
{
    lib->draw(baseSprites[_type][_direction], _position.first, _position.first + Centipedes::ScreenData::TILE_WIDTH, _position.second, _position.second + Centipedes::ScreenData::TILE_WIDTH);

    Direction prevDirection = this->_direction;
    auto it = this->next;
    if (it == nullptr || it->next == nullptr)
        return;
    for (; it->next->next; it = it->next) {
        if (prevDirection != it->_direction)
            lib->draw(baseSprites[CORNER][CornerCases[std::make_pair(it->_direction, prevDirection)]],  it->_position.first,  it->_position.first + Centipedes::ScreenData::TILE_WIDTH,  it->_position.second,  it->_position.second + Centipedes::ScreenData::TILE_WIDTH);
        else
            lib->draw(baseSprites[ it->_type][ it->_direction],  it->_position.first,  it->_position.first + Centipedes::ScreenData::TILE_WIDTH,  it->_position.second,  it->_position.second + Centipedes::ScreenData::TILE_WIDTH);
        prevDirection = it->_direction;
    }
    lib->draw(baseSprites[TAIL][prevDirection], it->_position.first, it->_position.first + Centipedes::ScreenData::TILE_WIDTH, it->_position.second, it->_position.second + Centipedes::ScreenData::TILE_WIDTH);
}

void CentipedeSegments::setDirections(CentipedeSegments::Direction direction)
{
    this->_direction = direction;
}

bool CentipedeSegments::isAnyCollision(std::pair<int, int> position,  bool checkForCompleteCollision)
{

    /*if (checkForCompleteCollision) {
        if (_position.first == _position.first && _position.second == _position.second)
            return true;
    }
    else if (\
(_position.first >= _position.first && _position.first <= _position.first + Centipedes::ScreenData::TILE_WIDTH \
&& _position.second >= _position.second && _position.second <= _position.second + Centipedes::ScreenData::TILE_WIDTH) \
|| (_position.first >= _position.first && _position.first <= _position.first + Centipedes::ScreenData::TILE_WIDTH \
&& _position.second >= _position.second && _position.second <= _position.second + Centipedes::ScreenData::TILE_WIDTH))
        return true;*/
    if (this->next == nullptr)
        return false;
    if (CentipedeSegments::isCollision(_position, position,
        checkForCompleteCollision))
        return true;
    return this->next->isAnyCollision(position, checkForCompleteCollision);
}

bool CentipedeSegments::isSelfCollision()
{
    if (!this->next || !this->next->next)
        return false;
    return this->next->next->isAnyCollision(this->_position, true);
}

std::vector<std::pair<int, int>> CentipedeSegments::getAllPositions()
{
    std::vector<std::pair<int, int>> res;
    for (auto it = this; it; it = it->next) {
        res.push_back(it->_position);
    }
    return res;
}

bool CentipedeSegments::isCollision(std::pair<int, int> position1,
    std::pair<int, int> position2, bool checkForCompleteCollision
)
{
    if (checkForCompleteCollision) {
        if (position1.first == position2.first &&
            position1.second == position2.second)
            return true;
    } else if (\
(position1.first >= position2.first && position1.first <= position2.first + Centipedes::ScreenData::TILE_WIDTH \
&& position1.second >= position2.second && position1.second <= position2.second + Centipedes::ScreenData::TILE_WIDTH) \
|| (position2.first >= position1.first && position2.first <= position1.first + Centipedes::ScreenData::TILE_WIDTH \
&& position2.second >= position1.second && position2.second <= position1.second + Centipedes::ScreenData::TILE_WIDTH))
            return true;
    return false;
}

std::pair<int, int> CentipedeSegments::getPosition()
{
    return _position;
}

std::pair<CentipedeSegments *, CentipedeSegments *> CentipedeSegments::split()
{
    std::pair<CentipedeSegments *, CentipedeSegments *> res = {this, nullptr};

    int len = 0;
    if (!this->next)
        return res;
    for (CentipedeSegments *it = this; it; it = it->next) {
        len++;
    }
    if (len == 0)
        return res;

    len /= 2;
    if (len < 3)
        return res;
    CentipedeSegments *temp = this;
    for (int i = 0; i < len; i++) {
        temp = temp->next;
    }

    res.second = temp->next;

     CentipedeSegments *temp2 = res.second;
    std::vector<CentipedeSegments *> savedSegments;
    for (; temp2; temp2 = temp2->next) {
        savedSegments.push_back(temp2);
    }
    res.second = savedSegments[savedSegments.size() - 1];

    temp2 = res.second;
    for (int j = savedSegments.size() - 2; j >= 0; j--) {
        temp2->next = savedSegments[j];
        temp2 = temp2->next;
    }
    temp2->_type = TAIL;
    temp2->next = nullptr;
    res.second->_type = HEAD;
    res.second->_direction = getOppositeDirection(res.second->_direction);
    /*CentipedeSegments *temp2 = res.second;
    for (; temp2->next; temp2 = temp2->next);
    temp2->_type = TAIL;*/
    temp->_type = TAIL;
    temp->next = nullptr;
    res.first = this;
    return res;
}

CentipedeSegments::Direction CentipedeSegments::getOppositeDirection(
    CentipedeSegments::Direction direction
)
{
    switch (direction) {
    case UP:
        return DOWN;
    case DOWN:
        return UP;
    case RIGHT:
        return LEFT;
    case LEFT:
        return RIGHT;
    default:
        return LEFT;
    }
}

std::pair<CentipedeSegments *, CentipedeSegments *> CentipedeSegments::splitFromPosition(
    std::pair<int, int> splitPosition
)
{
    std::pair<CentipedeSegments *, CentipedeSegments *> res = {nullptr, nullptr};

    int len = 0;
    int pos = 1;
    if (!this->next)
        return res;
    for (CentipedeSegments *it = this->next; it; it = it->next) {
        len++;
    }
    if (len <= 4) {
        return res;
    }
    for (CentipedeSegments *it = this; it && it->_position != splitPosition; it = it->next) {
        pos++;
    }
    CentipedeSegments *temp = this;
    for (int i = 0; temp && i < pos; i++) {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr) {
        res.second = nullptr;
        if (pos >= 2)
            res.first = this;
        return res;
    } else if (temp->next->next == nullptr) {
        res.second = nullptr;
        temp->next = nullptr;
        if (pos >= 2)
            res.first = this;
        return res;
    }
    res.second = temp->next->next;
    res.second->_type = HEAD;
    CentipedeSegments *temp2 = res.second;
    for (len = 1; temp2 && temp2->next; temp2 = temp2->next, len++);
    if (len < 3) {
        res.second = nullptr;
        if (pos >= 2)
            res.first = this;
        return res;
    }
    //res.second->_direction = getOppositeDirection(res.second->_direction);
    res.second->spawnedBySplit = true;
    temp2->_type = TAIL;
    temp->_type = TAIL;
    temp->next = nullptr;
    if (pos >= 2)
        res.first = this;
    return res;
}


