//
// Created by oem on 6/13/21.
//

#include <iostream>
#include "Game.hpp"
#include "Cube.hpp"
#include "Player.hpp"
#include "Chest.hpp"
#include "SaveLoader.hpp"

Game::Game()
{
    assetLoader.loadAssets();
    music = LoadMusicStream("resources/sounds/game_loop.mp3");
    victorySong = LoadMusicStream("resources/sounds/win_music.mp3");
    intenseMusic = LoadMusicStream("resources/sounds/rock.mp3");
    confirmSound = LoadSound("resources/sounds/confirm.wav");
    backSound = LoadSound("resources/sounds/back.wav");

    // Define the camera to look into our 3d world
    camera.position = { 0.0f, 11.0f, 0.0f };       // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };          // Camera looking at point
    camera.up = { 0.0f, 0.0f, 1.0f };              // Camera up vector (rotation towards target)
    camera.fovy = 10000.0f;                                             // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                          // Camera mode type

    _fps = PlayerConfigs::settings[FPS];
    SetTargetFPS(PlayerConfigs::settings[FPS]);
    screenWidth = (float) PlayerConfigs::settings[SCREEN_WIDTH];
    screenHeight = (float) PlayerConfigs::settings[SCREEN_HEIGHT];

    objects.push_front(new Player(startPositions[0], WHITE, 1.5, 1, \

        PlayerConfigs::settings[PLAYER1_UP], PlayerConfigs::settings[PLAYER1_DOWN],
        PlayerConfigs::settings[PLAYER1_LEFT], PlayerConfigs::settings[PLAYER1_RIGHT],
        PlayerConfigs::settings[PLAYER1_BOMB], _fps,
        {screenWidth * 0.002f, screenHeight * 0.003f, screenWidth * 0.33f, screenHeight * 0.1f},
        assetLoader));
    objects.push_front(
        new Player(dynamic_cast<Player *>(*objects.begin()), startPositions[1], YELLOW, 2,
            PlayerConfigs::settings[PLAYER2_UP], PlayerConfigs::settings[PLAYER2_DOWN],
            PlayerConfigs::settings[PLAYER2_LEFT], PlayerConfigs::settings[PLAYER2_RIGHT],
            PlayerConfigs::settings[PLAYER2_BOMB],
            {screenWidth * 0.671f, screenHeight * 0.003f, screenWidth * 0.33f, screenHeight * 0.1f},
            assetLoader));
    objects.push_front(
        new Player(dynamic_cast<Player *>(*objects.begin()), startPositions[2], BLUE, 3,
            PlayerConfigs::settings[PLAYER3_UP], PlayerConfigs::settings[PLAYER3_DOWN],
            PlayerConfigs::settings[PLAYER3_LEFT], PlayerConfigs::settings[PLAYER3_RIGHT],
            PlayerConfigs::settings[PLAYER3_BOMB],
            {screenWidth * 0.002f, screenHeight * 0.897f, screenWidth * 0.33f, screenHeight * 0.1f},
            assetLoader));
    objects.push_front(
        new Player(dynamic_cast<Player *>(*objects.begin()), startPositions[3], RED, 4,
            PlayerConfigs::settings[PLAYER4_UP], PlayerConfigs::settings[PLAYER4_DOWN],
            PlayerConfigs::settings[PLAYER4_LEFT], PlayerConfigs::settings[PLAYER4_RIGHT],
            PlayerConfigs::settings[PLAYER4_BOMB],
            {screenWidth * 0.671f, screenHeight * 0.897f, screenWidth * 0.33f, screenHeight * 0.1f},
            assetLoader));
    savePlayerReferences(objects);

    floorModel = LoadModelFromMesh(GenMeshCube(boardWidth + 2, 0.25f, boardHeight + 1));
    floorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =  LoadTexture("resources/images/floor.png");

    /* =====UI===== */

    //Load Fonts
    Font baseFont = (LoadFont("resources/fonts/setbackt.ttf"));
    Font bomberFont = (LoadFont("resources/fonts/Bomberman.ttf"));

    //Game Over Menu
    UIObjects[GAME_OVER].push_back(new Text(bomberFont, {screenWidth * 0.15f, screenHeight * 0.1f,
        screenWidth * 0.7f, screenHeight * 0.25f}, "Player 1 wins!", WHITE));
    UIObjects[GAME_OVER].push_back(
        new Button({screenWidth * 0.25f, screenHeight * 0.40f}, {screenWidth * 0.50f, screenHeight * 0.15f}, baseFont,
            "Again!", Button::START_NEW_GAME));
    UIObjects[GAME_OVER].push_back(
        new Button({screenWidth * 0.25f, screenHeight * 0.60f}, {screenWidth * 0.50f, screenHeight * 0.15f}, baseFont,
            "Quit", Button::LOAD_GAME_SELECT));

    //Pause Menu
    UIObjects[PAUSE].push_back(new Text(bomberFont, {screenWidth * 0.15f, screenHeight * 0.1f,
        screenWidth * 0.7f, screenHeight * 0.25f}, "Game Paused", WHITE));
    UIObjects[PAUSE].push_back(
        new Button({screenWidth * 0.25f, screenHeight * 0.35f}, {screenWidth * 0.50f, screenHeight * 0.10f}, baseFont,
            "Continue", Button::CONTINUE_GAME));
    UIObjects[PAUSE].push_back(
        new Button({screenWidth * 0.25f, screenHeight * 0.47f}, {screenWidth * 0.50f, screenHeight * 0.10f}, baseFont,
            "Restart", Button::START_NEW_GAME));
    UIObjects[PAUSE].push_back(
        new Button({screenWidth * 0.25f, screenHeight * 0.59f}, {screenWidth * 0.50f, screenHeight * 0.10f}, baseFont,
            "Change Settings", Button::LOAD_SETTINGS));
    UIObjects[PAUSE].push_back(
        new Button({screenWidth * 0.25f, screenHeight * 0.71f}, {screenWidth * 0.50f, screenHeight * 0.10f}, baseFont,
            "Quit", Button::BACK));
}

