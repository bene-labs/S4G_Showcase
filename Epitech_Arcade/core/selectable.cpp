/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Created by benedikt,
*/

#include "selectable.hpp"
#include <math.h>

#include <utility>

Selectable::Selectable(IGraphics *lib, std::string content,
    std::pair<int, int> position, int width, int height,
    std::string def_color, std::string active_color
) : _lib(lib), _position(std::move(position)), _width(width), _height(height),
_def_color(def_color), _active_color(active_color)
{
    rectangle_data.color_name = _def_color;
    rectangle = lib->createObject(&rectangle_data);

    text_data.text = content;
    text = lib->createObject(&text_data);
}

void Selectable::draw()
{
    int x = _position.first;
    int y = _position.second;

    _lib->draw(rectangle, x, x + _width, y, y + _height);
    _lib->draw(text, x + _width / 10, x + _width - _width / 10, \
y + _height / 10, y + _height - _height / 10);
}

bool Selectable::isActive()
{
    return _isActive;
}

void Selectable::toggleActive()
{
    _isActive = !_isActive;
    rectangle_data.color_name = _isActive ? _active_color : _def_color;
    _lib->deleteObject(rectangle);
    rectangle = _lib->createObject(&rectangle_data);
}

std::string Selectable::getText()
{
    return text_data.text;
}

void Selectable::setText(std::string newText)
{
    if (!_isActive)
        return;
    text_data.text = newText;
    _lib->deleteObject(text);
    text = _lib->createObject(&text_data);
}

void Selectable::loadNewLib(IGraphics *lib)
{
    _lib = lib;

    rectangle = _lib->createObject(&rectangle_data);
    text = _lib->createObject(&text_data);
}
