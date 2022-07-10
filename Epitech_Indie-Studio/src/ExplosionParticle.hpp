//
// Created by oem on 6/17/21.
//

#ifndef BOMBERMAN_EXPLOSIONPARTICLE_HPP
#define BOMBERMAN_EXPLOSIONPARTICLE_HPP

#define EXPLOSION_LIFESPAN 500000

#include <chrono>
#include "Cube.hpp"

class ExplosionParticle : public IGameObject {
    public:
    ExplosionParticle(float x, float z, Model model);

    void update(std::list<IGameObject *> *objects) override;
    void draw() override;
    void * get_memory_to_store() override;

    unsigned long get_storage_size() override;

    private:
    Model _model;
    float _scale;
    std::chrono::high_resolution_clock::time_point timestamp_life = std::chrono::high_resolution_clock::now();
};

#endif //BOMBERMAN_EXPLOSIONPARTICLE_HPP
