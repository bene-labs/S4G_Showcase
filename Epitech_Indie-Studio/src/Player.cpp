#include <cmath>
#include <iostream>
#include <utility>
#include "Player.hpp"
#include "Bomb.hpp"

// controls in following order: UP, DOWN, LEFT, RIGHT, PLACE_BOMB
Player::Player(Vector3 position, Color tint, float scale, int playerNb, int up, int down, int left,
    int right, int bomb, int fps, Rectangle statsRect, AssetLoader  getAssetsFrom
) : _fps(fps), playerNB(playerNb), _tint(tint), assetLoader(std::move(getAssetsFrom))
{
    name = "Player";
    type = "Player";

    destructable = true;

    _key_up = up;
    _key_down = down;
    _key_left = left;
    _key_right = right;
    _key_bomb = bomb;

    transform.translation = position;
    transform.scale = {scale, scale, scale};
    collision_cube_width = 0.9f;

    if (tint.r == YELLOW.r  && tint.g == YELLOW.g && tint.b == YELLOW.b && tint.a == YELLOW.a) {
        _whiteColor = {254, 205, 0, 255};
    } else if (tint.r == BLUE.r  && tint.g == BLUE.g && tint.b == BLUE.b && tint.a == BLUE.a) {
        _whiteColor = {20, 15, 160, 255};
    } else if (tint.r == RED.r  && tint.g == RED.g && tint.b == RED.b && tint.a == RED.a) {
        _whiteColor = {153, 7, 0, 255};
    } else
        _whiteColor = WHITE;

    std::vector<std::vector<Model>> models = assetLoader.getNeededModels(this);
    if (models.size() != 3 || models[0].size() != 22 ||  models[1].size() != 175 || models[2].size() != 67) {
        fprintf(stderr, "Failed to load Player Models!");
        exit(84);
    }
    _playerModelFrames[RUN] = models[0];
    _playerModelFrames[IDLE] = models[1];
    _playerModelFrames[DEATH] = models[2];
    _curAnimation.assignNewAnimation(_playerModelFrames[IDLE].size(), _animationDelay, IDLE);

    if (_playerModelFrames[IDLE][0].materialCount >= 8) {
        _shirtColor = _playerModelFrames[IDLE][0].materials[5].maps->color;
        _pinkColor = _playerModelFrames[IDLE][0].materials[7].maps->color;
    }
    /*
    for (auto model : _playerModelFrames[IDLE]) if (model.materialCount >= 4) model.materials[3].maps->color = {255,219,172, 255};
    for (auto model : _playerModelFrames[RUN]) if (model.materialCount >= 4) model.materials[3].maps->color = {255,219,172, 255};
    for (auto model : _playerModelFrames[DEATH]) if (model.materialCount >= 4) model.materials[3].maps->color ={255,219,172, 255};*/

    statsTextures[0] = LoadTexture("resources/images/big_wallpaper.png");
    statsTextures[1] = LoadTexture("resources/images/player_icons.png");
    statsTextures[2] = LoadTexture("resources/images/Bombupsprite.PNG.png");
    statsTextures[3] = LoadTexture("resources/images/Fireupsprite.PNG.png");
    statsTextures[4] = LoadTexture("resources/images/Skatesprite.PNG.png");
    statsTextures[5] = LoadTexture("resources/images/Soft_Block_Pass.png");

    statsFont = LoadFont("resources/fonts/neuropol-x-free.regular.ttf");

    stats = new PlayerStats(statsRect, statsFont, statsTextures, WHITE);

    hurtSound = LoadSound("resources/sounds/player_hurt.wav");
    floorSound = LoadSound("resources/sounds/enemy_hit_2.ogg");
    walkSound = LoadSound("resources/sounds/player_run.ogg");

}

