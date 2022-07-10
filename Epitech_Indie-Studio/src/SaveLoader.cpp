//
// Created by oem on 6/20/21.
//

#include <fstream>
#include <cstring>
#include "SaveLoader.hpp"
#include "Cube.hpp"
#include "powerUps/FireUp.hpp"
#include "powerUps/BombUp.hpp"
#include "powerUps/SpeedUp.hpp"
#include "powerUps/WallPass.hpp"
#include "Bomb.hpp"
#include "Chest.hpp"

void SaveLoader::save(std::list<IGameObject *> *objects)
{
    FILE * save= fopen(".save", "wb");

    for (auto obj : *objects) {
        if (obj->name == "ExplosionParticle")
            continue;
        /*if (obj->name == "Bomb")
            continue;*/
        fwrite((const char *) obj->name.c_str(), sizeof (char) * 80, 1, save);
        auto mem = obj->get_memory_to_store();
        if (mem != nullptr)
            fwrite((const char *) mem, obj->get_storage_size(), 1, save);
        delete mem;
    }
    fwrite((const char *) "END", sizeof (char) * 80, 1, save);
    fclose(save);
}

std::list<IGameObject *> *SaveLoader::load(AssetLoader assetLoader)
{
    auto objects = new std::list<IGameObject *>();
    FILE *save = fopen(".save", "rb");
    char buffer[80];
    fread(buffer, sizeof (char) * 80, 1, save);

    int bombFrameCount = 30;
    auto _frames = getModelFramesFromFile("resources/models/bomberman/Bomb/bomb", &bombFrameCount);
    Texture bombTexture = LoadTexture("resources/models/bomberman/Bomb/textures/Bomb.png");
    for (auto frame : _frames) {
        frame.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = bombTexture;
    }

    int counter = 0;
    while (strcmp(buffer, "END")) {
        counter++;
        auto name = std::string(buffer);
        if (name == "Cube") {
            Cube::memory_chunk_cube mem;
            fread((char *) &mem, sizeof (Cube::memory_chunk_cube), 1, save);
            objects->push_back(new Cube(&mem));
        }
        else if (name == "FireUp") {
            Cube::memory_chunk_cube mem;
            fread((char *) &mem, sizeof (Cube::memory_chunk_cube), 1, save);
            objects->push_back(new FireUp(&mem));
        }
        else if (name == "BombUp") {
            Cube::memory_chunk_cube mem;
            fread((char *) &mem, sizeof (Cube::memory_chunk_cube), 1, save);
            objects->push_back(new BombUp(&mem));
        }
        else if (name == "SpeedUp") {
            Cube::memory_chunk_cube mem;
            fread((char *) &mem, sizeof (Cube::memory_chunk_cube), 1, save);
            objects->push_back(new SpeedUp(&mem));
        }
        else if (name == "WallPass") {
            Cube::memory_chunk_cube mem;
            fread((char *) &mem, sizeof (Cube::memory_chunk_cube), 1, save);
            objects->push_back(new WallPass(&mem));
        }
        else if (name == "Bomb") {
            Bomb::memory_chunk_bomb mem;
            fread((char *) &mem, sizeof (Bomb::memory_chunk_bomb), 1, save);
            objects->push_back(new Bomb(&mem, assetLoader));
        }
        else if (name == "Chest") {
            Chest::memory_chunk_cube mem;
            fread((char *) &mem, sizeof (Chest::memory_chunk_cube), 1, save);
            objects->push_back(new Chest(&mem));
        }
        else if (name == "Player") {
            Player::memory_chunk_player mem;
            fread((char *) &mem, sizeof (Player::memory_chunk_player), 1, save);
            objects->push_back(new Player(&mem, assetLoader));
        }
        else
            std::cerr << "Error" << std::endl;
        if (fread(buffer, sizeof (char) * 80, 1, save) == 0)
            break;
    }
    fclose(save);
    remove(".save");
    return objects;
}
