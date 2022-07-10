//
// Created by oem on 6/14/21.
//

#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP

#define LIFESPAN_MS 2000000 // 2 sec

#include <chrono>
#include "Cube.hpp"
#include "Player.hpp"
#include "AssetLoader.hpp"

class Bomb : public Cube {
    public:

    Bomb(float x, float z, int strength, Player *owner, AssetLoader assetLoader);

    typedef struct {
        int _strenth;
        int _owner_player_nb;
        std::chrono::high_resolution_clock::time_point timestamp_life;
        std::chrono::high_resolution_clock::time_point timespamp_pause;
        float cube_size;
        unsigned char color_face_r;
        unsigned char color_face_a;
        unsigned char color_face_g;
        unsigned char color_face_b;
        unsigned char color_edge_r;
        unsigned char color_edge_g;
        unsigned char color_edge_b;
        unsigned char color_edge_a;
        float translation_x;
        float translation_y;
        float translation_z;
        bool destructable;
    } memory_chunk_bomb;

    Bomb(void *mem,  AssetLoader assetLoader);

    void update(std::list<IGameObject *> *objects) override;
    void draw() override;
    unsigned long get_storage_size() override;
    void *get_memory_to_store() override;

    private:
    Sound explodeSound;

    int _strenth;
    std::chrono::high_resolution_clock::time_point timestamp_life = std::chrono::high_resolution_clock::now();
    int _owner_player_nb;

    std::vector<Model> _frames;
    Animation animation;

    Player *getOwnerByPlayerNb(std::list<IGameObject *> *objects, int nb);
    Model _explosionModel;
};

#endif //BOMBERMAN_BOMB_HPP
