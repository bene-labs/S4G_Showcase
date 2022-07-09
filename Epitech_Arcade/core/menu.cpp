/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Created by benedikt,
*/

#include <fstream>
#include "menu.hpp"

std::string getUserName()
{
    std::ifstream highScoreFile("users");
    std::string fileContent;
    std::string nameLine;

    if (highScoreFile.fail())
        return "nobody";
    fileContent.assign((std::istreambuf_iterator<char>(highScoreFile) ),
        (std::istreambuf_iterator<char>()));
    nameLine = fileContent.substr(fileContent.find_last_of('\n') + 1, std::string::npos);
    if (nameLine.empty())
        return "nobody";
    return nameLine;
}

std::string getHighScore(const std::string& gameName)
{;
    std::ifstream highScoreFile(gameName + "_scores");
   // printf("searching: %s\n", gameName.c_str());
    std::string fileContent;
    std::string scoreLine;

    if (highScoreFile.fail())
        return ("Nobody 0000");
    fileContent.assign((std::istreambuf_iterator<char>(highScoreFile)),
        (std::istreambuf_iterator<char>()));
    if (fileContent.find_last_of('\n') != std::string::npos)
        scoreLine = fileContent.substr(fileContent.find_last_of('\n'),
            std::string::npos);
    else
        scoreLine = fileContent;
    if (scoreLine.empty())
        return ("Nobody 0000");
    return (scoreLine.substr(1, std::string::npos));
}

Menu::Menu(IGraphics *lib, int screen_width, int screen_height) : _lib(lib), _screen_width(screen_width), _screen_height(screen_height)
{
    inputField = new Selectable(lib, getUserName(), std::make_pair(screen_width / 11, screen_height * 0.85), \
screen_width * 0.87, screen_height * 0.1);
    loadGameSelection();
    loadGraphicsSelection();
    highScoreTextData.text = getHighScore(gameNames[selectedGame].substr(13, gameNames[selectedGame].size() - 16));
    highScoreText = _lib->createObject(&highScoreTextData);
}

void Menu::loadGameSelection()
{
    for (const auto & entry : std::filesystem::directory_iterator("./lib/")) {
        std::string entryName(entry.path().c_str());

        /*if (entryName.substr(0, 12) != "./lib/arcade")
            continue;*/
        if (entryName.substr(entryName.size() - 3, 3) != ".so")
            continue;
        Lib game_lib(entry.path());
        auto createGame = (IGame *(*)(IGraphics *)) game_lib.loadFunc("create_game",false);
        if (createGame == nullptr)
            continue;
        totalGames++;
        gameNames.push_back(entry.path());
    }

    if (totalGames == 0) {
        std::cerr << "No game-libs found in './lib' !\n";
        exit(84);
    }

    for (int i = 0, w = (int) (_screen_width * 0.1), h = _screen_height / 11; \
    i < totalGames; i++, h += (int) ((_screen_height * 0.7) / totalGames)) {
        gameSelection.push_back(new Selectable(_lib, gameNames[i].substr(13, gameNames[i].size() - 16), std::make_pair(w, h), (int) (_screen_width * 0.33), (int) ((_screen_height * 0.7) / (totalGames * 1.75))));
    }
    gameSelection[0]->toggleActive();
}

void Menu::loadGraphicsSelection()
{
    for (const auto & entry : std::filesystem::directory_iterator("./lib/")) {
        std::string entryName(entry.path().c_str());

        //printf("file loaded: |%s|\n", entryName.c_str());
        /*if (entryName.substr(0, 9) != "./lib/lib")
            continue;*/
        if (entryName.substr(entryName.size() - 3, 3) != ".so")
            continue;
        Lib gfx_lib(entry.path());
        auto createLib = (IGraphics *(*)()) gfx_lib.loadFunc("create_graphics",false);
        if (createLib == nullptr)
            continue;
        totalLibs++;
        libNames.push_back(entry.path());
    }
    if (totalLibs == 0) {
        std::cerr << "No graphical-libs found in './lib' !\n";
        exit(84);
    }

    for (int i = 0, w =(int) (_screen_width * 0.63), h = _screen_height / 11; \
    i < totalLibs; i++, h += (int) ((_screen_height * 0.7) / totalLibs)) {
        graphicsSelection.push_back(new Selectable(_lib, libNames[i].substr(13, libNames[i].size() - 16), std::make_pair(w, h), (int) (_screen_width * 0.33), (int) ((_screen_height * 0.7) / (totalLibs * 1.75))));
    }
    graphicsSelection[0]->toggleActive();
}

Menu::~Menu()
{
    _lib->destroy_screen();
}

