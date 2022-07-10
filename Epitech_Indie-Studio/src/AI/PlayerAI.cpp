/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/
#include "PlayerAI.hpp"


int getObjectTypeByPosition(std::list<IGameObject *> objects, int posX, int posY,
    Player *self)
{
    for (auto object : objects) {
        if (object != self && (int) object->transform.translation.x == posX && (int) (object->transform.translation.y == posY)) {
            if (object->type == "Obstacle") {
                if (self->stats->isWallPassActive)
                    return 1;
                return 0;
            } else if  (object->type == "Chest") {
                return  -1;
            } else if  (object->type == "PowerUp") {
                return  -2;
            } else if  (object->type == "Player" && !object->dying) {
                return  -1;
            }
        }
    }
    return 1;
}


PlayerAI::PlayerAI(Player *parent) : _parent(parent)
{
    valueMap.resize(HEIGHT);
    for (auto rows : valueMap) rows.resize(WIDTH);
    valueMapBuffer.resize(HEIGHT);
    for (auto rows : valueMapBuffer) rows.resize(WIDTH);
    pathMap.resize(HEIGHT);
    for (auto rows : valueMap) rows.resize(WIDTH);
    pathMapBuffer.resize(HEIGHT);
    for (auto rows : valueMapBuffer) rows.resize(WIDTH);


    _pos = {(int) _parent->transform.translation.x, (int) _parent->transform.translation.z};

    for (int y = 1; y < HEIGHT; y++) {
        for (int x = 1; x < WIDTH; x++) {
            if (y % 2 == 1 && x % 2 == 1) {
                intersections.push_back(std::make_pair(vector2D_t {x, y}, std::make_pair(0, 1)));
            }
        }
    }
}


void PlayerAI::update(std::list<IGameObject *> objects)
{

    _pos = {(int) _parent->transform.translation.x, (int) _parent->transform.translation.z};

    if (valueMap[_pos.x][_pos.y] >= ENEMY_PLAYER && valueMap[_pos.x][_pos.y] <= SAFE_SPACE) {
        _goalType = NONE;
    }
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int type = getObjectTypeByPosition(objects, x, y, _parent);
            valueMapBuffer[y][x] = type;
            pathMapBuffer[y][x] = (type != 0 ? 1 : 0);
        }
    }
    if (valueMapBuffer != valueMap) {
        valueMap = valueMapBuffer;
        //calcPath(_goal, 0);
    }
}

/*
int PlayerAI::calcPath(vector2D_t goal, int x, int y, int curDistance, int maxDistance)
{
    int minDistance = 0;
    //std::vector<std::pair<vector2D_t, int>> prevIntersections;
    vector2D_t goalVelocity = {(goal.x < _pos.x ? -2 : 2),  (goal.y < _pos.y ? -2 : 2)};

    if (x % 2 == 0) {
        if (pathMapBuffer[y][x + int (goalVelocity.x / 2)] != 0) {
            x += int (goalVelocity.x / 2);
        } else if (pathMapBuffer[y][x - int (goalVelocity.x / 2)] != 0)
            x -= int (goalVelocity.x / 2);
        else
            return -1;
    } else if (y % 2 == 0) {
        if (pathMapBuffer[y + int(goalVelocity.y / 2)][x] != 0) {
            y += int(goalVelocity.y / 2);
        } else if (pathMapBuffer[y + int(goalVelocity.x / 2)][x] != 0)
            y -= int(goalVelocity.y / 2);
        return -1;
    }

    for (; x != goal.x && y != goal.y; minDistance++) {
        if (x != goal.x && pathMapBuffer[y][x + goalVelocity.x] != 0 &&  {x += goalVelocity.x;
            if (x % 2 == 0 && y % 2 == 0) {

            }
    }
    return minDistance;
} */

void PlayerAI::determineGoal()
{
    for (int off = 1; _pos.x - off >= 0 || _pos.x + off < WIDTH ||
        _pos.y - off >= 0 || _pos.y + off < HEIGHT; off++) {
        if (_pos.x - off >= 0) {
            if (checkPositionIsGoal(_pos.x - off, _pos.y)) return;
        } else if (_pos.x + off < WIDTH) {
            if (checkPositionIsGoal(_pos.x + off, _pos.y)) return;
        } else  if (_pos.y - off >= 0) {
            if (checkPositionIsGoal(_pos.x, _pos.y - off)) return;
        } else if (_pos.y + off >= 0) {
            if (checkPositionIsGoal(_pos.x, _pos.y + off)) return;
        }
    }
}

bool PlayerAI::checkPositionIsGoal(int x, int y)
{
    if (!(valueMap[y][x] == POWER_UP || valueMap[y][x] == ENEMY_PLAYER))
        return false;
    if ( _goalType <= NONE) {
        _goalType = (DESIRED_OBJECTS) valueMap[y][x];
        _goal = {x, y};
        return true;
    }
    return false;
}