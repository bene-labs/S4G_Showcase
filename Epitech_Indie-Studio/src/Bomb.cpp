//
// Created by oem on 6/14/21.
//

#include <cmath>
#include <utility>
#include "Bomb.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "ExplosionParticle.hpp"
#include "PlayerConfigs.hpp"

Bomb::Bomb(float x, float z, int strength, Player *owner,  AssetLoader assetLoader)
    : Cube((float) (ceil(x) - (1.0f - (0.7f / 2)) - 0.5 + 1),(float) (ceil(z) - (1.0f - (0.7f / 2)) - 0.5 + 1), RED,BLACK,0.7f / 2, true)
{
    name = "Bomb";
    type = "Hazard";

    explodeSound = LoadSound("resources/sounds/bomb_explosion.ogg");
    SetSoundVolume(explodeSound, (float) PlayerConfigs::settings[VOLUME_SOUND] / 100);

    transform.scale = {0.8, 0.8, 0.8};
    transform.translation = {x, 0.5f, z};
    cubePosition = transform.translation;
    _owner_player_nb = owner->playerNB;
    owner->stats->decreaseBombs();
    collision_cube_width = 0;
    _strenth = strength;
    _owner_player_nb = owner->playerNB;

    std::vector<std::vector<Model>> models = assetLoader.getNeededModels(this);
    if (models.size() == 2 && models[0].size() == 30) {
        _frames = models[0];
        _explosionModel = models[1][0];
    } else {
        fprintf(stderr, "Unable to load essential bomb models!\n");
        exit(84);
    }
    animation.assignNewAnimation(30, LIFESPAN_MS / 7 / 15, IDLE);

}

Player *Bomb::getOwnerByPlayerNb(std::list<IGameObject *> *objects, int nb) {
    for (auto obj : *objects)
        if (obj->name == "Player" && ((Player *) obj)->playerNB == nb)
            return (Player *) obj;
    return nullptr;
}

void Bomb::update(std::list<IGameObject *> *objects)
{
    animation.update(PULSE);

    auto now = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::microseconds > (now - timestamp_life).count() > LIFESPAN_MS) {
        PlaySound(explodeSound);
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 ^ j == 0) {
                    bool direction_collided = false;
                    for (int off = 0; !direction_collided && off <= _strenth; off++) {
                        Vector2 curr_pos = {transform.translation.x + i * off,
                            transform.translation.z + j * off};
                        objects->push_front(
                            new ExplosionParticle(floor(curr_pos.x) + 0.5, floor(curr_pos.y) + 0.5, _explosionModel));
                        for (auto & object : *objects) {
                            if (object->dying && object->name == "Player")
                                continue;
                            if (object != objects->front() && collides_object_object(object, objects->front())) {
                                if (object->destructable) {
                                    object->dying = true;
                                }
                                else objects->pop_front();
                                if (object->blocking && object->name != "Player") {
                                    direction_collided = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        to_be_removed = true;
        if (nullptr != getOwnerByPlayerNb(objects, _owner_player_nb))
            getOwnerByPlayerNb(objects, _owner_player_nb)->stats->increaseBombs();
    }
}

void Bomb::draw()
{
    DrawModel(_frames[animation.getFrame()], transform.translation, transform.scale.x, WHITE);
}

unsigned long Bomb::get_storage_size()
{
    return sizeof(memory_chunk_bomb);
}

void *Bomb::get_memory_to_store()
{
    auto res = new memory_chunk_bomb;
    res->_owner_player_nb = this->_owner_player_nb;
    res->timestamp_life = timestamp_life;
    res->_strenth = this->_strenth;
    res->timespamp_pause = std::chrono::high_resolution_clock::now();
    res->cube_size = this->cube_size;
    res->translation_x = this->transform.translation.x;
    res->translation_y = this->transform.translation.y;
    res->translation_z = this->transform.translation.z;
    res->color_face_r = this->color_face.r;
    res->color_face_g = this->color_face.g;
    res->color_face_b = this->color_face.b;
    res->color_face_a = this->color_face.a;
    res->color_edge_a = this->color_edge.a;
    res->color_edge_r = this->color_edge.r;
    res->color_edge_g = this->color_edge.g;
    res->color_edge_b = this->color_edge.b;
    return (void *) res;
}

Bomb::Bomb(void *mem,  AssetLoader assetLoader) : Cube(mem)
{
    auto memory = (memory_chunk_bomb *) mem;

    explodeSound = LoadSound("resources/sounds/bomb_explosion.ogg");
    this->_owner_player_nb = memory->_owner_player_nb;
    this->timestamp_life = std::chrono::high_resolution_clock::now() - (memory->timespamp_pause - memory->timestamp_life);
    this->_strenth = memory->_strenth;
    this->cube_size = memory->cube_size;

    name = "Bomb";

    transform.translation.x = memory->translation_x;
    transform.translation.y = memory->translation_y;
    transform.translation.z = memory->translation_z;;
    transform.scale = {memory->cube_size, memory->cube_size, memory->cube_size};
    transform.rotation = {0, 0, 0};

    this->destructable = memory->destructable;
    cube_size = memory->cube_size;
    cubePosition = { transform.translation.x - (1.0f - cube_size) / 2, (1.0f - cube_size) / 2, transform.translation.z - (1.0f - cube_size) / 2};
    collision_cube_width = memory->cube_size;
    this->color_edge = ColorFromNormalized({255.0f / memory->color_edge_r, 255.0f / memory->color_edge_g, 255.0f / memory->color_edge_b, 255.0f / memory->color_edge_a});
    this->color_face = ColorFromNormalized({255.0f / memory->color_face_r, 255.0f / memory->color_face_g, 255.0f / memory->color_face_b, 255.0f / memory->color_face_a});

    transform.scale = {0.8, 0.8, 0.8};
    collision_cube_width = 0;
    _strenth = memory->_strenth;
    _owner_player_nb = memory->_owner_player_nb;


    std::vector<std::vector<Model>> models = assetLoader.getNeededModels(this);
    if (models.size() == 2 && models[0].size() == 30) {
        _frames = models[0];
        _explosionModel = models[1][0];
    } else {
        fprintf(stderr, "Unable to load essential bomb models!\n");
        exit(84);
    }
    int bombFrameCount = 30;
    animation.assignNewAnimation(30, LIFESPAN_MS / 7 / 15, IDLE);
}