void Game::build_board()
{
    for (float z = 0; z < boardHeight; z += 1)
        for (float x = 0; x < boardWidth; x += 1) {
            if (int (z) % 2 + int (x) % 2 == 0 || z == 0 || x == 0 || z == (float) boardHeight - 1 || x == boardWidth - 1) {
                objects.push_front(new Cube(x - (float)boardWidth / 2 + (1 - 0.9f) / 2,
                    z - (float)boardHeight / 2 + (1 - 0.9f) / 2, BLACK, DARKPURPLE, 0.9f, false));
            }
        }
    for (float z = 0; z < boardHeight; z += 1)
        for (float x = 0; x < boardWidth; x += 1) {
            if (!(int (z) % 2 + int (x) % 2 == 0
            || z == 0|| x == 0 || z == boardHeight - 1 || x == boardWidth - 1)
            && rand() % 2 == 0
            && !((z < 3 && x < 3)
            || (boardHeight - 1 - z < 3 && boardWidth - 1 - x < 3)
            || (boardHeight - 1 - z < 3 && x < 3)
            || (z < 3 && boardWidth - 1 - x < 3)))
                objects.push_front(new Chest(x - (float) boardWidth / 2 + (1 - 0.9f) / 2, z - (float) boardHeight / 2 + (1 - 0.9f) / 2));
        }
}

