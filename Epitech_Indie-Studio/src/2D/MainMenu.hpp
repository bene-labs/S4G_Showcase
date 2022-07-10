/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#ifndef BOMBERMAN_MAINMENU_HPP
#define BOMBERMAN_MAINMENU_HPP

#include <map>
#include "../bomberman.hpp"
#include "IGameObject2D.hpp"
#include "Button.hpp"
#include "LabeledButton.hpp"
#include "MySprite.hpp"
#include "../Game.hpp"

class MainMenu {
    public:

    MainMenu(PlayerConfigs configs);
    ~MainMenu();

    int run(Game *game);

    void display_all();

    MENU_STATE menuState = LOADING;

    private:
    float _sw;
    float _sh;

    std::vector<Font> availableFonts;
    std::vector<Texture2D> availableTextures;

    PlayerConfigs playerConfigs;
    Image backgroundImage;
    Camera2D camera = {0};
    std::map<MENU_STATE, std::vector<IGameObject2D *>> gameObjects;

    Music music;
    Sound selectSound;
    Sound backSound;


    void saveToFile(std::vector<IGameObject2D *> settingsElements);
};

#endif //BOMBERMAN_MAINMENU_HPP
