//
// Created by oem on 6/20/21.
//

#ifndef BOMBERMAN_SAVELOADER_HPP
#define BOMBERMAN_SAVELOADER_HPP

#include <list>
#include "IGameObject.hpp"
#include "AssetLoader.hpp"

class SaveLoader {
    public:

    void save(std::list<IGameObject *> *objects);
    std::list<IGameObject *> *load(AssetLoader assetLoader);
};

#endif //BOMBERMAN_SAVELOADER_HPP
