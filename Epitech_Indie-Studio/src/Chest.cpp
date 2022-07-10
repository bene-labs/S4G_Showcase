//
// Created by oem on 6/17/21.
//

#include <cstring>
#include "Chest.hpp"
#include "powerUps/BombUp.hpp"
#include "powerUps/FireUp.hpp"
#include "powerUps/SpeedUp.hpp"
#include "powerUps/WallPass.hpp"

Chest::Chest(float x, float z) : Cube(x, z, DARKBROWN, YELLOW, 0.9f, true)
{
    name = "Chest";
    type = "Chest";
}

void Chest::update(std::list<IGameObject *> *objects)
{
    if (dying) {
        int multiplier_chest_to_powerups = 3; // 2 would mean a chance of 1/2 to get a powerup
        int nb_of_types_of_powerups = 4; // TODO: inc to nb of implemented powerups
        auto type = rand() % ((nb_of_types_of_powerups) * multiplier_chest_to_powerups);

        switch (type) {
        case 0:
            objects->push_front(new BombUp(transform.translation.x, transform.translation.z));
            break;
        case 1:
            objects->push_front(new FireUp(transform.translation.x, transform.translation.z));
            break;
        case 2:
            objects->push_front(new SpeedUp(transform.translation.x, transform.translation.z));
            break;
        case 3:
            objects->push_front(new WallPass(transform.translation.x, transform.translation.z));
            break;
        default:
            break;
        }
        to_be_removed = true;
    }
}

void * Chest::get_memory_to_store()
{
    auto res = (memory_chunk_cube *) Cube::get_memory_to_store();
    strcpy(res->name, "Chest");
    return (void *) res;
}

Chest::Chest(void *mem
) : Cube(((memory_chunk_cube *) mem)->translation_x, ((memory_chunk_cube *) mem)->translation_z, ((Cube::memory_chunk_cube *) mem)->color_face, ((Cube::memory_chunk_cube *) mem)->color_edge ,((memory_chunk_cube *) mem)->cube_size,((memory_chunk_cube *) mem)->destructable)
{
    name = "Chest";
}
