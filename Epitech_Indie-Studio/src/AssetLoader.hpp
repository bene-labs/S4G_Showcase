/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#ifndef BOMBERMAN_ASSETLOADER_HPP
#define BOMBERMAN_ASSETLOADER_HPP

#include "IGameObject.hpp"
#include <vector>

std::vector<Model> loadAnimation(const char *animationFramesBasePath, int frames);

class AssetLoader {
    public:
    AssetLoader();
    void loadAssets();

    std::vector<std::vector<Model>> getNeededModels(IGameObject *assignTo);

    private:

    //Bomb
    Model _explosionModel;
    std::vector<Model> _framesBomb;
    bool assetsLoaded = false;

    //Player
    std::vector<std::vector<Model>> playerAnimations;
};

#endif //BOMBERMAN_ASSETLOADER_HPP
