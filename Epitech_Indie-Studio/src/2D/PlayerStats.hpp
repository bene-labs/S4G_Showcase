//
// Created by Benedikt Mertes on 19.06.2021.
//

#ifndef BOMBERMAN_PLAYERSTATS_HPP
#define BOMBERMAN_PLAYERSTATS_HPP

#include "LabeledButton.hpp"
#include "MySprite.hpp"


class PlayerStats : public IGameObject2D {
    public:
    PlayerStats(Rectangle Background, Font textFont, Texture2D spriteTextures[6], Color colorScheme = WHITE);

    void draw() override;
    int update() override;

    void increaseSpeed();
    void increaseMaxBombs();
    void increaseBombs();
    void decreaseBombs();
    void increaseFire();
    void enableWallPass();
    void reset();

    int bombCount = 3;
    int bombMax = 3;
    int fireCount = 1;
    int moveSpeedLevel = 0;

    bool isWallPassActive = false;
    bool hasWallPassRunOut = true;

    private:

    long long unsigned int wallPassTime = 5000000;

    Rectangle backgroundRect;
    MySprite *backgroundImage;
    MySprite *playerIconSprite;
    MySprite *bombUpSprite;
    MySprite *fireUpSprite;
    MySprite *speedUpSprite;
    MySprite *wallPassSprite;

    Font font;

    Text *bombsText;
    Text *fireText;
    Text *speedText;
    Text *wallPassText;

    Color _colorScheme;
    Color _textColor = BLACK;

    std::chrono::high_resolution_clock::time_point _wall_pass_timestamp;
};

#endif //BOMBERMAN_PLAYERSTATS_HPP