Player::Player(Player *to_copy, Vector3 position, Color tint, int playerNb, int up, int down,
    int left, int right, int bomb, Rectangle statsRect, AssetLoader getAssetsFrom
) : _tint(tint), _fps(to_copy->_fps), playerNB(playerNb),
    statsFont(to_copy->statsFont), _shirtColor(to_copy->_shirtColor), assetLoader(std::move(getAssetsFrom))
{
    int bombFrameCount = 30;
    this->_frames = getModelFramesFromFile("resources/models/bomberman/Bomb/bomb", &bombFrameCount);
    Texture bombTexture = LoadTexture("resources/models/bomberman/Bomb/textures/Bomb.png");
    for (auto frame : _frames) {
        frame.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = bombTexture;
    }

    name = "Player";
    type = "Player";

    _playerModelFrames = to_copy->_playerModelFrames;

    _key_up = up;
    _key_down = down;
    _key_left = left;
    _key_right = right;
    _key_bomb = bomb;

    destructable = true;

    transform.translation = position;
    transform.scale = to_copy->transform.scale;
    collision_cube_width = 0.9f;

    if (tint.r == YELLOW.r  && tint.g == YELLOW.g && tint.b == YELLOW.b && tint.a == YELLOW.a) {
        _whiteColor = {254, 205, 0, 255};
    } else if (tint.r == BLUE.r  && tint.g == BLUE.g && tint.b == BLUE.b && tint.a == BLUE.a) {
        _whiteColor = {20, 15, 160, 255};
    } else if (tint.r == RED.r  && tint.g == RED.g && tint.b == RED.b && tint.a == RED.a) {
        _whiteColor = {153, 7, 0, 255};
    } else
        _whiteColor = WHITE;

    _curAnimation.assignNewAnimation(_playerModelFrames[IDLE].size(), _animationDelay, IDLE);

    for (int i = 0; i < 6; i++) {
        statsTextures[i] = to_copy->statsTextures[i];
    }
    stats = new PlayerStats(statsRect, statsFont, statsTextures, tint);

    hurtSound = LoadSound("resources/sounds/player_hurt.wav");
    floorSound = LoadSound("resources/sounds/enemy_hit_2.ogg");
    walkSound = LoadSound("resources/sounds/player_run.ogg");
}

void Player::draw()
{
    if (!alive) {
        if (_playerModelFrames[DEATH][_curAnimation.getFrame()].materialCount >= 8) {
            _playerModelFrames[DEATH][_curAnimation.getFrame()].materials[6].maps->color = _whiteColor;
            if (_tint.r == YELLOW.r  && _tint.g == YELLOW.g && _tint.b == YELLOW.b && _tint.a == YELLOW.a) {
                _playerModelFrames[DEATH][_curAnimation.getFrame()].materials[5].maps->color = {255,
                    211, 0, 255};
                _playerModelFrames[DEATH][_curAnimation.getFrame()].materials[7].maps->color = {
                    253, 151, 150, 255};
            }
            else if (_tint.r == RED.r  && _tint.g == RED.g && _tint.b == RED.b && _tint.a == RED.a) {
                _playerModelFrames[DEATH][_curAnimation.getFrame()].materials[5].maps->color = {128, 0, 0, 255};
                _playerModelFrames[DEATH][_curAnimation.getFrame()].materials[7].maps->color =
                    {158,155, 247, 255};
            }
        }
        DrawModelEx(_playerModelFrames[DEATH][_curAnimation.getFrame()], {transform.translation.x,transform.translation.y, transform.translation.z} , {0, 1, 0}, _rotation_angle, transform.scale, WHITE);
        if (_playerModelFrames[DEATH][_curAnimation.getFrame()].materialCount >= 8) {
            _playerModelFrames[DEATH][_curAnimation.getFrame()].materials[6].maps->color = _whiteColor;
            _playerModelFrames[DEATH][_curAnimation.getFrame()].materials[5].maps->color = _shirtColor;
            if (_tint.r == RED.r  && _tint.g == RED.g && _tint.b == RED.b && _tint.a == RED.a)
                _playerModelFrames[DEATH][_curAnimation.getFrame()].materials[7].maps->color = _pinkColor;
        }
    } else {
        if (_playerModelFrames[animationState][_curAnimation.getFrame()].materialCount >= 8) {
            _playerModelFrames[animationState][_curAnimation.getFrame()].materials[6].maps->color = _tint;
            if (_tint.r == YELLOW.r  && _tint.g == YELLOW.g && _tint.b == YELLOW.b && _tint.a == YELLOW.a) {
                _playerModelFrames[animationState][_curAnimation.getFrame()].materials[5].maps->color = {
                    255, 211, 0, 255};
                _playerModelFrames[animationState][_curAnimation.getFrame()].materials[7].maps->color = {
                    253, 151, 150, 255};
            }
            else if (_tint.r == RED.r  && _tint.g == RED.g && _tint.b == RED.b && _tint.a == RED.a) {
                _playerModelFrames[animationState][_curAnimation.getFrame()].materials[5].maps->color = {
                    128, 0, 0, 255};
                _playerModelFrames[animationState][_curAnimation.getFrame()].materials[7].maps->color =
                    {158,155, 247, 255};
            }
            _playerModelFrames[animationState][_curAnimation.getFrame()].materials[6].maps->color = _whiteColor;
        }
        DrawModelEx(_playerModelFrames[animationState][_curAnimation.getFrame()],
            transform.translation, {0, 1, 0}, _rotation_angle, transform.scale, WHITE);
        if (_playerModelFrames[animationState][_curAnimation.getFrame()].materialCount >= 8) {
            _playerModelFrames[animationState][_curAnimation.getFrame()].materials[6].maps->color = WHITE;
            _playerModelFrames[animationState][_curAnimation.getFrame()].materials[5].maps->color = _shirtColor;
            if (_tint.r == YELLOW.r  && _tint.g == YELLOW.g && _tint.b == YELLOW.b && _tint.a == YELLOW.a || _tint.r == RED.r  && _tint.g == RED.g && _tint.b == RED.b && _tint.a == RED.a)
            _playerModelFrames[animationState][_curAnimation.getFrame()].materials[7].maps->color = _pinkColor;
        }
    }
}

