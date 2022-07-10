//
// Created by oem on 6/17/21.
//

#include <cstring>
#include "WallPass.hpp"
#include "raylib.h"
#include "../Game.hpp"
#include "../Player.hpp"

WallPass::WallPass(float x, float z
) : Cube(x, z,GREEN,GREEN,0.5f,true)
{
    this->transform.translation.x = x;
    this->transform.translation.z = z;
    this->transform.translation.y = 0.5;
    destructable = true;
    collision_cube_width = 0.5;
    blocking = false;
    destructable = true;

    model = LoadModelFromMesh((GenMeshHemiSphere(0.6, 16, 10)));
    name = "WallPass";
    type = "PowerUp";
}

WallPass::WallPass(void *mem
) : Cube(((memory_chunk_cube *) mem)->translation_x, ((memory_chunk_cube *) mem)->translation_z, GREEN,GREEN,0.5f,true)
{
    this->transform.translation.x = ((memory_chunk_cube *) mem)->translation_x;
    this->transform.translation.z = ((memory_chunk_cube *) mem)->translation_z;
    this->transform.translation.y = 0.5;
    destructable = true;
    collision_cube_width = 0.5;
    blocking = false;
    destructable = true;
    model = LoadModelFromMesh((GenMeshHemiSphere(0.6, 16, 10)));
    name = "WallPass";
    type = "PowerUp";
}

void WallPass::draw()
{
    //DrawModel(model, {transform.translation.x, 0, transform.translation.z}, transform.scale.x, PURPLE);
    DrawModelWiresEx(model, {transform.translation.x, 0, transform.translation.z}, {0, 1, 0}, rotation.getRotationAngle(), {1, 1, 1}, DARKPURPLE);

}

void WallPass::update(std::list<IGameObject *> *objects)
{
    rotation.rotate();
    for (auto object : *objects) {
        if (object != this && collides_object_object(this, object) && object->name == "Player") {
            ((Player *)object)->stats->enableWallPass();
            to_be_removed = true;
        }
    }
    if (dying)
        to_be_removed = true;
}

void *WallPass::get_memory_to_store()
{
    auto res = (memory_chunk_cube *) Cube::get_memory_to_store();
    strcpy(res->name, "WallPass");
    return (void *) res;
}
