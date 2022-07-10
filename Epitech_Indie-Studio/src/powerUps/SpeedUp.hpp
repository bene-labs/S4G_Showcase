//
// Created by oem on 6/17/21.
//

#ifndef BOMBERMAN_SPEEDUP_HPP
#define BOMBERMAN_SPEEDUP_HPP

#include "../IGameObject.hpp"
#include "../Rotation.hpp"
#include "../Cube.hpp"

class SpeedUp : public Cube {
    public:

    SpeedUp(float x, float z);

    SpeedUp(void *mem);

    void update(std::list<IGameObject *> *objects) override;
    void draw() override;
    void * get_memory_to_store() override;

    Model model;
    Rotation rotation;
};

#endif //BOMBERMAN_SpeedUp_HPP