void Player::update(std::list<IGameObject *> *objects)
{
    if (!alive) {
        return;
    }
    if (dying) {
        if (animationState != DEATH) {
            animationState = DEATH;
            PlaySound(hurtSound);
        }
        animationState = _curAnimation.update(animationState);
        if (_curAnimation.getFrame() == _playerModelFrames[DEATH].size() - 30)
            PlaySound(floorSound);
        alive = !(animationState == STILL);
        return;
    }

    stats->update();
    totalUpdatesCalled++;

    Vector3 vel = {0, 0, 0};

    bool colliding = false;
    for (auto object : *objects) {
        if (object != this && object->blocking &&
            object->collision_cube_width != 0 &&
            collides_object_object(this, object)) {
            colliding = true;
            break;
        }
    }

    if (!_controlledByAI) {
        if (IsKeyDown(_key_up) && transform.translation.z > -Game::boardHeight / 2)
            vel.z -= (moveSpeedPerLevel[stats->moveSpeedLevel] / (float) _fps);//GetFPS());
        if (IsKeyDown(_key_down) && transform.translation.z < Game::boardHeight / 2 - 1)
            vel.z += (moveSpeedPerLevel[stats->moveSpeedLevel] / (float) _fps);//GetFPS());
        if (IsKeyDown(_key_left) && transform.translation.x > -Game::boardWidth / 2)
            vel.x -= (moveSpeedPerLevel[stats->moveSpeedLevel] / (float) _fps);//GetFPS());
        if (IsKeyDown(_key_right) && transform.translation.x < Game::boardWidth / 2 - 1)
            vel.x += (moveSpeedPerLevel[stats->moveSpeedLevel] / (float) _fps);//GetFPS());
        if (!colliding && stats->bombCount > 0 && IsKeyPressed(_key_bomb))
            plant_bomb(objects);
    }
    if (stats->isWallPassActive)
        transform.translation.y = 1.1f;
    else
        transform.translation.y = 0.0f;

    animationState = IDLE;
    if (vel.x != 0 || vel.z != 0) {
        if (!IsSoundPlaying(walkSound))
            PlaySound(walkSound);
        if (vel.z < 0) {
            _rotation_angle = 180.0f;
            if (vel.x > 0) {
                _rotation_angle -= 45.0f;
            } else if (vel.x < 0) {
                _rotation_angle += 45.0f;
            }
        } else if (vel.z > 0) {
            _rotation_angle = 0.0f;
            if (vel.x > 0) {
                _rotation_angle += 45.0f;
            } else if (vel.x < 0) {
                _rotation_angle -= 45.0f;
            }
        } else {
            if (vel.x > 0) {
                _rotation_angle = 90.0f;
            } else if (vel.x < 0) {
                _rotation_angle = -90.0f;
            }
        }
        animationState = RUN;
    }
    if (vel.x != 0 || vel.z != 0) {
        transform.translation.x += vel.x;
        if (!stats->isWallPassActive) {
            for (auto object : *objects) {
                if (object != this && !(object->name == "Player" && object->dying) && object->blocking &&
                    object->collision_cube_width != 0 &&
                    collides_object_object(this, object)) {
                    transform.translation.x -= vel.x;
                }
            }
        }
        transform.translation.z += vel.z;
        if (!stats->isWallPassActive) {
            for (auto object : *objects) {
                if (object != this && !(object->name == "Player" && object->dying) && object->blocking &&
                    object->collision_cube_width != 0 &&
                    collides_object_object(this, object)) {
                    transform.translation.z -= vel.z;
                }
            }
        }
    } else
        StopSound(walkSound);
    auto now = std::chrono::high_resolution_clock::now();
    if (!colliding && stats->isWallPassActive && stats->hasWallPassRunOut)
        stats->isWallPassActive = false;
    animationState = _curAnimation.update(animationState);
}

