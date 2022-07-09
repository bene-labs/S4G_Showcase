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

#include "centipede.hpp"

class Box {
    public:
    Box(IGraphics *lib);
    ~Box() = default;

    std::vector<std::pair<int, int>> getPositions();

    void useLib(IGraphics *lib);
    void loadSprites();
    void updatePossibleSpawns(std::vector<std::pair<int, int>> takenSpaces);
    void spawn(int boxNb = 1);
    void spawnAtFixedPos(std::pair<int, int> pos);
    void respawn(std::pair<int, int> prev_position);
    void drawAll();
    std::pair<int, int> handleProjectileCollision(std::vector<std::pair<int, int>> projectilePosition);
    void removeAllBoxes();


    void *_sprites[5];
    object_creation_data boxCreationData[5] = {\
    {object_type::SPRITE, "1", "lib/centipede/resources/box/1.png", "blue"},
        {object_type::SPRITE, "2", "lib/centipede/resources/box/2.png", "blue"},
        {object_type::SPRITE, "3", "lib/centipede/resources/box/3.png", "blue"},
        {object_type::SPRITE, "4", "lib/centipede/resources/box/4.png", "blue"},
        {object_type::SPRITE, "5", "lib/centipede/resources/box/5.png", "blue"} };


    Centipedes *centipedeReference;

    private:
    int totalBoxes = 0;
    std::vector<std::pair<int, int>> _positions;
    std::vector<int> _hpStates;
    std::map<std::pair<int, int>, bool> possibleSpawns;

    IGraphics *_lib;
};

#endif //NIBBLER_APPLE_HPP
