/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Created by benedikt,
*/

#ifndef ARCADE_SHIP_HPP
#define ARCADE_SHIP_HPP

#include <stack>
#include <chrono>
#include "../../lib_include/gfx_interface.hpp"
#include "centipede.hpp"

class Ship {
    public:
    Ship(IGraphics *lib);

    void setLib(IGraphics *lib);
    void loadSprites();
    bool handleInput(const std::string& input);
    void draw();
    void shootProjectile();
    void moveProjectiles();
    std::vector<std::pair<int, int>> getProjectilePosition();
    void deleteProjectileAtPos(std::pair<int, int> position);
    void deleteAllProjectiles();
    void resetPosition();
    std::pair<int, int> getPosition();

    object_creation_data shipSpriteData = {\
   object_type::SPRITE, "^", "lib/centipede/resources/ship.png", "red" };
    object_creation_data projectileSpriteData = {\
   object_type::SPRITE, "*", "lib/centipede/resources/projectile.png", "yellow" };

    private:
    std::chrono::steady_clock::time_point last_shot_time = std::chrono::steady_clock::now();
    double shots_per_second = 0.33;
    IGraphics *_gfx;
    void *_sprite;
    void *_projectileSprite;
    std::vector<std::pair<int, int>> _projectilePositions;
    std::pair<int, int> _position = { Centipedes::ScreenData::TILE_WIDTH * (int)((Centipedes::ScreenData::WIDTH / Centipedes::ScreenData::TILE_WIDTH) / 2), Centipedes::ScreenData::HEIGHT - Centipedes::ScreenData::TILE_HEIGHT * 2};

};

#endif //ARCADE_SHIP_HPP
