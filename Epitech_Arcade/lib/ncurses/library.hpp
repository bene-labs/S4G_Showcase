#ifndef SFML_LIBRARY_HPP
#define SFML_LIBRARY_HPP

#include "../../lib_include/gfx_interface.hpp"
#include <ncurses.h>

#include <string>
#include <map>
#include <vector>

class Graphics : public IGraphics {
    public:
    Graphics();

    ~Graphics() override;
    void init_screen(int x, int y) override;
    void destroy_screen() override;
    void clear_screen() override;
    void *createObject(object_creation_data *object_data) override ;

    void draw(void *object, int x0, int x1, int y0, int y1) override; // x, y in px => x0,y0 top left corner && x1,y1 bottom left corner
    void deleteObject(void *object) override;
    void display_screen() override;
    std::string getPressedKey() override;

    virtual std::vector<object_creation_data> getObjectData();
    private:
    int get_color(std::string name);
    void print_rect(int x0, int x1, int y0, int y1, char c, std::string color_name = "white");
    void print_text_rect(int x0, int x1, int y0, int y1, std::string text, std::string color_name = "white");

    const int relation_corrector_x = 2;
    const int relation_corrector_y = 1;
    static int scale_correction(int &n) { return (n /= 10); }
    int X(int x) { return x * relation_corrector_x; }
    int Y(int y) { return y * relation_corrector_y; }
    WINDOW *window;
    int height;
    int width;
    std::map<void *, object_creation_data> objects;
    void resize(int x, int y);
};

extern "C" {
    __attribute__((constructor))
    void init();

    IGraphics *create_graphics();

    __attribute__((destructor))
    void destroy();
};
#endif //SFML_LIBRARY_HPP
