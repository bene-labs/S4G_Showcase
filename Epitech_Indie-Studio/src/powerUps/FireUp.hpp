//
// Created by oem on 6/17/21.
//

#ifndef BOMBERMAN_FIREUP_HPP
#define BOMBERMAN_FIREUP_HPP

#include "../IGameObject.hpp"
#include "../Rotation.hpp"
#include "../Cube.hpp"
#include <chrono>

class FireUp : public Cube {
    public:

    FireUp(float x, float z);

    FireUp(void *mem);

    void update(std::list<IGameObject *> *objects) override;
    void draw() override;
    void * get_memory_to_store() override;

    Model model;
    Rotation rotation;
};

#endif //BOMBERMAN_FireUp_HPP
