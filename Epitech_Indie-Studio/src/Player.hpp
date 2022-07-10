//
// Created by oem on 6/13/21.
//

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include "Cube.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "2D/PlayerStats.hpp"
#include <string>
#include <map>
#include <vector>
#include "AssetLoader.hpp"

class Player : public IGameObject {
    public:

    typedef struct {
        float translation_x;
        float translation_y;
        float translation_z;

        int _key_up;
        int _key_down;
        int _key_left;
        int _key_right;
        int _key_bomb;

        int bombCount;
        int bombMax;
        int fireCount;
        int moveSpeedLevel;

        bool isWallPassActive;
        bool hasWallPassRunOut;

        bool isAi;
        int playerNb;

        bool isDying;

        Color tint;
    } memory_chunk_player;

    Player(Vector3 position, Color tint, float scale, int playerNb, int up, int down, int left,
        int right, int bomb, int fps, Rectangle statsRect, AssetLoader  getAssetsFrom
    );
    Player(Player *to_copy, Vector3 position, Color tint, int playerNb, int up, int down, int left,
        int right, int bomb, Rectangle statsRect, AssetLoader  getAssetsFrom);
    Player(void *mem, AssetLoader getAssetsFrom);

    void setAI(bool state);
    void revive();

    PlayerStats *stats;
    std::vector<float> moveSpeedPerLevel = {3.0f, 3.9f, 4.6f, 5.3f, 5.9f, 6.4f, 6.8f, 7.1f, 7.3f, 7.4f};

    void updateControls(PlayerConfigs configs);
    int playerNB = 1;

    Sound hurtSound;
    Sound floorSound;
    Sound walkSound;

    private:
    AssetLoader assetLoader;

    //animation
    AnimationStates animationState = IDLE;
    Animation _curAnimation;
    std::map<AnimationStates, std::vector<Model>> _playerModelFrames;
    long long totalUpdatesCalled = 0;
    long long _animationDelay = 20000;
    float _rotation_angle = 0.0f;
    Color _tint;
    Color _whiteColor;
    Color _shirtColor = SKYBLUE;
    Color _pinkColor = PINK;
    bool temp = true;

    int _fps = 60;
    bool _controlledByAI = false;
    int _key_up;
    int _key_down;
    int _key_left;
    int _key_right;
    int _key_bomb;

    Texture2D statsTextures[6];
    Font statsFont;
    std::vector<Model> _frames;

    //object overrides
    void draw() override;
    void update(std::list<IGameObject *> *objects) override;

    //player specific functions
    void plant_bomb(std::list<IGameObject *> *pList);
    unsigned long get_storage_size() override;
    void * get_memory_to_store() override;

};

#endif //BOMBERMAN_PLAYER_HPP
