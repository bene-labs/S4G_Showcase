#include <string>
#include "menu.hpp"

void core_loop(IGraphics *(*createLib)(), IGraphics *game_gfx,
    IGame *(*createGame)(IGraphics *), IGame *game, Menu *menu,
    std::string &last_pressed_key, std::string &last_key_from_gfx
);

void handle_key_events(IGraphics *(*createLib)(),
    IGame *(*createGame)(IGraphics *), Menu *menu, const std::string &tick,
    IGraphics *&game_gfx, IGame *&game
);

void check_arguments(int argc);

void core_loop(IGraphics *(*createLib)(), IGraphics *game_gfx,
    IGame *(*createGame)(IGraphics *), IGame *game, Menu *menu,
    std::string &last_pressed_key, std::string &last_key_from_gfx
)
{
    while (last_pressed_key != "esc" && last_pressed_key != "exit") {
        last_key_from_gfx = menu->getActiveGraphicsLib()->getPressedKey();
        if (!last_key_from_gfx.empty())
            last_pressed_key = last_key_from_gfx;
        if (menu->handleInput(last_pressed_key)) {
            menu->setState(false);
            Lib new_gfx_lib(menu->getSelectedLib());
            createLib = (IGraphics *(*)()) new_gfx_lib.loadFunc("create_graphics");
            game_gfx = createLib();
            Lib new_game_lib(menu->getSelectedGame());
            createGame = (IGame *(*)(IGraphics *)) new_game_lib.loadFunc("create_game");
            game = createGame(game_gfx);
            game->start_game();
        }
        if (!menu->isNewFrame())
            continue;
        menu->display();


        for (; !menu->isActive() && game->is_running();) {
            std::string tick = "";
            tick = game->game_tick();
            if ("exit" == tick)
                break;
            if (tick == "x") {
                game_gfx->destroy_screen();
                delete menu;
                exit(0);
            }
            handle_key_events(createLib, createGame, menu, tick, game_gfx,
                game);
        }
        menu->setState(true);
    }
}

void handle_key_events(IGraphics *(*createLib)(),
    IGame *(*createGame)(IGraphics *), Menu *menu, const std::string &tick,
    IGraphics *&game_gfx, IGame *&game
)
{
    if (tick == "r") {
        game_gfx->destroy_screen();
        Lib new_gfx_lib(menu->getSelectedLib());
        createLib = (IGraphics *(*)()) new_gfx_lib.loadFunc("create_graphics");
        game_gfx = createLib();
        Lib new_game_lib(menu->getSelectedGame());
        createGame = (IGame *(*)(IGraphics *)) new_game_lib.loadFunc("create_game");
        game = createGame(game_gfx);
        game->start_game();
    } else if (tick == "1") {
        if (menu->selectPrevGame()) {
          game_gfx->destroy_screen();
          Lib new_gfx_lib(menu->getSelectedLib());
          createLib = (IGraphics *(*)()) new_gfx_lib.loadFunc("create_graphics");
          game_gfx = createLib();
          Lib new_game_lib(menu->getSelectedGame());
          createGame = (IGame *(*)(IGraphics *)) new_game_lib.loadFunc("create_game");
          game = createGame(game_gfx);
          game->start_game();
      }
    } else if (tick == "2") {
        if (menu->selectNextGame()) {
            game_gfx->destroy_screen();
            Lib new_gfx_lib(menu->getSelectedLib());
            createLib = (IGraphics *(*)())new_gfx_lib.loadFunc(
                "create_graphics");
            game_gfx = createLib();
            Lib new_game_lib(menu->getSelectedGame());
            createGame = (IGame *(*)(IGraphics *))new_game_lib.loadFunc(
                "create_game");
            game = createGame(game_gfx);
            game->start_game();
        }
    } else if (tick == "3") {
        if (menu->selectPrevLib()) {
            game_gfx->destroy_screen(); //todo: delete lib and destroy the screen in it's destructor instead
            Lib new_gfx_lib(menu->getSelectedLib());
            createLib = (IGraphics *(*)()) new_gfx_lib.loadFunc("create_graphics");
            game_gfx = createLib();
            game->use_graphics_lib(game_gfx);
            game->reload_all_objects();
        }
    } else if (tick == "4") {
        if (menu->selectNextLib()) {
            game_gfx->destroy_screen();
            Lib new_gfx_lib(menu->getSelectedLib());
            createLib = (IGraphics *(*)()) new_gfx_lib.loadFunc("create_graphics");
            game_gfx = createLib();
            game->use_graphics_lib(game_gfx);
            game->reload_all_objects();
        }
    }
}

void check_arguments(int argc)
{
    if (argc != 2) {
        std::cout << "USAGE:" << std::endl
                  << "./arcade [path to dynamic intermediate graphical lib]" << std::endl;
        exit(84);
    }
}