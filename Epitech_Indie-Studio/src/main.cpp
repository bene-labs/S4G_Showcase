#include <iostream>
#include "raylib.h"
#include "Game.hpp"
#include "PlayerConfigs.hpp"
#include "2D/MainMenu.hpp"

bool collides_object_point(IGameObject *obj, Vector2 pt) {
    auto x0 = obj->transform.translation.x - obj->collision_cube_width / 2;
    auto z0 = obj->transform.translation.z - obj->collision_cube_width / 2;

    auto x1 = x0 + obj->collision_cube_width;
    auto z1 = z0 + obj->collision_cube_width;

    if (x0 <= pt.x && pt.x <= x1 && z0 <= pt.y && pt.y <= z1)
        return true;
    return false;
}

bool collides_object_object(IGameObject *obj1, IGameObject *obj2) {
    Vector2 mid1 = {obj1->transform.translation.x, obj1->transform.translation.z};
    Vector2 mid2 = {obj2->transform.translation.x, obj2->transform.translation.z};

    Rectangle r1 = {mid1.x - obj1->collision_cube_width / 2, mid1.y - obj1->collision_cube_width / 2, obj1->collision_cube_width, obj1->collision_cube_width};
    Rectangle r2 = {mid2.x - obj2->collision_cube_width / 2, mid2.y - obj2->collision_cube_width / 2, obj2->collision_cube_width, obj2->collision_cube_width};

    return CheckCollisionRecs(r1, r2);
}

int main()
{
    PlayerConfigs playerConfigs;
    playerConfigs.loadFromFile();

    InitWindow(playerConfigs.settings[SCREEN_WIDTH], playerConfigs.settings[SCREEN_HEIGHT], "bomberman");
    InitAudioDevice();
    SetExitKey(KEY_F4);

    MainMenu menu(playerConfigs);

    menu.display_all();
    Game game;

    menu.menuState = START;
    menu.run(&game);

    return 0;
}
