/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#include "Text.hpp"

#include <utility>


Text::Text(Font font, Vector2 position, Vector2 size, std::string content, Color color,
    float spacing
)
{
    _position = position;
    _font = font;
    text = std::move(content);
    _color = color;

    _size = size;
    _sizeText = size.x;
    _spacing = spacing;

    _textRect = {position.x, position.y, _size.x, _size.y};
    autoResizeText();
}

Text::Text(Font font, Rectangle placeInto, std::string content,
    Color color, float spacing)
{
    _font = font;
    text = std::move(content);
    _color = color;

    _size = {placeInto.width, placeInto.height};
    _sizeText = placeInto.width;
    _spacing = spacing;

    _textRect = placeInto;
    autoResizeText();
}


Text::Text(Font font, Vector2 position, Vector2 size, std::string content, Rectangle limit, Color color, float spacing)
{
    _position = position;
    _font = font;
    text = std::move(content);

    _size = size;
    _sizeText = size.x;
    _spacing = spacing;

    for (Vector2 curTextBoxSize = MeasureTextEx(_font, text.c_str(), _sizeText, _spacing); \
curTextBoxSize.x > size.x || curTextBoxSize.y > size.y; _sizeText -= 1) {
        curTextBoxSize = MeasureTextEx(_font, text.c_str(), _sizeText, _spacing);
    }
    _textRect = limit;
    useRect = true;
}

void Text::draw()
{
    if (!useRect) {
        DrawTextEx(_font, text.c_str(), _position, _sizeText, _spacing,_color);
    } else {
        DrawTextRec(_font, text.c_str(), _textRect, _sizeText, _spacing, true, _color);
    }
}

int Text::update()
{
    /*
    _textRect.y = _position.y;
    _textRect.x = _position.x;*/
    return 0;
}

void Text::autoResizeText()
{
    _sizeText = _textRect.width;

    Vector2 curTextBoxSize = MeasureTextEx(_font, text.c_str(), _sizeText, _spacing);
    for (; (curTextBoxSize.x > _textRect.width || curTextBoxSize.y > _textRect.height); _sizeText -= 1) {
        curTextBoxSize = MeasureTextEx(_font, text.c_str(), _sizeText, _spacing);
    }
    _size = curTextBoxSize;

    _position.x = _textRect.x + ((_textRect.width - _size.x) / 2);
    _position.y = _textRect.y + ((_textRect.height - _size.y) / 2);
}

void Text::replaceText(std::string newText, Color newColor)
{
    if (newColor.a != 0)
        _color = newColor;
    text = newText;
    autoResizeText();
}
