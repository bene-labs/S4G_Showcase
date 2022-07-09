#include "library.hpp"


#include <iostream>
#include <unistd.h>
#include <math.h>
#include <ncurses.h>

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

void Graphics::display_screen()
{
    refresh();
}

void Graphics::print_rect(int x0, int x1, int y0, int y1, char c, std::string color_name) {
    attron(COLOR_PAIR(get_color(color_name)));
    for (int y = Y(y0); y <= Y(y1); y++) {
        for (int x = X(x0); x <= X(x1); x++)
            mvprintw(y, x, "%c", c);
    }
    attroff(COLOR_PAIR(get_color(color_name)));
    refresh();
}

void Graphics::print_text_rect(int x0, int x1, int y0, int y1, std::string text,
    std::string color_name) {
    int i = 0;
    bool textFitsInLine;
    std::string trailingLines = " ";
    text.append("|");
    attron(COLOR_PAIR(get_color(color_name)));
    for (int y = Y(y0); y <= Y(y1); y++) {
        textFitsInLine = true;
        for (int x = X(x0); x <= X(x1); x++) {
            if (i >= text.size()) {
                i = 0;
                if (X(x1) - x < text.size())
                    textFitsInLine = false;
            }
            if (textFitsInLine)
                mvprintw(y, x, "%c", text[i]);
            else
                mvprintw(y, x, "%c", trailingLines[i]);
            if (textFitsInLine)
                i++;
        }
    }
    attroff(COLOR_PAIR(get_color(color_name)));
    refresh();
}

void Graphics::resize(int x, int y) {
    getmaxyx( stdscr, height, width);
    while (Y(y) != LINES - 1 || X(x) != COLS - 1) {
        print_rect(0, x, 0, y, '.');
        //clear();
        //std::string resize_message = "!RESIZE to fit box!";
        //int y_message = (int) LINES / 2;
        //int x_message = (int) round(COLS / 2 - round(resize_message.length() / 2));
        //move(y_message, x_message);
        //printw(resize_message.c_str());
        getch();
        refresh();
        getmaxyx( stdscr, height, width);
    }
}

void Graphics::init_screen(int x, int y)
{
    try {
        window = initscr();
        width = scale_correction(x);
        height = scale_correction(y);
        wresize(window, Y(height) + 1, X(width) + 1);
        curs_set(0);
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        clear();
        start_color();
        resize(width, height);
        clear_screen();
        refresh();
    } catch (std::exception e) {
        std::cerr << "your terminal in incompatible with ncurses :(" << std::endl;
        exit(84);
    }
}

void Graphics::destroy_screen()
{
    endwin();
}

void Graphics::clear_screen()
{
    erase();
}

void *Graphics::createObject(object_creation_data *object_data)
{
    if (!(object_data->type >= TEXT && object_data->type <= RECT))
        return nullptr;
    auto res = new object_creation_data;
    res->type = object_data->type;
    res->path_to_resource = object_data->path_to_resource;
    if (object_data->text == "")
        res->text = " ";
    else
        res->text = object_data->text;
    res->color_name = object_data->color_name;
    objects[res] = *res;
    return res;
}

Graphics::Graphics()
{

}

int Graphics::get_color(std::string name)
{
    static std::map<std::string, int> colors;

    if (colors.empty()) {
        colors["red"] = 1; init_pair(1, COLOR_BLACK, COLOR_RED);
        colors["blue"] = 2; init_pair(2, COLOR_WHITE, COLOR_BLUE);
        colors["green"] = 3; init_pair(3, COLOR_BLACK, COLOR_GREEN);
        colors["yellow"] = 4; init_pair(4, COLOR_BLACK, COLOR_YELLOW);
        colors["black"] = 5; init_pair(5, COLOR_WHITE, COLOR_BLACK);
        colors["white"] = 6; init_pair(6, COLOR_BLACK, COLOR_WHITE);
        colors["orange"] = 7; init_pair(7, COLOR_BLACK, COLOR_YELLOW); // :( no ncurses orange
        colors["cyan"] = 8; init_pair(8, COLOR_BLACK, COLOR_CYAN);
        colors["magenta"] = 9; init_pair(9, COLOR_WHITE, COLOR_MAGENTA);
    }
    if (colors.contains(name))
        return colors[name];
    return colors["magenta"];
}

void Graphics::draw(void *object, int x0, int x1, int y0, int y1)
{
    scale_correction(x0);
    scale_correction(x1);
    scale_correction(y0);
    scale_correction(y1);

    if (objects[object].type == TEXT) {
        //mvprintw(X(x0), Y(y0), "%s", objects[object].text.c_str());
        print_text_rect(x0, x1, y0, y1, objects[object].text, objects[object].color_name);
    }
    else
        print_rect(x0, x1, y0, y1, objects[object].text.at(0), objects[object].color_name);
    refresh();
}

void Graphics::deleteObject(void *object)
{
    objects.erase(object);
}

std::string Graphics::getPressedKey()
{
    int c = getch();

    if (c == ERR)
        return "";
    if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
        return std::string("").append(1, c);
    switch (c) {
    case KEY_LEFT:
        return "left";
    case KEY_RIGHT:
        return ("right");
    case KEY_UP:
        return ("up");
    case KEY_DOWN:
        return ("down");
    case KEY_BACKSPACE:
        return ("backspace");
    case ' ':
        return ("space");
    case 27: // Alt or Esc
        return ("esc");
    case '\n':
        return ("enter");
    case '\t':
        return ("tab");
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
    destroy_screen();
    for (auto it = objects.begin(); it != objects.end(); it++) {
        deleteObject(it->first);
    }
}