void Player::plant_bomb(std::list<IGameObject *> *objects)
{
    objects->push_front(new Bomb(transform.translation.x, transform.translation.z, stats->fireCount, this, assetLoader));
}

void Player::setAI(bool state)
{
    _controlledByAI = state;
}

void Player::revive()
{
    alive = true;
    dying = false;
    animationState = IDLE;
}

void Player::updateControls(PlayerConfigs configs)
{
    switch (playerNB) {
    case 1:
        _key_up = configs.settings[PLAYER1_UP];
        _key_down = configs.settings[PLAYER1_DOWN];
        _key_left = configs.settings[PLAYER1_LEFT];
        _key_bomb = configs.settings[PLAYER1_BOMB];
        _key_right = configs.settings[PLAYER1_RIGHT];
        _key_down = configs.settings[PLAYER1_DOWN];
        break;
    case 2:
        _key_up = configs.settings[PLAYER2_UP];
        _key_down = configs.settings[PLAYER2_DOWN];
        _key_left = configs.settings[PLAYER2_LEFT];
        _key_bomb = configs.settings[PLAYER2_BOMB];
        _key_right = configs.settings[PLAYER2_RIGHT];
        _key_down = configs.settings[PLAYER2_DOWN];
        break;
    case 3:
        _key_up = configs.settings[PLAYER3_UP];
        _key_down = configs.settings[PLAYER3_DOWN];
        _key_left = configs.settings[PLAYER3_LEFT];
        _key_bomb = configs.settings[PLAYER3_BOMB];
        _key_right = configs.settings[PLAYER3_RIGHT];
        _key_down = configs.settings[PLAYER3_DOWN];
        break;
    case 4:
        _key_up = configs.settings[PLAYER4_UP];
        _key_down = configs.settings[PLAYER4_DOWN];
        _key_left = configs.settings[PLAYER4_LEFT];
        _key_bomb = configs.settings[PLAYER4_BOMB];
        _key_right = configs.settings[PLAYER4_RIGHT];
        _key_down = configs.settings[PLAYER4_DOWN];
        break;
    default:
        break;
    }
}

unsigned long Player::get_storage_size()
{
    return sizeof(Player::memory_chunk_player);
}

void *Player::get_memory_to_store()
{
    auto memory = new memory_chunk_player;
    memory->translation_x = transform.translation.x;
    memory->translation_y = transform.translation.y;
    memory->translation_z = transform.translation.z;

    memory->_key_up = _key_up;
    memory->_key_down = _key_down;
    memory->_key_bomb = _key_bomb;
    memory->_key_left = _key_left;
    memory->_key_right = _key_right;

    memory->bombCount = stats->bombCount;
    memory->bombMax = stats->bombMax;
    memory->fireCount = stats->fireCount;
    memory->moveSpeedLevel = stats->moveSpeedLevel;

    memory->isWallPassActive = stats->isWallPassActive;
    memory->hasWallPassRunOut = stats->hasWallPassRunOut;

    memory->isAi = _controlledByAI;
    memory->playerNb = playerNB;
    memory->tint = _tint;

    memory->isDying = dying;
    return (void *) memory;
}

