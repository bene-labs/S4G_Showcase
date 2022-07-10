/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/
#include "MainMenu.hpp"
#include "../Animation.hpp"

void updatePlayerConfigsFromButtonValues(PlayerConfigs *configs, std::vector<IGameObject2D *> keyBindingsElements)
{
    std::string lineToInsert;

    int i = 3;
    for (auto it = keyBindingsElements.begin(); it != keyBindingsElements.end() && i < VOLUME_MUSIC; it++) {
        if (dynamic_cast<LabeledButton *>(*it) != nullptr) {
            if (dynamic_cast<LabeledButton *>(*it)->command == Button::SINGLE_INPUT) {
                lineToInsert = dynamic_cast<LabeledButton *>(*it)->getText();
                if (lineToInsert.size() == 1 && lineToInsert[0] >= 32 && lineToInsert[0] <= 125) {
                    configs->settings[(SETTINGS)i] = (unsigned int) lineToInsert[0];
                    i++;
                } else {
                    int key = 0;
                    for (auto it2 = Button::specialKeys.begin();
                        it2 != Button::specialKeys.end(); it2++) {
                        if ((*it2).second == lineToInsert) {
                            key = (*it2).first;
                            break;
                        }
                    }
                    configs->settings[(SETTINGS)i] = key;
                    i++;
                }
            }
        }
    }
}


void MainMenu::saveToFile(std::vector<IGameObject2D *> settingsElements)
{
    std::ofstream settingsFile("data/settings", std::ios::trunc);
    std::string lineToInsert;



    for (auto it = settingsElements.begin(); it != settingsElements.end(); it++) {
        if (dynamic_cast<LabeledButton *>(*it) != nullptr) {
            if (dynamic_cast<LabeledButton *>(*it)->command == Button::INPUT || dynamic_cast<LabeledButton *>(*it)->command == Button::VOLUME_INPUT)
                settingsFile << dynamic_cast<LabeledButton *>(*it)->getText() << std::endl;
            else {
                lineToInsert = dynamic_cast<LabeledButton *>(*it)->getText();
                if (lineToInsert.size() == 1 && lineToInsert[0] >= 32 && lineToInsert[0] <= 125) {
                    settingsFile << std::to_string((int) lineToInsert[0]) << std::endl;
                } else {
                    int key = 0;
                    for (auto it2 = Button::specialKeys.begin(); it2 != Button::specialKeys.end(); it2++) {
                        if ((*it2).second == lineToInsert) {
                            key = (*it2).first;
                            break;
                        }
                    }
                    settingsFile << std::to_string(key) << std::endl;
                }
            }
        }
    }
}

