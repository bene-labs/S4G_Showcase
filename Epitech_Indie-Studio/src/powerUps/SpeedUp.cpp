//
// Created by oem on 6/17/21.
//

#include <cstring>
#include "SpeedUp.hpp"
#include "raylib.h"
#include "../Game.hpp"
#include "../Player.hpp"

SpeedUp::SpeedUp(float x, float z
) : Cube(x, z, GREEN,GREEN,0.5f,true)
{
    this->transform.translation.x = x;
    this->transform.translation.z = z;
    this->transform.translation.y = 0.5;
    destructable = true;
    collision_cube_width = 0.5;
    blocking = false;
    destructable = true;

    model = LoadModelFromMesh(GenMeshTorus(0.23f, 0.65f, 10, 20));
    name = "SpeedUp";
    type = "PowerUp";
}

SpeedUp::SpeedUp(void *mem
) : Cube(((memory_chunk_cube *) mem)->translation_x, ((memory_chunk_cube *) mem)->translation_z, GREEN,GREEN,0.5f,true)
{
    this->transform.translation.x = ((memory_chunk_cube *) mem)->translation_x;
    this->transform.translation.z = ((memory_chunk_cube *) mem)->translation_z;
    this->transform.translation.y = 0.5;
    destructable = true;
    collision_cube_width = 0.5;
    blocking = false;
    destructable = true;
    model = LoadModelFromMesh(GenMeshTorus(0.23f, 0.65f, 10, 20));
    name = "SpeedUp";
    type = "PowerUp";
}

void SpeedUp::draw()
{
    //DrawModel(model, {transform.translation.x, 0, transform.translation.z}, transform.scale.x, YELLOW);
    DrawModelWiresEx(model, {transform.translation.x, 0, transform.translation.z}, {0, 1, 0}, rotation.getRotationAngle(), {0.85, 0.85, 0.85}, GREEN);
}

void SpeedUp::update(std::list<IGameObject *> *objects)
{
    rotation.rotate();
    for (auto object : *objects) {
        if (object != this && collides_object_object(this, object) && object->name == "Player") {
            ((Player *)object)->stats->increaseSpeed();
            to_be_removed = true;
        }
    }
    if (dying)
        to_be_removed = true;
}

void *SpeedUp::get_memory_to_store()
{
    auto res = (memory_chunk_cube *) Cube::get_memory_to_store();
    strcpy(res->name, "SpeedUp");
    return (void *) res;
}
