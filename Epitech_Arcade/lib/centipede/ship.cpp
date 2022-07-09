/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Created by benedikt,
*/
#include "ship.hpp"

Ship::Ship(IGraphics *lib)
{
    setLib(lib);
    loadSprites();
}

bool Ship::handleInput(const std::string& input)
{
    std::chrono::steady_clock::time_point this_call_time = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::duration<double>>(
        this_call_time - last_shot_time).count() >= shots_per_second) {
        shootProjectile();
        last_shot_time = this_call_time;
    }
    if ((input == "left" || input == "a") && _position.first > 0) {
        _position.first -= Centipedes::TILE_WIDTH;
    } else if ((input == "right" || input == "d") && _position.first < Centipedes::WIDTH - Centipedes::TILE_WIDTH * 3) {
        _position.first += Centipedes::TILE_WIDTH;
    } else if ((input == "up" || input == "w") && _position.second > (int) Centipedes::ScreenData::HEIGHT * 0.8) {
        _position.second -= Centipedes::TILE_HEIGHT;
    } else if ((input == "down" || input == "s") && _position.second < Centipedes::ScreenData::HEIGHT - Centipedes::ScreenData::TILE_HEIGHT * 2) {
        _position.second += Centipedes::TILE_HEIGHT;
    } /*else if ((input == "space"))
        shootProjectile();*/
    else
        return false;
    return true;
}

void Ship::draw()
{
    _gfx->draw(_sprite, _position.first, _position.first + Centipedes::TILE_WIDTH * 3, \
    _position.second, _position.second + Centipedes::TILE_HEIGHT * 2);
    for (auto position : _projectilePositions)
        _gfx->draw(_projectileSprite, position.first, position.first + Centipedes::TILE_WIDTH, \
    position.second, position.second + Centipedes::TILE_HEIGHT);
}

void Ship::loadSprites()
{
    _sprite = _gfx->createObject(&shipSpriteData);
    _projectileSprite = _gfx->createObject(&projectileSpriteData);
}

void Ship::setLib(IGraphics *lib)
{
    _gfx = lib;
}

void Ship::shootProjectile()
{
    _projectilePositions.push_back(std::make_pair(_position.first + Centipedes::TILE_WIDTH, _position.second));
}

void Ship::moveProjectiles()
{
    for (auto it = _projectilePositions.begin(); it != _projectilePositions.end(); ) {
        it->second -= Centipedes::TILE_HEIGHT;
        if (it->second < 0) {
            it = _projectilePositions.erase(it);
        } else
            it++;
    }
}

std::vector<std::pair<int, int>> Ship::getProjectilePosition()
{
    return _projectilePositions;
}

void Ship::deleteProjectileAtPos(std::pair<int, int> position)
{
    for (auto it = _projectilePositions.begin(); it != _projectilePositions.end(); it++) {
        if (*it == position) {
            _projectilePositions.erase(it);
            return;
        }
    }
}

void Ship::resetPosition()
{
    _position = { Centipedes::ScreenData::TILE_WIDTH * (int)((Centipedes::ScreenData::WIDTH / Centipedes::ScreenData::TILE_WIDTH) / 2), Centipedes::ScreenData::HEIGHT - Centipedes::ScreenData::TILE_HEIGHT * 2};
}

void Ship::deleteAllProjectiles()
{
    _projectilePositions.clear();
}

std::pair<int, int> Ship::getPosition()
{
    return _position;
}
