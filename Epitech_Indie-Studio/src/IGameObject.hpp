//
// Created by oem on 6/13/21.
//

#ifndef BOMBERMAN_IGAMEOBJECT_HPP
#define BOMBERMAN_IGAMEOBJECT_HPP

#include <list>
#include <string>
#include "raylib.h"

class IGameObject {
    public:

    virtual void draw() = 0;
    virtual void update(std::list<IGameObject *> *objects) = 0;
    virtual unsigned long get_storage_size() = 0;
    virtual void * get_memory_to_store() = 0;

    float collision_cube_width = 0; // 0 means the object has no collision

    Transform transform = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    std::string name = "undefined";
    std::string type = "object";

    bool to_be_removed = false;
    bool blocking = true;
    bool destructable = false;
    bool draw_faces = true;
    bool dying = false;
    bool alive = true;
    protected:
};

#endif //BOMBERMAN_IGAMEOBJECT_HPP
