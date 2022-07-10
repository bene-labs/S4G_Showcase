//
// Created by oem on 6/13/21.
//

#ifndef BOMBERMAN_GAME_HPP
#define BOMBERMAN_GAME_HPP

#define DRAW_DEBUG false

#include <list>
#include "raylib.h"
#include "IGameObject.hpp"
#include "bomberman.hpp"
#include "Player.hpp"
#include "2D/IGameObject2D.hpp"
#include "2D/LabeledButton.hpp"
#include "2D/MySprite.hpp"
#include "AssetLoader.hpp"

bool collides_object_point(IGameObject *obj, Vector2 pt);
bool collides_object_object(IGameObject *obj1, IGameObject *obj2);

class Game {

    public:

    enum GAME_STATE {
        RUNNING,
        PAUSE,
        EDIT_SETTINGS,
        GAME_OVER,
        EXIT,
        BACK
    };
    Game();
    ~Game();
    bool run();
    bool startNew(int playerCount);
    bool deleteMap();
    bool wasInterrupted();

    void updatePlayerControls(const PlayerConfigs& configs);

    inline static const float boardWidth = 21;
    inline static const float boardHeight = 13;

    GAME_STATE state = RUNNING;

    void load_from_file();
    void savePlayerReferences(std::list<IGameObject *> objects);

    private:
    void startNew();
    void checkGameOver();
    Model floorModel;
    Music music;
    Music intenseMusic;
    Music victorySong;
    Sound confirmSound;
    Sound backSound;
    AssetLoader assetLoader;
    int _playerCount = 4;

    Camera3D camera = { 0 };

    void draw_objects();
    void update_objects();
    std::list<IGameObject *> objects;

    std::map<GAME_STATE, std::vector<IGameObject2D *>> UIObjects;
    std::vector<IGameObject *> playerReferences;
    int alivePlayerCount = 4;

    Vector3 startPositions[4] = {
        {(float)-boardWidth / 2 + 1, 0, (float)-boardHeight / 2 + 1},\
        {(float)+boardWidth / 2 - 2, 0, (float)-boardHeight / 2 + 1},
        {(float)-boardWidth / 2 + 1, 0, (float)+boardHeight / 2 - 2},
        {(float)+boardWidth / 2 - 2, 0, (float)+boardHeight / 2 - 2}};

    int _fps;
    float screenWidth;
    float screenHeight;

    bool isGameRunning = false;

    void build_board();
};



#endif //BOMBERMAN_GAME_HPP