bool Game::run()
{
    StopMusicStream(music);
    PlayMusicStream(music);
    StopMusicStream(victorySong);
    PlayMusicStream(victorySong);
    StopMusicStream(intenseMusic);
    PlayMusicStream(intenseMusic);
    SetMusicVolume(music, (float) PlayerConfigs::settings[VOLUME_MUSIC] / 100);
    SetMusicVolume(victorySong, (float) PlayerConfigs::settings[VOLUME_MUSIC] / 100);
    SetMusicVolume(intenseMusic, (float) PlayerConfigs::settings[VOLUME_MUSIC] / 100);

    SetSoundVolume(backSound, (float) PlayerConfigs::settings[VOLUME_SOUND] / 100);
    SetSoundVolume(confirmSound, (float) PlayerConfigs::settings[VOLUME_SOUND] / 100);
    for (auto player : playerReferences) {
        SetSoundVolume(dynamic_cast<Player *>(player)->hurtSound, (float) PlayerConfigs::settings[VOLUME_SOUND] / 100);
        SetSoundVolume(dynamic_cast<Player *>(player)->walkSound, (float) PlayerConfigs::settings[VOLUME_SOUND] / 100);
        SetSoundVolume(dynamic_cast<Player *>(player)->floorSound, (float) PlayerConfigs::settings[VOLUME_SOUND] / 100);
    }

    isGameRunning = true;
    while (!WindowShouldClose() && state != EXIT)    // Detect window close button or ESC key
    {
        if (state == RUNNING) {
            if (alivePlayerCount >= 3)
                UpdateMusicStream(music);
            else
                UpdateMusicStream(intenseMusic);
        } else if (state == GAME_OVER) {
            UpdateMusicStream(victorySong);
        }
        if (state == EDIT_SETTINGS || state == BACK) {
            StopSoundMulti();
            PlaySound(backSound);
            return true;
        }
        if (IsKeyPressed(KEY_ESCAPE) && state != GAME_OVER) {
            if (state == PAUSE)
                PlaySound(backSound);
            else {
                StopSoundMulti();
                PlaySound(confirmSound);
            }
            state = (state == PAUSE ? RUNNING : PAUSE);
        }
        //if (IsKeyDown(KEY_F))
        //    ToggleFullscreen();
        update_objects();
        draw_objects();
        checkGameOver();
    }
    isGameRunning = false;
    StopSoundMulti();
    if (state == EXIT) {
        PlaySound(backSound);
        return true;
    }
    return false;
}

void Game::draw_objects()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    BeginMode3D(camera);

    if (DRAW_DEBUG) {
        DrawFPS(10, 10);
        DrawGrid(40, 1.0f);
    }

    Vector3 pos = {(-((float)boardWidth + 2) / 2 + (1 - 0.9f) / 2) - ((1.0f - boardWidth + 2) / 2) + 2, -1 -((1.0f - 0.25) / 2), (-(boardHeight + 1) / 2 + (1 - 0.9f) / 2) - ((1.0f - boardHeight + 1) / 2) + 1};
    DrawModel(floorModel, pos, 1, WHITE);
    for (auto object : objects)
        object->draw();

    EndMode3D();
    for (auto player : playerReferences) {
        dynamic_cast<Player *>(player)->stats->draw();
    }
    for (auto object : UIObjects[state])
        object->draw();
    EndDrawing();
}

void Game::update_objects()
{
    if (state == RUNNING) {
        for (auto it = objects.begin(); it != objects.end(); it++) {
            if ((*it)->to_be_removed) {
                it = objects.erase(it);
                if (it == objects.end())
                    break;
            }
        }
        for (auto object : objects) {
            object->update(&objects);
        }
    }

    int buttonReturnValue = -1;

    if (buttonReturnValue >= 1)
        PlaySound(confirmSound);
    for (auto object : UIObjects[state]) {
        buttonReturnValue = object->update();

        switch (buttonReturnValue) {
        case Button::START_NEW_GAME:
            startNew();
            break;
        case Button::LOAD_GAME_SELECT:
            state = EXIT;
            break;
        case Button::CONTINUE_GAME:
            state = RUNNING;
            break;
        case Button::LOAD_SETTINGS:
            state = EDIT_SETTINGS;
            break;
        case Button::BACK:
            state = BACK;
            break;
        default:
            break;
        }
    }
}

