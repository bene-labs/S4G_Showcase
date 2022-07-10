//
// Created by oem on 6/17/21.
//

#ifndef BOMBERMAN_BOMBUP_HPP
#define BOMBERMAN_BOMBUP_HPP

#include "../IGameObject.hpp"
#include "../Rotation.hpp"
#include "../Cube.hpp"

class BombUp : public Cube {
    public:

    BombUp(void *);

    BombUp(float x, float z);

    void update(std::list<IGameObject *> *objects) override;
    void draw() override;
    void * get_memory_to_store() override;

    Model model;
    Rotation rotation;
};

#endif //BOMBERMAN_BOMBUP_HPP
