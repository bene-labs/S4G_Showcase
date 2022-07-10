//
// Created by oem on 6/17/21.
//

#include <cstring>
#include "BombUp.hpp"
#include "raylib.h"
#include "../Game.hpp"
#include "../Player.hpp"

BombUp::BombUp(float x, float z
) : Cube(x, z, GREEN,GREEN,0.5f,true)
{
    this->transform.translation.x = x;
    this->transform.translation.z = z;
    this->transform.translation.y = 0.5;
    destructable = true;
    collision_cube_width = 0.5;
    blocking = false;
    destructable = true;
    model = LoadModel("resources/models/bomberman/Bomb/bomb_000001.obj");

    name = "BombUp";
    type = "PowerUp";
}

BombUp::BombUp(void *mem
) : Cube(((memory_chunk_cube *) mem)->translation_x, ((memory_chunk_cube *) mem)->translation_z, GREEN,GREEN,0.5f,true)
{
    this->transform.translation.x = ((memory_chunk_cube *) mem)->translation_x;
    this->transform.translation.z = ((memory_chunk_cube *) mem)->translation_z;
    this->transform.translation.y = 0.5;
    destructable = true;
    collision_cube_width = 0.5;
    blocking = false;
    destructable = true;
    model = LoadModel("resources/models/bomberman/Bomb/bomb_000001.obj");

    name = "BombUp";
    type = "PowerUp";
}

void BombUp::draw()
{
    //DrawModel(model, {transform.translation.x, 0, transform.translation.z}, transform.scale.x, YELLOW);
    DrawModelWiresEx(model, {transform.translation.x, 0, transform.translation.z}, {0, 1, 0}, rotation.getRotationAngle(), {0.85, 0.85, 0.85}, {255, 192, 3, 255});

}

void BombUp::update(std::list<IGameObject *> *objects)
{
    rotation.rotate();
    for (auto object : *objects) {
        if (object != this && collides_object_object(this, object) && object->name == "Player") {
            ((Player *)object)->stats->increaseMaxBombs();
            to_be_removed = true;
        }
    }
    if (dying)
        to_be_removed = true;
}

void *BombUp::get_memory_to_store()
{
    auto res = (memory_chunk_cube *) Cube::get_memory_to_store();
    strcpy(res->name, "BombUp");
    return (void *) res;
}