bool Game::wasInterrupted()
{
    return (isGameRunning);
}

Game::~Game()
{
    SaveLoader saver;
    saver.save(&objects);
    while (!objects.empty())
        objects.remove(objects.front());
    CloseWindow();
}

bool Game::startNew(int playerCount)
{
    int i = 0;

    StopMusicStream(music);
    PlayMusicStream(music);
    StopMusicStream(victorySong);
    PlayMusicStream(victorySong);
    StopMusicStream(intenseMusic);
    PlayMusicStream(intenseMusic);

    _playerCount = playerCount;
    alivePlayerCount = 4;

    this->deleteMap();
    for (auto it = std::prev(objects.end()); i < 4; i++, it--)
    {
        if (i >= playerCount)
            dynamic_cast<Player *>(*it)->setAI(true);
        else
            dynamic_cast<Player *>(*it)->setAI(false);
        dynamic_cast<Player *>(*it)->stats->reset();
        dynamic_cast<Player *>(*it)->transform.translation = startPositions[i];
        dynamic_cast<Player *>(*it)->revive();
        if (it == objects.begin()) break;
    }
    state = RUNNING;
    build_board();
    return run();
}

void Game::startNew()
{
    int i = 0;

    alivePlayerCount = 4;

    this->deleteMap();
    for (auto it = std::prev(objects.end()); i < 4; i++, it--)
    {
        if (i >= _playerCount)
            dynamic_cast<Player *>(*it)->setAI(true);
        else
            dynamic_cast<Player *>(*it)->setAI(false);
        dynamic_cast<Player *>(*it)->stats->reset();
        dynamic_cast<Player *>(*it)->transform.translation = startPositions[i];
        dynamic_cast<Player *>(*it)->revive();
        if (it == objects.begin()) break;
    }
    state = RUNNING;
    build_board();
}

bool Game::deleteMap()
{
    unsigned int prevSize = objects.size();

    auto  it = objects.begin();
    for (; ((*it)->name != "Player") && it != objects.end(); ++it);
    if (it == objects.begin())
        return false;
    objects.erase(objects.begin(), it);
    return true;
}

void Game::checkGameOver()
{
    if (state == GAME_OVER)
        return;
    int alivePlayerNb = 1;
    int alivePlayerTemp = 0;
    for (int i = 0; i < 4; i++) {
        if (dynamic_cast<Player *>(playerReferences[i])->alive) {
            alivePlayerTemp++;
            alivePlayerNb = dynamic_cast<Player *>(playerReferences[i])->playerNB;
        }
    }
    if (alivePlayerTemp < alivePlayerCount) {
        alivePlayerCount = alivePlayerTemp;
    } else
        return;
    if (alivePlayerCount == 1) {
        dynamic_cast<Text *>(UIObjects[GAME_OVER][0])->replaceText("Player " + std::to_string(alivePlayerNb) + " wins!");
        state = GAME_OVER;
    } else if (alivePlayerCount == 0) {
        dynamic_cast<Text *>(UIObjects[GAME_OVER][0])->replaceText("No one wins. YOU ALL SUCK!");
        state = GAME_OVER;
    }
}

void Game::updatePlayerControls(const PlayerConfigs& configs)
{
    for (auto player : playerReferences)
    {
        dynamic_cast<Player *>(player)->updateControls(configs);
    }
}

void Game::load_from_file()
{
    SaveLoader loader;
    while (objects.size() > 0)
        objects.pop_front();
    objects = *loader.load(assetLoader);
    savePlayerReferences(objects);
}

void Game::savePlayerReferences(std::list<IGameObject *> objects)
{
    while (!playerReferences.empty()) playerReferences.pop_back();

    for (auto object : objects) {
        if (object->name == "Player")
            playerReferences.push_back(object);
    }
}
