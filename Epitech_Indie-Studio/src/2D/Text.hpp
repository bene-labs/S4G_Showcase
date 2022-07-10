/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#ifndef BOMBERMAN_TEXT_HPP
#define BOMBERMAN_TEXT_HPP

#include "../bomberman.hpp"
#include "IGameObject2D.hpp"

class Text : public IGameObject2D {
    public:
    Text(Font font, Vector2 position, Vector2 size, std::string content, Color color = BLACK,
        float spacing = 2.0f);
    Text(Font font, Rectangle placeInto, std::string content, Color color = BLACK,
        float spacing = 2.0f);
    Text(Font font, Vector2 position, Vector2 size, std::string content, Rectangle limit, Color color = BLACK, float spacing = 2.0f);
    ~Text() = default;

    void draw() override;
    int update() override;
    void autoResizeText();
    void replaceText(std::string newText, Color newColor = {0, 0, 0, 0});

    std::string text;
    Rectangle _textRect;

    private:

    Color  _color;
    float _sizeText;
    float _spacing;
    Font _font;
    bool useRect = false;

};

#endif //BOMBERMAN_TEXT_HPP
