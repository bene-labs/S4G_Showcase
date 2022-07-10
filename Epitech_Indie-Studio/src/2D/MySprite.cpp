/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#include "MySprite.hpp"

MySprite::MySprite(const char *filePath, Vector2 position, Vector2 size)
{
    _sprite = LoadTexture(filePath);
    _sprite.width = (int) size.x;
    _sprite.height = (int) size.y;
    _size = size;
    _position = position;
}

MySprite::MySprite(Texture2D texture, Vector2 position, Vector2 size)
{
    _sprite.id = texture.id;
    _sprite.format = texture.format;
    _sprite.mipmaps = texture.mipmaps;
    _sprite.width = (int) size.x;
    _sprite.height = (int) size.y;
    _size = {size.x, size.y};
    _position = position;
}



MySprite::~MySprite()
{
}

int MySprite::update()
{
    return 0;
}

void MySprite::draw()
{
    if (!useTextureRec)
        DrawTexture(_sprite, (int) _position.x, (int) _position.y, WHITE);
    else
        DrawTextureRec(_sprite, textureRec, _position, WHITE);
}

void MySprite::enableTextureRect(Rectangle toCutOut)
{
    textureRec = toCutOut;
    /*
    _size.x *=  (_size.x / textureRec.x);
    _size.y *=  (_size.y / textureRec.y);*/
    useTextureRec = true;
}
