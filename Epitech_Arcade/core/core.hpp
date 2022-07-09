//
// Created by oem on 4/11/21.
//

#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

void check_arguments(int argc);
void handle_key_events(IGraphics *(*createLib)(), IGame *(*createGame)(IGraphics *), Menu *menu, const std::string &tick, IGraphics *&game_gfx, IGame *&game);
void core_loop(IGraphics *(*createLib)(), IGraphics *game_gfx, IGame *(*createGame)(IGraphics *), IGame *game, Menu *menu, std::string &last_pressed_key, std::string &last_key_from_gfx);

#endif //ARCADE_CORE_HPP
