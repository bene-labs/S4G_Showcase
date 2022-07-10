//
// Created by oem on 6/17/21.
//

#ifndef BOMBERMAN_CHEST_HPP
#define BOMBERMAN_CHEST_HPP

#include "Cube.hpp"

class Chest : public Cube {

    void update(std::list<IGameObject *> *objects) override;
    void * get_memory_to_store() override;

    public:
    Chest(float x, float z);

    Chest(void *mem);
};

#endif //BOMBERMAN_CHEST_HPP
