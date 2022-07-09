/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Created by benedikt,
*/

#ifndef ARCADE_MENU_HPP
#define ARCADE_MENU_HPP

#include "selectable.hpp"
#include <vector>
#include <iostream>
#include <filesystem>
#include "lib_handler.hpp"
#include "../lib_include/game_interface.hpp"

class Menu {
    public:
    Menu(IGraphics *lib, int screen_width = 1200, int screen_height = 960);
    ~Menu();

    void loadGameSelection();
    void loadGraphicsSelection();
    void display();
    bool selectPrevGame();
    bool selectNextGame();
    bool selectPrevLib();
    bool selectNextLib();
    std::string getSelectedGame();
    std::string getSelectedLib();
    IGraphics *getActiveGraphicsLib();

    bool handleInput(std::string& last_pressed_key);
    void setState(bool active);
    bool isActive() const;
    bool isNewFrame();

    std::chrono::steady_clock::time_point last_call_time = std::chrono::steady_clock::now();
    double min_frame_delay = 0.1;
    void updateUserName(std::string& input);

    private:
    void useNextGraphicsLib();
    void usePrevGraphicsLib();
    void reloadObjects();

    IGraphics *_lib;
    std::vector<Selectable *> gameSelection;
    std::vector<Selectable *> graphicsSelection;
    std::vector<std::string> gameNames;
    std::vector<std::string> libNames;

    Selectable *inputField;
    bool _isActive = false;

    std::string prevInput;
    int _screen_height;
    int _screen_width;

    int selectedGame = 0;
    int selectedLib = 0;
    int totalGames = 0;
    int totalLibs = 0;

    void *highScoreText;
    object_creation_data highScoreTextData = {object_type::TEXT, \
"", "core/resources/Bebas-Regular.otf", "yellow"};
};

#endif //ARCADE_MENU_HPP
