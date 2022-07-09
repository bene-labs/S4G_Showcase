/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Created by benedikt,
*/

#ifndef ARCADE_SELECTABLE_HPP
#define ARCADE_SELECTABLE_HPP

#include "../lib_include/gfx_interface.hpp"

class Selectable {
    public:
    Selectable(IGraphics *lib, std::string content, std::pair<int, int> position,
        int width = 100, int height = 30, std::string def_color = "white",  std::string active_color = "blue"
    );
    ~Selectable() = default;

    void draw();

    std::string getText();
    bool isActive();
    void toggleActive();
    void setText(std::string newText);
    void loadNewLib(IGraphics *lib);

    private:

    void *rectangle;
    void *text;
    std::string _def_color;
    std::string _active_color;
    std::pair<int, int> _position;
    IGraphics *_lib;

    bool _isActive = false;

    int _width;
    int _height;
    object_creation_data rectangle_data = {object_type::RECT, \
"", "", _def_color};
    object_creation_data text_data = {object_type::TEXT, \
"", "core/resources/Bebas-Regular.otf", "black"};


};
#endif //ARCADE_SELECTABLE_HPP
