#ifndef ARCADE_LIBHANDLER_HPP
#define ARCADE_LIBHANDLER_HPP

#include <iostream>
#include <utility>
#include <dlfcn.h>
#include <string>

class Lib {
    public:

    explicit Lib(const std::string& lib_path) {
        loadLib(lib_path);
    }

    void close_lib() {
        dlclose(handle);
    }

    void *loadFunc(const std::string &func_name, bool verbose = true)
    {
        void *res = dlsym(handle, func_name.c_str());
        if (res == nullptr) {
            if (verbose)
                std::cerr << func_name << " not in lib! Abort.";
            return nullptr;
        }
        return res;
    }

    private:
    void *handle = nullptr;

    void loadLib(const std::string& lib_name)
    {
        handle = dlopen(lib_name.c_str(), RTLD_LAZY);
        if (handle == nullptr) {
            std::cerr << lib_name << " not found! Abort.";
            exit(84);
        }
        dlerror();
    }
};

class GraphicalLib : Lib {

    public:
    void (*init_screen)(int x, int y); //x+y in px
    void (*destroy_screen)();
    void (*clear_screen)();
    void * (*createObject)(void *object_data); // initializes object and returns pointer to it in memory

    void (*draw)(void *object, int x0, int x1, int y0, int y1); // x, y in px => x0,y0 top left corner && x1,y1 bottom left corner
    void (*deleteObject)(void *object);
    std::string (*getPressedKey)(void);
    // on no user input: “”
    // on window exit: “exit”
    // eg on pressed ‘e’: “e”


    explicit GraphicalLib(const std::string &libPath) : Lib(libPath)
    {
        init_screen = reinterpret_cast<typeof init_screen>(loadFunc("init_screen"));
        destroy_screen = reinterpret_cast<typeof destroy_screen>(loadFunc("destroy_screen"));
        clear_screen = reinterpret_cast<typeof clear_screen>(loadFunc("clear_screen"));
        createObject = reinterpret_cast<typeof createObject>(loadFunc("createObject"));
        draw = reinterpret_cast<typeof draw>(loadFunc("draw"));
        deleteObject = reinterpret_cast<typeof deleteObject>(loadFunc("deleteObject"));
        getPressedKey = reinterpret_cast<typeof getPressedKey>(loadFunc("getPressedKey"));
    }
};

class GameLib : Lib {

    public:
    void (*start_game)(void);
    std::string (*game_tick)(void);
    bool (*is_running)(void);

    explicit GameLib(const std::string &libPath) : Lib(libPath)
    {
        start_game = reinterpret_cast<typeof start_game>(loadFunc("start_game"));
        game_tick = reinterpret_cast<typeof game_tick>(loadFunc("game_tick"));
        is_running = reinterpret_cast<typeof is_running>(loadFunc("is_running"));
    }
};

#endif //ARCADE_LIBHANDLER_HPP