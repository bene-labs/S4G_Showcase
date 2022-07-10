cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(bomberman)
set(CMAKE_CXX_STANDARD 20)

# Set this to the minimal version you want to support
find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

    endif()

endif()


# replace tinyobj_loader_c.h content to fix/mod HASH_TABLE_DEFAULT_SIZE to what is needed
FILE(GLOB FIXED_OBJ_LOADER fixed_tinyobj_loader_c.h)
file(STRINGS ${FIXED_OBJ_LOADER} FIXED_OBJ_LOADER_STR NEWLINE_CONSUME)
file(WRITE _deps/raylib-src/src/external/tinyobj_loader_c.h ${FIXED_OBJ_LOADER_STR})


# This is the main part:

FILE(GLOB SRC_DIR src/*.cpp src/*.hpp src/2D/*.cpp src/2D/*.hpp)

add_executable(${PROJECT_NAME} ${SRC_DIR} src/Bomb.cpp src/Bomb.hpp src/ExplosionParticle.cpp src/ExplosionParticle.hpp src/Chest.cpp src/Chest.hpp src/powerUps/BombUp.cpp src/powerUps/BombUp.hpp src/powerUps/FireUp.cpp src/powerUps/FireUp.hpp src/powerUps/SpeedUp.cpp src/powerUps/SpeedUp.hpp src/powerUps/WallPass.cpp src/powerUps/WallPass.hpp src/2D/Button.cpp  src/2D/Button.hpp  src/2D/IGameObject2D.hpp  src/2D/LabeledButton.cpp  src/2D/LabeledButton.hpp  src/2D/MainMenu.cpp  src/2D/MainMenu.hpp  src/2D/MySprite.cpp  src/2D/MySprite.hpp  src/2D/PlayerStats.cpp  src/2D/PlayerStats.hpp  src/2D/Text.cpp  src/2D/Text.hpp src/SaveLoader.cpp src/SaveLoader.hpp)

# set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# That's it! You should have an example executable that you can run. Have fun!