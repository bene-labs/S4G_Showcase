/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#include "IGameObject2D.hpp"

#ifndef BOMBERMAN_SPRITE_HPP
#define BOMBERMAN_SPRITE_HPP

class MySprite : public IGameObject2D {

    public:
    MySprite(const char *filePath, Vector2 position, Vector2 size);
    MySprite(Texture2D texture, Vector2 position, Vector2 size);
    ~MySprite();

    void enableTextureRect(Rectangle toCutOut);

    int update() override;
    void draw() override;

    Texture2D _sprite;

    private:
    bool useTextureRec = false;
    Rectangle textureRec;
};

#endif //BOMBERMAN_SPRITE_HPP
