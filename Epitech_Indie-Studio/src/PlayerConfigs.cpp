/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#include "PlayerConfigs.hpp"

std::map<SETTINGS, int> PlayerConfigs::settings = {
    {SCREEN_WIDTH, 1000},
    {SCREEN_HEIGHT, 800},
    {PLAYER1_UP, KEY_UP},
    {PLAYER1_RIGHT, KEY_RIGHT},
    {PLAYER1_LEFT, KEY_LEFT},
    {PLAYER1_DOWN, KEY_DOWN}};

void PlayerConfigs::loadFromFile(const std::string& path)
{
    std::ifstream inputFileStream(path);
    int i = 0;

    for (std::string line; std::getline(inputFileStream, line) && i <= VOLUME_SOUND; i++) {
            settings[(SETTINGS) i] = std::atoi(line.substr(line.find(':') + 1).c_str());
        }
    _path = path;
}

PlayerConfigs::PlayerConfigs()
{
}

PlayerConfigs::~PlayerConfigs()
{
}