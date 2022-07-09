#ifndef SFML_LIBRARY_HPP
#define SFML_LIBRARY_HPP

#include "../../lib_include/gfx_interface.hpp"
#include "../../lib_include/game_interface.hpp"
#include <SFML/Graphics.hpp>

#include <string>
#include <map>

class Game : public IGame {
    public:
    Game(IGraphics *pGfx);

    void start_game() override;
    std::string game_tick() override;
    bool is_running() override;
    void use_graphics_lib(IGraphics *lib) override;
    void reload_all_objects() override;
    private:
    object_creation_data obj_data = {RECT, "red", " ", ""};
    void *curr_obj;
};

extern "C" {
    __attribute__((constructor))
    void init();

    IGame *create_game(IGraphics *gfx_lib);

    __attribute__((destructor))
    void destroy();
};
#endif //SFML_LIBRARY_HPP
