#include "library.hpp"


#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <math.h>

sf::RenderWindow *window;

extern "C" {
    __attribute__((constructor))
    void init() {// temp debug
    }

    IGame *create_game(IGraphics *gfx_lib) {
        return new Game(gfx_lib);
    }

    __attribute__((destructor))
    void destroy() {
    }
}

Game::Game(IGraphics *gfx_lib)
{
    lib = gfx_lib;
    curr_obj = lib->createObject(&obj_data);
}

void Game::start_game()
{
    lib->init_screen(600, 600);
    lib->clear_screen();
    object_creation_data obj_data;
    obj_data.type = RECT;
    obj_data.color_name = "red";
    obj_data.text = "toto";
    obj_data.path_to_resource = "";
    auto curr_obj = lib->createObject(&obj_data);
    lib->draw(curr_obj, 0,100,0,100);
}

std::string Game::game_tick()
{
    usleep(20);
    static float x = 0;
    static float y = 0;
    x += 0.01;
    if (x > 550)
        x = 0;
    lib->clear_screen();
    lib->draw(curr_obj, round(x), round(x) + 50, y, y+ 50);
    lib->display_screen();
    std::string res = lib->getPressedKey();
    if (res == "esc") {
        lib->destroy_screen();
        return ("exit");
    }
    return res;
}

bool Game::is_running()
{
    return true;
}

void Game::use_graphics_lib(IGraphics *gfx_lib)
{
    lib = gfx_lib;
}

void Game::reload_all_objects()
{
    curr_obj = lib->createObject(&obj_data);
}
