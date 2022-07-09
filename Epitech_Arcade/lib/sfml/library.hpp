#ifndef SFML_LIBRARY_HPP
#define SFML_LIBRARY_HPP

#include "../../lib_include/gfx_interface.hpp"
#include <SFML/Graphics.hpp>

#include <string>
#include <map>

class Graphics : public IGraphics {
    public:
    Graphics();

    ~Graphics() override;
    void init_screen(int x, int y) override;
    void destroy_screen() override;
    void clear_screen() override;
    void display_screen() override;
    void *createObject(object_creation_data *object_data) override ;

    void draw(void *object, int x0, int x1, int y0, int y1) override; // x, y in px => x0,y0 top left corner && x1,y1 bottom left corner
    void deleteObject(void *object) override;
    std::string getPressedKey() override;

    virtual std::vector<object_creation_data> getObjectData();
    private:
    sf::Color &get_color(std::string name);

    sf::RenderWindow *window;

    std::map<void *, object_creation_data> objects;

};

extern "C" {
    __attribute__((constructor))
    void init();

    IGraphics *create_graphics();

    __attribute__((destructor))
    void destroy();
};
#endif //SFML_LIBRARY_HPP
