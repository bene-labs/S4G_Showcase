/*
** EPITECH PROJECT, 2024
** B_OOP_400_BER_4_1_arcade_emile_hanau
** File description:
** Created by benedikt,
*/

#ifndef B_OOP_400_BER_4_1_ARCADE_EMILE_HANAU_GAME_HPP
#define B_OOP_400_BER_4_1_ARCADE_EMILE_HANAU_GAME_HPP

#include "../../../lib_include/game_interface.hpp"
#include <vector>
#include "snake.hpp"
#include "snakeSegments.hpp"
#include "apple.hpp"

#include <chrono>
#include <iostream>
#include <fstream>

class Game : public IGame {
    public:
    Game(IGraphics *lib);

    void start_game() override;
    std::string game_tick() override;
    bool is_running() override;
    void use_graphics_lib(IGraphics *lib) override;
    void reload_all_objects() override;

    private:

    void loadHighScore();
    void handleGameOver();
    void loadUserName();
    std::chrono::steady_clock::time_point last_call_time = std::chrono::steady_clock::now();
    double min_frame_delay = 0.42;

    std::string last_key_pressed = "";

    int score = 0;
    int oldHighScore = 0;
    int highScore = 0;
    int level = 1;
    std::string userName = "Nobody";


    Snake snake;
    Apple *apples;

    bool isRunning = false;

    void *scoreHeadlineText;
    void *scoreText;
    void *highScoreHeadlineText;
    void *highScoreText;

    object_creation_data appleCreationData = {\
object_type::SPRITE, "*", "lib/nibbler/resources/apple.png", "red"};

    object_creation_data snakeSpriteData[4][4] = {
    {{object_type::SPRITE, "<",
        "lib/nibbler/resources/head/left.png", "green"},
        {object_type::SPRITE, "^",
            "lib/nibbler/resources/head/up.png", "green"},
        {object_type::SPRITE, ">",
            "lib/nibbler/resources/head/right.png", "green"},
        {object_type::SPRITE, "v",
            "lib/nibbler/resources/head/down.png", "green"}, },
    {{object_type::SPRITE, "=",
        "lib/nibbler/resources/body/left.png", "green"},
        {object_type::SPRITE, "|",
            "lib/nibbler/resources/body/up.png", "green"},
        {object_type::SPRITE, "=",
            "lib/nibbler/resources/body/right.png", "green"},
        {object_type::SPRITE, "|",
            "lib/nibbler/resources/body/down.png", "green"},},
        {{object_type::SPRITE, "/",
            "lib/nibbler/resources/corner/1.png", "green"},
            {object_type::SPRITE, "\\",
                "lib/nibbler/resources/corner/2.png", "green"},
            {object_type::SPRITE, "\\",
                "lib/nibbler/resources/corner/3.png", "green"},
            {object_type::SPRITE, "/",
                "lib/nibbler/resources/corner/4.png", "green"}, },
    {{object_type::SPRITE, "D",
        "lib/nibbler/resources/tail/left.png", "green"},
        {object_type::SPRITE, "u",
            "lib/nibbler/resources/tail/up.png", "green"},
        {object_type::SPRITE, "C",
            "lib/nibbler/resources/tail/right.png", "green"},
        {object_type::SPRITE, "n",
            "lib/nibbler/resources/tail/down.png", "green"},}
    };
};

#endif //B_OOP_400_BER_4_1_ARCADE_EMILE_HANAU_GAME_HPP
