/*
** EPITECH PROJECT, 2024
** nibbler
** File description:
** Created by benedikt,
*/

#include "box.hpp"
#include "centipede.hpp"

Box::Box(IGraphics *lib)
{
    _lib = lib;
    loadSprites();
    for (int i = 80; i < Centipedes::ScreenData::WIDTH - Centipedes::ScreenData::TILE_WIDTH * 2; i+= Centipedes::ScreenData::TILE_WIDTH) {
        for (int j = 0; j < (int) Centipedes::ScreenData::HEIGHT * 0.8 - (int)Centipedes::ScreenData::TILE_HEIGHT; j += Centipedes::ScreenData::TILE_HEIGHT) {
            possibleSpawns[std::make_pair(i, j)] = true;
        }
    }
}


std::vector<std::pair<int, int>> Box::getPositions()
{
    return _positions;
}

void Box::updatePossibleSpawns(std::vector<std::pair<int, int>> takenSpaces)
{
    for (auto & possibleSpawn : possibleSpawns) {
        for (auto taken_it = takenSpaces.begin(); taken_it != takenSpaces.end(); taken_it++) {
            if (CentipedeSegments::isCollision(possibleSpawn.first, *taken_it, false)) {
                possibleSpawn.second = false;
                break;
            } else {
                possibleSpawn.second = true;
            }
        }
    }
}

void Box::spawn(int boxNb)
{
    for (int i = 0; i < boxNb; i++) {
        std::vector<std::pair<int, int>> allowedSpawns;
        for (auto &possibleSpawn : possibleSpawns) {
            if (possibleSpawn.second)
                allowedSpawns.push_back(possibleSpawn.first);
        }
        _positions.push_back(allowedSpawns[std::rand() % allowedSpawns.size()]);
        _hpStates.push_back(5);
        updatePossibleSpawns(_positions);
        totalBoxes++;
    }
}

void Box::drawAll()
{
    int i = 0;
    for (auto _position : _positions) {
        _lib->draw(_sprites[_hpStates[i] - 1], _position.first,
            _position.first + Centipedes::ScreenData::TILE_WIDTH,
            _position.second,
            _position.second + Centipedes::ScreenData::TILE_HEIGHT);
        i++;
    }
}

void Box::respawn(std::pair<int, int> prev_position)
{
    for (int i = 0; i < _positions.size(); i++) {
        if (prev_position == _positions[i]) {
            std::vector<std::pair<int, int>> allowedSpawns;
            for (auto & possibleSpawn : possibleSpawns) {
                if (possibleSpawn.second)
                    allowedSpawns.push_back(possibleSpawn.first);
            }
            _positions[i] = allowedSpawns[std::rand() % allowedSpawns.size()];
            _hpStates[i] = 5;
            return;
        }
    }
}

void Box::loadSprites()
{
    for (int i = 0; i < 5; i++) {
        _sprites[i] = _lib->createObject(&boxCreationData[i]);
    }
}

void Box::useLib(IGraphics *lib)
{
    _lib = lib;
}

std::pair<int, int> Box::handleProjectileCollision(
    std::vector<std::pair<int, int>> projectilePosition)
{
    int i = 0;
    auto hp_it = _hpStates.begin();

    for (auto  it = _positions.begin(); it != _positions.end(); it++) {
        for (auto it_projectile = projectilePosition.begin(); it_projectile != projectilePosition.end(); it_projectile++) {
            if (CentipedeSegments::isCollision(*it.base(), \
                *it_projectile.base(), true)) {
                _hpStates[i]--;
                if (*hp_it == 0) {
                    _positions.erase(it);
                    _hpStates.erase(hp_it);
                }
                return *it_projectile;
            }
        }
        i++;
        hp_it++;
    }
    return std::pair<int, int>();
}

void Box::spawnAtFixedPos(std::pair<int, int> pos)
{
    _positions.push_back(pos);
    _hpStates.push_back(5);
}

void Box::removeAllBoxes()
{
    _positions.clear();
    _hpStates.clear();
}