void Menu::display()
{
    _lib->clear_screen();
    _lib->draw(highScoreText, _screen_width * 0.25, _screen_width * 0.75, 0, _screen_height * 0.09);
    try {
        for (size_t i = 0; i < gameSelection.size(); i++)
            gameSelection[i]->draw();
        for (size_t i = 0; i < graphicsSelection.size(); i++)
            graphicsSelection[i]->draw();
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    inputField->draw();
    _lib->display_screen();
}

std::string Menu::getSelectedGame()
{
    return gameNames[selectedGame];
}

std::string Menu::getSelectedLib()
{
    return libNames[selectedLib];
}

bool Menu::isActive() const
{
    return _isActive;
}

bool Menu::handleInput(std::string& last_pressed_key)
{
    if (last_pressed_key == "enter") {
        last_pressed_key = "";
        return true;
    }

    if (last_pressed_key == "1") {
        usePrevGraphicsLib();
        last_pressed_key = "";
    } else  if (last_pressed_key == "2") {
        useNextGraphicsLib();
        last_pressed_key = "";
    } else if (last_pressed_key == "space") {
        inputField->toggleActive();
        last_pressed_key = "";
    }
    else if (inputField->isActive()) {
        updateUserName(last_pressed_key);
        return false;
    }
    if (last_pressed_key == "w") {
        selectPrevGame();
        last_pressed_key = "";
    } else if (last_pressed_key == "s") {
        selectNextGame();
        last_pressed_key = "";
    } else if (last_pressed_key == "up") {
        selectPrevLib();
        last_pressed_key = "";
    } else if (last_pressed_key == "down") {
        selectNextLib();
        last_pressed_key = "";
    }
    return false;
}

void Menu::setState(bool active)
{
    if (_isActive == active)
        return;
    if (!active) {
        if (inputField->getText() != getUserName()) {
            std::ofstream nameFile("users", std::ios::app);
            if (nameFile.is_open())
                nameFile << "\n" + inputField->getText();
        }
        _lib->destroy_screen();
    } else {
        _lib->init_screen(1200, 960);
        highScoreTextData.text = getHighScore(gameNames[selectedGame].substr(13, gameNames[selectedGame].size() - 16));
        highScoreText = _lib->createObject(&highScoreTextData);
    }
    _isActive = active;
}

void Menu::updateUserName(std::string& input)
{
    if (input == "")
        return;
    if (input == "backspace") {
        inputField->setText(inputField->getText().substr(0, inputField->getText().size() - 1));
        input = "";
        return;
    }
    if (input != "esc" && (input[0] >= 'a' && input[0] <= 'z') || (input[0] >= '0' && input[0] <= '9')) {
        inputField->setText(inputField->getText().append(input.substr(0, 1)));
        input = "";
        return;
    }

}

bool Menu::isNewFrame()
{
    std::chrono::steady_clock::time_point this_call_time = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::duration<double>>(
        this_call_time - last_call_time).count() < min_frame_delay) {
        return false;
    }
    last_call_time = this_call_time;
    return true;
}

bool Menu::selectPrevGame()
{
    if (totalGames <= 1)
        return false;
    gameSelection[selectedGame]->toggleActive();
    selectedGame--;
    if (selectedGame < 0)
        selectedGame = totalGames - 1;
    gameSelection[selectedGame]->toggleActive();
    highScoreTextData.text = getHighScore(gameNames[selectedGame].substr(13, gameNames[selectedGame].size() - 16));
    highScoreText = _lib->createObject(&highScoreTextData);
    return true;
}

bool Menu::selectNextGame()
{
    if (totalGames <= 1)
        return false;
    gameSelection[selectedGame]->toggleActive();
    selectedGame++;
    if (selectedGame >= totalGames)
        selectedGame = 0;
    gameSelection[selectedGame]->toggleActive();
    highScoreTextData.text = getHighScore(gameNames[selectedGame].substr(13, gameNames[selectedGame].size() - 16));
    highScoreText = _lib->createObject(&highScoreTextData);
    return true;
}

bool Menu::selectPrevLib()
{
    if (totalLibs <= 1)
        return false;
    graphicsSelection[selectedLib]->toggleActive();
    selectedLib--;
    if (selectedLib < 0)
        selectedLib = totalLibs - 1;
    graphicsSelection[selectedLib]->toggleActive();
    return true;
}

bool Menu::selectNextLib()
{
    if (totalLibs <= 1)
        return false;
    graphicsSelection[selectedLib]->toggleActive();
    selectedLib++;
    if (selectedLib >= totalLibs)
        selectedLib = 0;
    graphicsSelection[selectedLib]->toggleActive();
    return true;
}

void Menu::useNextGraphicsLib()
{
    _lib->destroy_screen();
    selectNextLib();
    Lib new_gfx_lib(getSelectedLib());
    auto createLib = (IGraphics *(*)()) new_gfx_lib.loadFunc("create_graphics");
    _lib = createLib();
    reloadObjects();
    _lib->init_screen(1200, 960);
}

void Menu::usePrevGraphicsLib()
{
    _lib->destroy_screen();
    selectPrevLib();
    Lib new_gfx_lib(getSelectedLib());
    auto createLib = (IGraphics *(*)()) new_gfx_lib.loadFunc("create_graphics");
    _lib = createLib();
    reloadObjects();
    _lib->init_screen(1200, 960);
}

void Menu::reloadObjects()
{
    highScoreText = _lib->createObject(&highScoreTextData);
    for (auto selectable : gameSelection)
        selectable->loadNewLib(_lib);
    for (auto selectable : graphicsSelection)
        selectable->loadNewLib(_lib);
    inputField->loadNewLib(_lib);
}

IGraphics *Menu::getActiveGraphicsLib()
{
    return _lib;
}
