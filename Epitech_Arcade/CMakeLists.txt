cmake_minimum_required(VERSION 3.17)
project(arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)

add_library(arcade_sfml SHARED lib/sfml/library.cpp lib/sfml/library.hpp)
# add_library(arcade_sdl2 SHARED lib/sfml/library.cpp lib/sfml/library.hpp)
add_library(arcade_ncurses SHARED lib/ncurses/library.cpp lib/ncurses/library.hpp)
add_library(arcade_nibbler SHARED lib/nibbler/src/game.cpp lib/nibbler/src/snake.cpp lib/nibbler/src/snakeSegments.cpp lib/nibbler/src/apple.cpp lib/nibbler/include/game.hpp lib/nibbler/include/apple.hpp lib/nibbler/include/snake.hpp lib/nibbler/include/snakeSegments.hpp)
# add_library(arcade_toto SHARED lib/toto/library.cpp lib/toto/library.hpp)
add_library(arcade_centipede SHARED lib/centipede/game.cpp lib/centipede/game.hpp lib/centipede/centipedeSegments.cpp lib/centipede/centipedeSegments.hpp lib/centipede/centipede.cpp lib/centipede/centipede.hpp lib/centipede/box.cpp lib/centipede/box.hpp lib/centipede/ship.cpp lib/centipede/ship.hpp)

target_link_libraries(arcade_sfml sfml-window sfml-graphics sfml-audio sfml-system m)
target_link_libraries(arcade_ncurses ncurses)

set_target_properties(arcade_sfml PROPERTIES PREFIX "")
# set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")
set_target_properties(arcade_ncurses PROPERTIES PREFIX "")
set_target_properties(arcade_nibbler PROPERTIES PREFIX "")
set_target_properties(arcade_centipede PROPERTIES PREFIX "")
# set_target_properties(arcade_toto PROPERTIES PREFIX "")

link_libraries(dl)
add_executable(arcade core/main.cpp core/menu.cpp  core/menu.hpp core/selectable.cpp  core/selectable.hpp core/lib_handler.hpp core/core.cpp core/core.hpp)