/*
** EPITECH PROJECT, 2024
** sfml
** File description:
** Created by benedikt,
*/

#ifndef SFML_GAME_INTERFACE_HPP
#define SFML_GAME_INTERFACE_HPP

#include "gfx_interface.hpp"

class IGame
{
    protected:
    IGraphics *lib;
    public:
    virtual void start_game() = 0;
    virtual std::string game_tick() = 0;
    virtual bool is_running() = 0;
    virtual void use_graphics_lib(IGraphics *lib) = 0;
    virtual ~IGame() = default;
    virtual void reload_all_objects() = 0;
};

#endif //SFML_GAME_INTERFACE_HPP
