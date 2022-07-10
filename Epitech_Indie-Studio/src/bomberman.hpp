/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#ifndef BOMBERMAN_BOMBERMAN_HPP
#define BOMBERMAN_BOMBERMAN_HPP

#include <raylib.h>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>

#include "PlayerConfigs.hpp"

std::vector<Model> getModelFramesFromFile(const char *animationFramesBasePath, int *frames);


enum MENU_STATE {
    LOADING,
    START,
    SETTING,
    GAME_SELECT,
    LEVELS,
    PLAYER_SELECT,
    QUIT,
    IN_GAME,

};

#endif //BOMBERMAN_BOMBERMAN_HPP
