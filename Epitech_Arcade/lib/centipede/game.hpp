/*
** EPITECH PROJECT, 2024
** B_OOP_400_BER_4_1_arcade_emile_hanau
** File description:
** Created by benedikt,
*/

#ifndef B_OOP_400_BER_4_1_ARCADE_EMILE_HANAU_GAME_HPP
#define B_OOP_400_BER_4_1_ARCADE_EMILE_HANAU_GAME_HPP

#include "../../lib_include/game_interface.hpp"
#include <vector>
#include "centipede.hpp"
#include "centipedeSegments.hpp"
#include "box.hpp"
#include "ship.hpp"

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
    void computeProjectileCollisions();
    void handleGameOver();

    void spawnEnemies();
    void increaseLevel();

    private:
    void loadHighScore();
    void loadUserName();
    std::chrono::steady_clock::time_point last_call_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point last_spawn_time = std::chrono::steady_clock::now();
    double min_frame_delay = 0.1;

    std::string last_key_pressed = "";

    double enemySpawnDelay = 8.0;
    int _enemiesSpawned = 1;

    int score = 0;
    int oldHighScore = 0;
    int highScore = 0;
    int level = 1;
    std::string userName = "Nobody";
    Ship *ship;

    Centipedes centipede;
    Box *boxes;


    bool isRunning = false;

    void *scoreHeadlineText;
    void *scoreText;
    void *highScoreHeadlineText;
    void *highScoreText;
    void *levelText;

    object_creation_data centipedeSpriteData[4][4] = {
    {{object_type::SPRITE, "<",
        "lib/centipede/resources/head/left.png", "green"},
        {object_type::SPRITE, "^",
            "lib/centipede/resources/head/up.png", "green"},
        {object_type::SPRITE, ">",
            "lib/centipede/resources/head/right.png", "green"},
        {object_type::SPRITE, "v",
            "lib/centipede/resources/head/down.png", "green"}, },
    {{object_type::SPRITE, "=",
        "lib/centipede/resources/body/left.png", "green"},
        {object_type::SPRITE, "|",
            "lib/centipede/resources/body/up.png", "green"},
        {object_type::SPRITE, "=",
            "lib/centipede/resources/body/right.png", "green"},
        {object_type::SPRITE, "|",
            "lib/centipede/resources/body/down.png", "green"},},
        {{object_type::SPRITE, "/",
            "lib/centipede/resources/corner/1.png", "green"},
            {object_type::SPRITE, "\\",
                "lib/centipede/resources/corner/2.png", "green"},
            {object_type::SPRITE, "\\",
                "lib/centipede/resources/corner/3.png", "green"},
            {object_type::SPRITE, "/",
                "lib/centipede/resources/corner/4.png", "green"}, },
    {{object_type::SPRITE, "D",
        "lib/centipede/resources/tail/left.png", "green"},
        {object_type::SPRITE, "u",
            "lib/centipede/resources/tail/up.png", "green"},
        {object_type::SPRITE, "C",
            "lib/centipede/resources/tail/right.png", "green"},
        {object_type::SPRITE, "n",
            "lib/centipede/resources/tail/down.png", "green"},}
    };
};

#endif //B_OOP_400_BER_4_1_ARCADE_EMILE_HANAU_GAME_HPP
