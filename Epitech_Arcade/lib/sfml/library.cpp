#include "library.hpp"
#include "../ncurses/library.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

sf::RenderWindow *window;

extern "C" {
    __attribute__((constructor))
    void init() {
    }

    IGraphics *create_graphics() {
        return new Graphics;
    }

    __attribute__((destructor))
    void destroy() {
    }
}

void Graphics::init_screen(int x, int y)
{
    window = new sf::RenderWindow(sf::VideoMode(x, y), "Arcade");
}

void Graphics::destroy_screen()
{
    window->close();
}

void Graphics::clear_screen()
{
    window->clear();
}

void Graphics::display_screen()
{
    window->display();
}

void *Graphics::createObject(object_creation_data *object_data)
{
    switch (object_data->type) {
    case TEXT: {
        auto font = new sf::Font();
        font->loadFromFile(object_data->path_to_resource);
        auto text = new sf::Text(object_data->text, *font);
        text->setFillColor(get_color(object_data->color_name));
        objects[text] = *object_data;
        return text;
    }
    case SPRITE: {
        auto texture = new sf::Texture;
        texture->loadFromFile(object_data->path_to_resource);
        auto sprite = new sf::Sprite(*texture);
        objects[sprite] = *object_data;
        return sprite;
    }
    case RECT: {
        auto rect = new sf::RectangleShape();
        objects[rect] = *object_data;
        rect->setFillColor(get_color(object_data->color_name));
        return rect;
    }
    default:
        return nullptr;
    }
}

Graphics::Graphics()
{

}

sf::Color &Graphics::get_color(std::string name)
{
    static std::map<std::string, sf::Color *> colors;

    if (colors.empty()) {
        colors["red"] = new sf::Color(sf::Color::Red);
        colors["blue"] = new sf::Color(sf::Color::Blue);
        colors["green"] = new sf::Color(sf::Color::Green);
        colors["yellow"] = new sf::Color(sf::Color::Yellow);
        colors["black"] = new sf::Color(sf::Color::Black);
        colors["white"] = new sf::Color(sf::Color::White);
        colors["orange"] = new sf::Color(232, 144, 37);
        colors["cyan"] = new sf::Color(sf::Color::Cyan);
        colors["magenta"] = new sf::Color(sf::Color::Magenta);
    }
    if (colors.contains(name))
        return *colors[name];
    return *colors["magenta"];
}

struct MyException : public std::exception {
    [[nodiscard]] const char * what () const noexcept override {
        return "Invalid size to draw!";
    }
};

void Graphics::draw(void *object, int x0, int x1, int y0, int y1)
{
    if (x0 >= x1 || y0 >= y1)
        throw MyException();
    if (!objects.contains(object))
        exit(44);
    switch (objects[object].type) {
    case TEXT: {
        auto text = (sf::Text *) object;
        text->setCharacterSize( y1 - y0);
        while (text->getLocalBounds().width > (float) (x1 - x0)) {
            text->setCharacterSize(text->getCharacterSize() - 1);
        }
        text->setPosition((float)x0, (float)y0);
        window->draw(*text);
        break;
    }
    case SPRITE: {
        auto sprite = (sf::Sprite *) object;
        sprite->setScale((float) (x1 - x0) / (float) sprite->getTextureRect().width,(float) (y1 - y0) / (float) sprite->getTextureRect().height);
        sprite->setPosition((float) x0, (float) y0);
        window->draw(*sprite);
       // printf("SFML:Draw from [%f,%f] to [%d, %d]\n", sprite->getPosition().x, sprite->getPosition().y, sprite->getTextureRect().width, sprite->getTextureRect().height);
        break;
    }
    case RECT: {
        auto rect = (sf::RectangleShape *) object;
        sf::Vector2f size(x1-x0, y1-y0);
        rect->setSize(size);
        rect->setPosition((float) x0, (float ) y0);
        //printf("pos: (%.2f, %.2f), size: (%.2f, %.2f)\n", rect->getPosition().x, rect->getPosition().y, rect->getSize().x, rect->getSize().y);
        sf::RectangleShape shape;
        window->draw(*rect);
        break;
    }
    default:
        printf("reached default case in draw.\n");
    }
}

void Graphics::deleteObject(void *object)
{
    switch (objects[object].type) {
    case TEXT: {
        //delete ((sf::Text *) object);
        break;
    }
    case SPRITE: {
        //delete ((sf::Sprite *) object);
        break;
    }
    case RECT: {
        //delete ((sf::RectangleShape *) object);
        break;
    }
    }
    objects.erase(object);
}

std::string Graphics::getPressedKey()
{
    sf::Event ev;
    window->pollEvent(ev);

   /*if (ev.type == sf::Event::Closed)
        return "exit";*/
    if (ev.type != sf::Event::KeyPressed)
        return "";
    if (ev.key.code <= 'z' - 'a' && ev.key.code >= 'a' - 'a') {
        std::string res;
        res.push_back(ev.key.code + 'a');
        return res;
    }
    if (ev.key.code <= sf::Keyboard::Key::Num9 && ev.key.code >= sf::Keyboard::Key::Num0) {
        std::string res;
        if (ev.key.code == sf::Keyboard::Key::Num0)
            return ("0");
        res.push_back(ev.key.code - sf::Keyboard::Key::Num0 + '0');
        return res;
    }

    switch (ev.key.code) {
    case sf::Keyboard::Key::Left:
        return "left";
    case sf::Keyboard::Key::Right:
        return ("right");
    case sf::Keyboard::Key::Up:
        return ("up");
    case sf::Keyboard::Key::Down:
        return ("down");
    case sf::Keyboard::Key::Space:
        return ("space");
    case sf::Keyboard::Key::BackSpace:
        return ("backspace");
    case sf::Keyboard::Key::Escape:
        return ("esc");
    case sf::Keyboard::Key::Enter:
        return ("enter");
    default:
        return ("*");
    }
}

std::vector<object_creation_data> Graphics::getObjectData()
{
    std::vector<object_creation_data> res;
    for (auto & object : objects)
        res.push_back(object.second);
    return res;
}

Graphics::~Graphics()
{
    window->close();
    /*for (auto it = objects.begin(); it != objects.end(); it++) {
        deleteObject(it->first);
    }*/
}


