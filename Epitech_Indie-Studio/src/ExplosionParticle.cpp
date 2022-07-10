//
// Created by oem on 6/17/21.
//

#include <iostream>
#include "ExplosionParticle.hpp"

ExplosionParticle::ExplosionParticle(float x, float z, Model model)
{
    transform.translation = {x, 0, z};
    transform.scale = {0.9f, 0.9f, 0.9f};
    transform.rotation = {0, 0, 0};
    collision_cube_width = 0;

    _model = model;
}

void ExplosionParticle::update(std::list<IGameObject *> *objects)
{
    auto now = std::chrono::high_resolution_clock::now();

    long long microseconds_since_tick = std::chrono::duration_cast<std::chrono::microseconds>(now - timestamp_life).count();

    this->_scale = (float) (EXPLOSION_LIFESPAN - microseconds_since_tick) / EXPLOSION_LIFESPAN;
    if (_scale < 0.05)
        to_be_removed = true;
}

void ExplosionParticle::draw()
{
    DrawModel(_model, transform.translation, _scale, WHITE);
}

void *ExplosionParticle::get_memory_to_store()
{
    return nullptr;
}

unsigned long ExplosionParticle::get_storage_size()
{
    return 0;
}
