//
// Created by oem on 6/17/21.
//

#ifndef BOMBERMAN_WALLWASS_HPP
#define BOMBERMAN_WALLPASS_HPP

#include "../IGameObject.hpp"
#include "../Rotation.hpp"
    #include "../Cube.hpp"

class WallPass : public Cube {
    public:

    WallPass(float x, float z);

    WallPass(void *mem);

    void update(std::list<IGameObject *> *objects) override;
    void draw() override;
    void * get_memory_to_store() override;

    Model model;
    Rotation rotation;
};

#endif //BOMBERMAN_WallPass_HPP
