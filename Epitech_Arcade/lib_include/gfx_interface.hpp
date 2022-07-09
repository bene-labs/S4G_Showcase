/*
** EPITECH PROJECT, 2024
** sfml
** File description:
** Created by benedikt,
*/

#ifndef SFML_GFX_INTERFACE_HPP
#define SFML_GFX_INTERFACE_HPP

#include <string>
#include <vector>

enum object_type
{
    TEXT,
    SPRITE,
    RECT
};

typedef struct object_creation_data {
    object_type type;
    std::string text;
    std::string path_to_resource;
    std::string color_name;
} object_creation_data;

class IGraphics
{
    public:
    virtual void init_screen(int width, int height) = 0;
    virtual ~IGraphics() = default;
    virtual void *createObject(object_creation_data *object_data) = 0;
    virtual void draw(void *object, int x0, int x1, int y0, int y1) = 0;
    virtual void deleteObject(void *object) = 0;
    virtual std::string getPressedKey(void) = 0;
    virtual void destroy_screen() = 0;
    virtual void display_screen() = 0;
    virtual void clear_screen() = 0;
    //    virtual std::vector<object_creation_data> getObjectData() = 0;
};

#endif //SFML_GFX_INTERFACE_HPP
