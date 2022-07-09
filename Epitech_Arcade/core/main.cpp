#include "menu.hpp"
#include <string>
#include "core.hpp"

int main(int argc, char **argv)
{
    check_arguments(argc);
    Lib gfx_lib(argv[1]);
    auto createLib = (IGraphics *(*)()) gfx_lib.loadFunc("create_graphics");

    auto gfx = createLib();
    IGraphics *game_gfx;

    auto createGame = (IGame *(*)(IGraphics *)) nullptr;
    IGame *game = nullptr;

    Menu *menu = new Menu(gfx);
    menu->setState(true);

    std::vector<IGame *> games;
    std::string last_pressed_key = "";
    std::string last_key_from_gfx;

    core_loop(createLib, game_gfx, createGame, game, menu, last_pressed_key,
        last_key_from_gfx);
    gfx_lib.close_lib();
    delete menu;
    return 0;
}

