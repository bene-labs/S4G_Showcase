//
// Created by oem on 6/13/21.
//

#include <iostream>
#include <cstring>
#include "Cube.hpp"

void Cube::draw()
{
    if (isSquareCube) {
        if (draw_faces)
            DrawCube(cubePosition, cube_size, cube_size, cube_size, color_face);
        DrawCubeWires(cubePosition, cube_size, cube_size, cube_size, color_edge);
    } else {
        if (draw_faces)
            DrawModelWires(cubeModel, transform.translation, 1, WHITE);
        DrawModel(cubeModel, transform.translation, 1, WHITE);
    }
}

// constructor called with floats will use floats as absolute position
Cube::Cube(float x, float z, Color color_face=GREEN, Color color_edge=BLUE, float width=0.9f, bool destructable=false)
{
    name = "Cube";
    type = "Obstacle";

    transform.translation = {x, 0, z};
    transform.scale = {width, width, width};
    transform.rotation = {0, 0, 0};

    this->destructable = destructable;
    cube_size = width;
    cubePosition = { x - (1.0f - cube_size) / 2, (1.0f - cube_size) / 2, z - (1.0f - cube_size) / 2};
    transform.translation = cubePosition;
    collision_cube_width = width;
    this->color_edge = color_edge;
    this->color_face = color_face;
}

void Cube::update(std::list<IGameObject *> *objects)
{
    if (dying)
        to_be_removed = true;
}

Cube::~Cube()
{
}

void *Cube::get_memory_to_store()
{
    auto *res = new memory_chunk_cube;
    strcpy(res->name, "Cube");
    res->cube_size = this->cube_size;
    res->translation_x = this->transform.translation.x;
    res->translation_y = this->transform.translation.y;
    res->translation_z = this->transform.translation.z;
    res->color_face = this->color_face;
    res->color_edge = this->color_edge;
    res->destructable = this->destructable;
    return (void *) res;
}

Cube::Cube(void *mem)
{
    auto memory = (memory_chunk_cube *) mem;
    name = "Cube";

    transform.translation.x = memory->translation_x;
    transform.translation.y = memory->translation_y;
    transform.translation.z = memory->translation_z;

    this->color_face = memory->color_face;
    this->color_edge = memory->color_edge;

    transform.scale = {memory->cube_size, memory->cube_size, memory->cube_size};
    transform.rotation = {0, 0, 0};

    this->destructable = memory->destructable;
    cube_size = memory->cube_size;
    cubePosition = {transform.translation.x - (1.0f - cube_size) / 2,
        (1.0f - cube_size) / 2,
        transform.translation.z - (1.0f - cube_size) / 2};
    collision_cube_width = memory->cube_size;
}


Cube::Cube(Vector3 position, Vector3 size, Texture texture, bool destructable)
{
    isSquareCube = false;

    name = "Cube";
    type = "Deco";

    draw_faces = false;
    transform.translation  = { position.x - (1.0f - size.x) / 2, position.y - (1.0f - size.y) / 2, position.z - (1.0f - size.z) / 2};
    transform.scale = size;
    transform.rotation = {0, 0, 0};
    cubeModel = LoadModelFromMesh(GenMeshCube(size.x, size.y, size.z));
    cubeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    this->destructable = destructable;
}