MainMenu::MainMenu(PlayerConfigs configs
) : _sh((float) configs.settings[SCREEN_HEIGHT]), _sw((float) configs.settings[SCREEN_WIDTH]), playerConfigs(configs)
{
    //sounds
    music = LoadMusicStream("resources/sounds/menu_loop.mp3");
    PlayMusicStream(music);

    selectSound = LoadSound("resources/sounds/confirm.wav");
    backSound = LoadSound("resources/sounds/back.wav");

    //Load Fonts
    availableFonts.push_back(LoadFont("resources/fonts/setbackt.ttf"));
    availableFonts.push_back(LoadFont("resources/fonts/Bomberman.ttf"));

    //Load Textures
    availableTextures.push_back(LoadTexture("resources/images/Bomberman Wallpaper.png"));

    //Load Loading Objects
    gameObjects[LOADING].push_back(new MySprite(availableTextures[0], \
    {0, 0}, {_sw, _sh}));
    gameObjects[LOADING].push_back(new Text(availableFonts[0], {_sw * 0.25f, _sh * 0.26f, _sw * 0.50f, _sh * 0.15f}, "Loading...", YELLOW, 10));
    gameObjects[LOADING].push_back(new Text(availableFonts[1], {(float) (_sh * 0.05), 0, (float) (_sw * 0.9), (float) (_sh * 0.2)}, "Bomberman 3D", WHITE, 10));


    //Load Start Objects
    gameObjects[START].push_back(new MySprite(availableTextures[0], \
    {0, 0}, {_sw, _sh}));
    gameObjects[START].push_back(
        new Button({_sw * 0.25f, _sh * 0.26f}, {_sw * 0.50f, _sh * 0.15f}, availableFonts[0],
            "Play", Button::LOAD_GAME_SELECT));
    gameObjects[START].push_back(new Text(availableFonts[1], {(float) (_sh * 0.05), 0, (float) (_sw * 0.9), (float) (_sh * 0.2)}, "Bomberman 3D", WHITE, 10));


    //Load Game Select Objects
    gameObjects[GAME_SELECT].push_back(new MySprite(availableTextures[0], \
    {0, 0}, {_sw, _sh}));
    gameObjects[GAME_SELECT].push_back(
        new Button({_sw * 0.25f, _sh * 0.26f}, {_sw * 0.50f, _sh * 0.15f}, availableFonts[0],
            "Continue", Button::CONTINUE_GAME, "No Game Found!"));
    gameObjects[GAME_SELECT].push_back(
        new Button({_sw * 0.25f, _sh * 0.46f}, {_sw * 0.50f, _sh * 0.15f}, availableFonts[0],
            "New Game", Button::START_NEW_GAME));
    gameObjects[GAME_SELECT].push_back(new Text(availableFonts[1], {(float) (_sh * 0.05), 0, (float) (_sw * 0.9), (float) (_sh * 0.2)}, "GET READY", WHITE, 10));
    gameObjects[GAME_SELECT].push_back(
        new Button({_sw * 0.25f, _sh * 0.66f}, {_sw * 0.50f, _sh * 0.15f}, availableFonts[0],
            "Settings", Button::LOAD_SETTINGS));


    //Load Player Select Objects
    gameObjects[PLAYER_SELECT].push_back(new MySprite(availableTextures[0], {0, 0}, {_sw, _sh}));
    gameObjects[PLAYER_SELECT].push_back(new Text(availableFonts[1], {(float) (_sh * 0.05), 0, (float) (_sw * 0.9), (float) (_sh * 0.2)}, "How many PLAYERS?", WHITE, 10));
    gameObjects[PLAYER_SELECT].push_back(
        new Button({_sw * 0.25f, _sh * 0.25f}, {_sw * 0.50f, _sh * 0.12f}, availableFonts[0],
            "P1 vs AI vs AI vs AI", Button::ONE_PLAYER));
    gameObjects[PLAYER_SELECT].push_back(
        new Button({_sw * 0.25f, _sh * 0.40f}, {_sw * 0.50f, _sh * 0.12f}, availableFonts[0],
            "P1 vs P2 vs AI vs AI", Button::TWO_PLAYER));
    gameObjects[PLAYER_SELECT].push_back(
        new Button({_sw * 0.25f, _sh * 0.55f}, {_sw * 0.50f, _sh * 0.12f}, availableFonts[0],
            "P1 vs P2 vs P3 vs AI", Button::THREE_PLAYER));
    gameObjects[PLAYER_SELECT].push_back(
        new Button({_sw * 0.25f, _sh * 0.70f}, {_sw * 0.50f, _sh * 0.12f}, availableFonts[0],
            "P1 vs P2 vs P3 vs P4", Button::FOUR_PLAYER));


    //Load Settings Objects

    gameObjects[SETTING].push_back(new MySprite(availableTextures[0], {0, 0}, {_sw, _sh}));
    gameObjects[SETTING].push_back(new Text(availableFonts[1], {(float) (_sh * 0.05), 0,
        (float) (_sw * 0.9), (float) (_sh * 0.2)}, "Settings", WHITE, 10));

    //Resolution
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 0.10f, _sh * 0.27f}, {_sw * 0.20f, _sh * 0.12f}, availableFonts[0],
            std::to_string(configs.settings[SCREEN_WIDTH]), "ScreenWidth", {0, -_sh * 0.1f}, {0, 0},
            Button::INPUT));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 0.7f, _sh * 0.27f}, {_sw * 0.20f, _sh * 0.12f}, availableFonts[0],
            std::to_string(configs.settings[SCREEN_HEIGHT]), "ScreenHeight", {0, -_sh * 0.1f},
            {0, 0}, Button::INPUT));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 0.40f, _sh * 0.27f}, {_sw * 0.2f, _sh * 0.12f}, availableFonts[0],
            std::to_string(configs.settings[FPS]), "FPS", {0, -_sh * 0.115f}, {0, 0}, Button::INPUT));


    //Key Bindings
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 0.20f, _sh * 0.72f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER1_UP], "Player1 Up", {0, -_sh * 0.1f}, {7.5f, 0},
            Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 0.6f, _sh * 0.72f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER1_DOWN], "Player1 Down", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 0.40f, _sh * 0.80f}, {_sw * 0.2f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER1_BOMB], "Player1 Bomb", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 0.20f, _sh * 0.88f}, {_sw * 0.20f, _sh * 0.10f}, availableFonts[0],
            configs.settings[PLAYER1_LEFT], "Player1 Left", {0, -_sh * 0.1f}, {7.5f, 0},
            Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 0.6f, _sh * 0.88f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER1_RIGHT], "Player1 Right", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));

    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 1.0f, _sh * 0.72f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER2_UP], "Player2 Up", {0, -_sh * 0.1f}, {7.5f, 0},
            Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 1.4f, _sh * 0.72f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER2_DOWN], "Player2 Down", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 1.2f, _sh * 0.80f}, {_sw * 0.2f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER2_BOMB], "Player2 Bomb", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 1.0f, _sh * 0.88f}, {_sw * 0.20f, _sh * 0.10f}, availableFonts[0],
            configs.settings[PLAYER2_LEFT], "Player2 Left", {0, -_sh * 0.1f}, {7.5f, 0},
            Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 1.4f, _sh * 0.88f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER2_RIGHT], "Player2 Right", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));

    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 2.0f, _sh * 0.72f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER3_UP], "Player3 Up", {0, -_sh * 0.1f}, {7.5f, 0},
            Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 2.4f, _sh * 0.72f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER3_DOWN], "Player3 Down", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 2.2f, _sh * 0.80f}, {_sw * 0.2f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER3_BOMB], "Player3 Bomb", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 2.0f, _sh * 0.88f}, {_sw * 0.20f, _sh * 0.10f}, availableFonts[0],
            configs.settings[PLAYER3_LEFT], "Player3 Left", {0, -_sh * 0.1f}, {7.5f, 0},
            Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 2.4f, _sh * 0.88f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER3_RIGHT], "Player3 Right", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));

    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 3.0f, _sh * 0.72f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER4_UP], "Player4 Up", {0, -_sh * 0.1f}, {7.5f, 0},
            Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 3.4f, _sh * 0.72f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER4_DOWN], "Player4 Down", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 3.2f, _sh * 0.80f}, {_sw * 0.2f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER4_BOMB], "Player4 Bomb", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 3.0f, _sh * 0.88f}, {_sw * 0.20f, _sh * 0.10f}, availableFonts[0],
            configs.settings[PLAYER4_LEFT], "Player4 Left", {0, -_sh * 0.1f}, {7.5f, 0},
            Button::SINGLE_INPUT, "", {86, 186, 245,255}));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 3.4f, _sh * 0.88f}, {_sw * 0.20f, _sh * 0.08f}, availableFonts[0],
            configs.settings[PLAYER4_RIGHT], "Player4 Right", {0, -_sh * 0.1f},
            {7.5f, 0}, Button::SINGLE_INPUT, "", {86, 186, 245,255}));

    //Sound Settings
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 0.2f, _sh * 0.47f}, {_sw * 0.20f, _sh * 0.12f}, availableFonts[0],
            std::to_string(configs.settings[VOLUME_MUSIC]), "Music Volume", {0, -_sh * 0.1f}, {0, 0},
            Button::VOLUME_INPUT));
    gameObjects[SETTING].push_back(
        new LabeledButton({_sw * 0.6f, _sh * 0.47f}, {_sw * 0.20f, _sh * 0.12f}, availableFonts[0],
            std::to_string(configs.settings[VOLUME_SOUND]), "Sound Volume", {0, -_sh * 0.1f},
            {0, 0}, Button::VOLUME_INPUT));

    //Load Map Selection Object
}