Player::Player(void *mem, AssetLoader getAssetsFrom) : assetLoader(std::move(getAssetsFrom))
{
    auto memory = (Player::memory_chunk_player *) mem;

    transform.translation.x = memory->translation_x;
    transform.translation.y = memory->translation_y;
    transform.translation.z = memory->translation_z;

    transform.scale = {1.5f, 1.5f, 1.5f};
    transform.rotation = {0, 0, 0};

    this->destructable = true;

    name = "Player";
    type = "Player";

    destructable = true;

    playerNB = memory->playerNb;

    _key_up = memory->_key_up;
    _key_down = memory->_key_down;
    _key_left = memory->_key_left;
    _key_right = memory->_key_right;
    _key_bomb = memory->_key_bomb;

    collision_cube_width = 0.9f;

    _tint = memory->tint;

    dying = memory->isDying;

    std::vector<std::vector<Model>> models = assetLoader.getNeededModels(this);
    if (models.size() != 3 || models[0].size() != 22 ||  models[1].size() != 175 || models[2].size() != 67) {
        fprintf(stderr, "Failed to load Player Models!");
        exit(84);
    }
    _playerModelFrames[RUN] = models[0];
    _playerModelFrames[IDLE] = models[1];
    _playerModelFrames[DEATH] = models[2];
    if (dying)
        _curAnimation.assignNewAnimation(_playerModelFrames[DEATH].size(), _animationDelay, DEATH);
    else
        _curAnimation.assignNewAnimation(_playerModelFrames[IDLE].size(), _animationDelay, IDLE);
    if (_playerModelFrames[IDLE][0].materialCount >= 8) {
        _shirtColor = _playerModelFrames[IDLE][0].materials[5].maps->color;
        _pinkColor = _playerModelFrames[IDLE][0].materials[7].maps->color;
    }

    statsTextures[0] = LoadTexture("resources/images/big_wallpaper.png");
    statsTextures[1] = LoadTexture("resources/images/player_icons.png");
    statsTextures[2] = LoadTexture("resources/images/Bombupsprite.PNG.png");
    statsTextures[3] = LoadTexture("resources/images/Fireupsprite.PNG.png");
    statsTextures[4] = LoadTexture("resources/images/Skatesprite.PNG.png");
    statsTextures[5] = LoadTexture("resources/images/Soft_Block_Pass.png");


    Rectangle statsRect;
    switch (playerNB) {
    case 1: {
        statsRect = {(float) PlayerConfigs::settings[SCREEN_WIDTH] * 0.002f, (float) PlayerConfigs::settings[SCREEN_HEIGHT] * 0.003f, (float) PlayerConfigs::settings[SCREEN_WIDTH] * 0.33f, (float) PlayerConfigs::settings[SCREEN_HEIGHT] * 0.1f};
        break;
    }
    case 2: {
        statsRect = {(float) PlayerConfigs::settings[SCREEN_WIDTH] *  0.671f, (float) PlayerConfigs::settings[SCREEN_HEIGHT] * 0.003f, (float) PlayerConfigs::settings[SCREEN_WIDTH] * 0.33f, (float) PlayerConfigs::settings[SCREEN_HEIGHT] * 0.1f};
        break;
    }
    case 3: {
        statsRect = {(float) PlayerConfigs::settings[SCREEN_WIDTH] *  0.002f, (float) PlayerConfigs::settings[SCREEN_HEIGHT] * 0.897f, (float) PlayerConfigs::settings[SCREEN_WIDTH] * 0.33f, (float) PlayerConfigs::settings[SCREEN_HEIGHT] * 0.1f};
        break;
    }
    case 4: {
        statsRect = {(float) PlayerConfigs::settings[SCREEN_WIDTH] *  0.671f, (float) PlayerConfigs::settings[SCREEN_HEIGHT] * 0.897f, (float) PlayerConfigs::settings[SCREEN_WIDTH] * 0.33f, (float) PlayerConfigs::settings[SCREEN_HEIGHT] * 0.1f};
        break;
    }
    }

    if (_tint.r == YELLOW.r  && _tint.g == YELLOW.g && _tint.b == YELLOW.b && _tint.a == YELLOW.a) {
        _whiteColor = {254, 205, 0, 255};
    } else if (_tint.r == BLUE.r  && _tint.g == BLUE.g && _tint.b == BLUE.b && _tint.a == BLUE.a) {
        _whiteColor = {20, 15, 160, 255};
    } else if (_tint.r == RED.r  && _tint.g == RED.g && _tint.b == RED.b && _tint.a == RED.a) {
        _whiteColor = {153, 7, 0, 255};
    } else
        _whiteColor = WHITE;

    statsFont = LoadFont("resources/fonts/neuropol-x-free.regular.ttf");
    stats = new PlayerStats(statsRect, statsFont, statsTextures, _tint);



    for (int i = 1; i < memory->fireCount; i++) stats->increaseFire();
    /*
    if (memory->bombCount < 3)
        for (int i = 3; i > memory->bombCount; i--) stats->decreaseBombs();
    else
        for (int i = 3; i < memory->bombCount; i++) stats->increaseBombs();*/
    for (int i = 3; i < memory->bombMax; i++) stats->increaseMaxBombs();
    for (int i = memory->bombMax; i > memory->bombCount; i--) stats->decreaseBombs();
    for (int i = 0; i < memory->moveSpeedLevel; i++) stats->increaseSpeed();
    if (memory->isWallPassActive) stats->enableWallPass();

    hurtSound = LoadSound("resources/sounds/player_hurt.wav");
    floorSound = LoadSound("resources/sounds/enemy_hit_2.ogg");
    walkSound = LoadSound("resources/sounds/player_run.ogg");
}
