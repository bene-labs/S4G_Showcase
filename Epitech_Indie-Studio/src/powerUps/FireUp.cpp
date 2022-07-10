//
// Created by oem on 6/17/21.
//

#include <cstring>
#include "FireUp.hpp"
#include "raylib.h"
#include "../Game.hpp"
#include "../Player.hpp"

FireUp::FireUp(float x, float z
) : Cube(x, z, GREEN,GREEN,0.5f,true)
{
    this->transform.translation.x = x;
    this->transform.translation.z = z;
    this->transform.translation.y = 0.5;
    transform.scale = {1, 1, 1};
    destructable = true;
    collision_cube_width = 0.5;
    blocking = false;
    destructable = true;

    model = LoadModelFromMesh(GenMeshCylinder(0.3f, 0.25f, 10));

    name = "FireUp";
    type = "PowerUp";
}

FireUp::FireUp(void *mem
) : Cube(((memory_chunk_cube *) mem)->translation_x, ((memory_chunk_cube *) mem)->translation_z, GREEN,GREEN,0.5f,true)
{
    this->transform.translation.x = ((memory_chunk_cube *) mem)->translation_x;
    this->transform.translation.z = ((memory_chunk_cube *) mem)->translation_z;
    this->transform.translation.y = 0.5;
    destructable = true;
    collision_cube_width = 0.5;
    blocking = false;
    destructable = true;

    model = LoadModelFromMesh(GenMeshCylinder(0.3f, 0.25f, 10));
    name = "FireUp";
    type = "PowerUp";
}

void FireUp::draw()
{
   // DrawModel(model, {transform.translation.x, 0, transform.translation.z}, transform.scale.x, RED);
    DrawModelWiresEx(model, {transform.translation.x, 0, transform.translation.z}, {0, 1, 0}, rotation.getRotationAngle(), {1, 1, 1}, RED);
}

void FireUp::update(std::list<IGameObject *> *objects)
{
    rotation.rotate();
    for (auto object : *objects) {
        if (object != this && collides_object_object(this, object) && object->name == "Player") {
            dynamic_cast<Player *>(object)->stats->increaseFire();
            to_be_removed = true;
        }
    }
    if (dying)
        to_be_removed = true;
}

void *FireUp::get_memory_to_store()
{
    auto res = (memory_chunk_cube *) Cube::get_memory_to_store();
    strcpy(res->name, "FireUp");
    return (void *) res;
}
