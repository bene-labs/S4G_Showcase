/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/
#ifndef BOMBERMAN_IGAMEOBJECT2D_HPP
#define BOMBERMAN_IGAMEOBJECT2D_HPP

#include <raylib.h>

class IGameObject2D {
    public:

    virtual void draw() = 0;
    virtual int update() = 0;

    Vector2 _position = {0, 0};
    Vector2 _size = {1, 1};
    protected:
};

#endif //BOMBERMAN_IGAMEOBJECT2D_HPP
