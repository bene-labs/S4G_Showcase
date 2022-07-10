/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#include "AssetLoader.hpp"

std::vector<Model> loadAnimation(const char *animationFramesBasePath, int frames)
{
    char framePath[120] = {0};
    std::vector<Model> res;

    for (int i = 1; i <= frames; i++) {
        sprintf(framePath, "%s_%06d.obj", animationFramesBasePath, i);
        res.push_back(LoadModel(framePath));
    }
    return res;
}

std::vector<Model> getModelFramesFromFile(const char *animationFramesBasePath, int *frames)
{
    char framePath[120] = {0};
    std::vector<Model> res;

    for (int i = 1; i <= *frames; i++) {
        sprintf(framePath, "%s_%06d.obj", animationFramesBasePath, i);
        res.push_back(LoadModel(framePath));
    }
    *frames = res.size();
    return res;
};


AssetLoader::AssetLoader()
{
}


void AssetLoader::loadAssets()
{
    _explosionModel = LoadModel("resources/models/bomberman/Bomb/fire.obj");
    _explosionModel.materials[0].maps->texture = LoadTexture("resources/images/Fire.png");

    //Bomb
    int bombFrameCount = 30;
    _framesBomb = getModelFramesFromFile("resources/models/bomberman/Bomb/bomb", &bombFrameCount);
    Texture bombTexture = LoadTexture("resources/models/bomberman/Bomb/textures/Bomb.png");
    for (auto frame : _framesBomb) {
        frame.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = bombTexture;
    }

    //Player
    playerAnimations.push_back(loadAnimation("resources/models/bomberman/animations/run/short_run", 22));
    playerAnimations.push_back(loadAnimation("resources/models/bomberman/animations/idle/idle", 175));
    playerAnimations.push_back(loadAnimation("resources/models/bomberman/animations/die/death", 67));


    assetsLoaded = true;

}


std::vector<std::vector<Model>> AssetLoader::getNeededModels(IGameObject *assignTo)
{
    std::vector<std::vector<Model>> res;

    if (!assetsLoaded) return res;
    if (assignTo->name == "Bomb") {
        res.push_back(_framesBomb);
        res.push_back(std::vector<Model> {_explosionModel});
        return res;
    } else if (assignTo->name == "Player") {
        return playerAnimations;
    }

    return std::vector<std::vector<Model>>();
}