MainMenu::~MainMenu()
{
    saveToFile(gameObjects[SETTING]);
}

int MainMenu::run(Game *game)
{
    int updateReturn = -1;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            PlaySound(backSound);
            switch (menuState) {
            case START:
                return QUIT;
            case GAME_SELECT:
                menuState = START;
                break;
            case PLAYER_SELECT:
            case IN_GAME:
            case SETTING:
                if (game->state == Game::EDIT_SETTINGS) {
                    game->state = Game::RUNNING;
                    game->run();
                }
                menuState = GAME_SELECT;
                break;
            default:
                break;
            }
        }
        if (game->state == Game::EXIT || game->state == Game::BACK) {
            menuState = GAME_SELECT;
            game->state = Game::RUNNING;
        } else if (game->state == Game::EDIT_SETTINGS) {
            menuState = SETTING;
        }
        if (menuState == IN_GAME)
            return (QUIT);
        SetMusicVolume(music, (float) playerConfigs.settings[VOLUME_MUSIC] / 100);
        SetSoundVolume(backSound, (float) playerConfigs.settings[VOLUME_SOUND] / 100);
        SetSoundVolume(selectSound, (float) playerConfigs.settings[VOLUME_SOUND] / 100);
        if (game->state != Game::EDIT_SETTINGS)
            UpdateMusicStream(music);
        BeginDrawing();
        ClearBackground(BEIGE);
        //BeginMode2D(camera);
        for (auto object : gameObjects[menuState])
            object->draw();
        //EndMode2D();
        EndDrawing();

        for (auto object : gameObjects[menuState]) {
            updateReturn = object->update();
            if (updateReturn >= 1) {
                PlaySound(selectSound);
            }
            if (updateReturn >= 1 && updateReturn <= 4) {
                StopMusicStream(music);
                menuState = IN_GAME;
                game->startNew(updateReturn);
                PlayMusicStream(music);
            } else {
                switch (updateReturn) {
                case Button::START_NEW_GAME:
                    menuState = PLAYER_SELECT;
                    break;
                case Button::CONTINUE_GAME: {
                    display_all();
                    std::ifstream f(".save");
                    if (game->wasInterrupted() || f.good()) {
                        if (!game->wasInterrupted() && f.good()) {
                            dynamic_cast<Button *>(object)->_text->replaceText("Loading...");
                            display_all();
                            f.close();
                            game->load_from_file();
                            dynamic_cast<Button *>(object)->_text->replaceText("Continue");
                        }
                        StopMusicStream(music);
                        menuState = IN_GAME;
                        game->run();
                        PlayMusicStream(music);
                        break;
                    } else {
                        dynamic_cast<Button *>(object)->setError();
                        break;
                    }
                }
                case Button::LOAD_GAME_SELECT:
                    menuState = GAME_SELECT;
                    break;
                case Button::LOAD_SETTINGS:
                    menuState = SETTING;
                    break;
                case Button::SINGLE_INPUT:
                    updatePlayerConfigsFromButtonValues(&playerConfigs, gameObjects[SETTING]);
                    game->updatePlayerControls(playerConfigs);
                    break;
                case Button::VOLUME_INPUT:
                    if (dynamic_cast<LabeledButton *>(object)->labelText->text == "Music Volume") {
                        playerConfigs.settings[VOLUME_MUSIC] = std::stoi(dynamic_cast<LabeledButton *>(object)->getValue());
                    } else if (dynamic_cast<LabeledButton *>(object)->labelText->text == "Sound Volume") {
                        playerConfigs.settings[VOLUME_SOUND] = std::stoi(dynamic_cast<LabeledButton *>(object)->getValue());
                    }
                default:
                    break;
                }
            }
        }
    }
    return (QUIT);
}

void MainMenu::display_all()
{
    BeginDrawing();
    ClearBackground(BEIGE);
    //BeginMode2D(camera);
    for (auto object : gameObjects[menuState])
        object->draw();
    //EndMode2D();
    EndDrawing();
}
