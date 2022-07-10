/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#ifndef BOMBERMAN_PLAYERCONFIGS_HPP
#define BOMBERMAN_PLAYERCONFIGS_HPP

#include <string>
#include <fstream>
#include <map>
#include <raylib.h>
#include "2D/IGameObject2D.hpp"
#include <vector>
//#include "2D/LabeledButton.hpp"

//should encompass all data that the player wants to save permantly
// ==> settings for all configured settings including KeyBindings
// ==> Data required to load saved game

enum SETTINGS {
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    FPS,
    PLAYER1_UP,
    PLAYER1_DOWN,
    PLAYER1_BOMB,
    PLAYER1_LEFT,
    PLAYER1_RIGHT,
    PLAYER2_UP,
    PLAYER2_DOWN,
    PLAYER2_BOMB,
    PLAYER2_LEFT,
    PLAYER2_RIGHT,
    PLAYER3_UP,
    PLAYER3_DOWN,
    PLAYER3_BOMB,
    PLAYER3_LEFT,
    PLAYER3_RIGHT,
    PLAYER4_UP,
    PLAYER4_DOWN,
    PLAYER4_BOMB,
    PLAYER4_LEFT,
    PLAYER4_RIGHT,
    VOLUME_MUSIC,
    VOLUME_SOUND
};

class PlayerConfigs {
    public:

    PlayerConfigs();
    ~PlayerConfigs();

    static std::map<SETTINGS, int> settings;


    void loadFromFile(const std::string& path = "data/settings");

    private:
    std::string _path;
};


void updatePlayerConfigsFromButtonValues(PlayerConfigs *configs, std::vector<IGameObject2D *> keyBindingsElements);


#endif //BOMBERMAN_PLAYERCONFIGS_HPP
