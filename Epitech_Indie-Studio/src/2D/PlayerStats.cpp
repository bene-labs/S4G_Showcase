//
// Created by Benedikt Mertes on 19.06.2021.
//

#include "PlayerStats.hpp"

PlayerStats::PlayerStats(Rectangle Background, Font textFont, Texture2D *spriteTextures,  Color colorScheme)
{
    backgroundRect = {Background.x, Background.y, Background.width, Background.height};
    font = textFont;
    _colorScheme = colorScheme;


    float borderSize = (backgroundRect.width < backgroundRect.height ? backgroundRect.width * 0.05f : backgroundRect.height * 0.05f);
    backgroundImage = new MySprite(spriteTextures[0], \
{backgroundRect.x + borderSize, backgroundRect.y + borderSize}, \
{backgroundRect.width - borderSize * 2, backgroundRect.height - borderSize * 2});


    playerIconSprite = new MySprite(spriteTextures[1], \
    {backgroundRect.x + borderSize, backgroundRect.y + borderSize}, \
    {backgroundRect.width * 0.2f * 4, backgroundRect.height * 0.9f * 3});

    auto iconWidth = (float) playerIconSprite->_sprite.width;
    auto iconHeight = (float) playerIconSprite->_sprite.height;
     Rectangle iconRect = {0, 0, iconWidth / 4, iconHeight / 3};
    if (colorScheme.r == BLUE.r && colorScheme.g == BLUE.g && colorScheme.b == BLUE.b && colorScheme.a == BLUE.a) {
        iconRect.x = (iconWidth / 4) * 2;
    } else if (colorScheme.r == YELLOW.r && colorScheme.g == YELLOW.g && colorScheme.b == YELLOW.b && colorScheme.a == YELLOW.a) {
        iconRect.y = iconHeight / 3;
    } else if (colorScheme.r == RED.r && colorScheme.g == RED.g && colorScheme.b == RED.b && colorScheme.a == RED.a) {
        iconRect.x = iconWidth / 4 * 3;
    }

    playerIconSprite->enableTextureRect(iconRect);

    bombsText = new Text(font, {backgroundRect.x + borderSize + backgroundRect.width * 0.35f, backgroundRect.y + borderSize, (backgroundRect.width - borderSize) * 0.1f, (backgroundRect.height - borderSize) * 0.4f}, "x3");
    bombUpSprite =  new MySprite(spriteTextures[2], \
    {backgroundRect.x + borderSize + backgroundRect.width * 0.25f, backgroundRect.y + borderSize + backgroundRect.height * 0.10f}, \
    {backgroundRect.width * 0.1f, backgroundRect.height * 0.3f});

    fireText = new Text(font, {backgroundRect.x + borderSize + backgroundRect.width * 0.35f, backgroundRect.y + borderSize + backgroundRect.height * 0.5f,
        (backgroundRect.width - borderSize) * 0.1f, (backgroundRect.height - borderSize) * 0.4f}, "x1");
    fireUpSprite =  new MySprite(spriteTextures[3], \
    {backgroundRect.x + borderSize + backgroundRect.width * 0.25f, backgroundRect.y + borderSize + backgroundRect.height * 0.55f}, \
    {backgroundRect.width * 0.1f, backgroundRect.height * 0.3f});

    speedText = new Text(font, {backgroundRect.x + borderSize + backgroundRect.width * 0.6f, backgroundRect.y + borderSize,
        (backgroundRect.width - borderSize) * 0.1f, (backgroundRect.height - borderSize) * 0.4f}, "x0");
    speedUpSprite =  new MySprite(spriteTextures[4], \
    {backgroundRect.x + borderSize + backgroundRect.width * 0.50f, backgroundRect.y + borderSize + backgroundRect.height * 0.10f}, \
    {backgroundRect.width * 0.1f, backgroundRect.height * 0.3f});

    wallPassText = new Text(font, {backgroundRect.x + borderSize + backgroundRect.width * 0.6f, backgroundRect.y + borderSize + backgroundRect.height * 0.45f,
        (backgroundRect.width - borderSize) * 0.15f, (backgroundRect.height - borderSize) * 0.5f}, "x0.0s");
    wallPassSprite =  new MySprite(spriteTextures[5], \
    {backgroundRect.x + borderSize + backgroundRect.width * 0.5f, backgroundRect.y + borderSize + backgroundRect.height * 0.55f}, \
    {backgroundRect.width * 0.1f, backgroundRect.height * 0.3f});
}


void PlayerStats::draw()
{
    DrawRectangle((int) backgroundRect.x, (int) backgroundRect.y, (int) backgroundRect.width, (int) backgroundRect.height, _colorScheme);
    backgroundImage->draw();
    playerIconSprite->draw();
    bombsText->draw();
    bombUpSprite->draw();
    fireText->draw();
    fireUpSprite->draw();
    speedText->draw();
    speedUpSprite->draw();
    wallPassText->draw();
    wallPassSprite->draw();
}

void PlayerStats::increaseSpeed()
{
    if (moveSpeedLevel < 10) {
        moveSpeedLevel++;
        speedText->replaceText("x" + std::to_string(moveSpeedLevel));
    }
}

void PlayerStats::increaseMaxBombs()
{
    bombMax++;
    bombCount++;
    bombsText->replaceText("x" + std::to_string(bombCount));
}

void PlayerStats::increaseFire()
{
    fireCount++;
    fireText->replaceText("x" + std::to_string(fireCount));
}

void PlayerStats::enableWallPass()
{
    isWallPassActive = true;
    hasWallPassRunOut = false;
    _wall_pass_timestamp = std::chrono::high_resolution_clock::now();
    wallPassText->text = "x5.0s";
}

int PlayerStats::update()
{
    if (isWallPassActive == true && hasWallPassRunOut == false) {

        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - _wall_pass_timestamp).count();

        if ( wallPassText->text[1] != '5' && (int) duration / 1000000 > 0 &&  (4 - (int) duration / 1000000) < (int) wallPassText->text[1] - '0') {
            wallPassText->text[1] -= 1;
            wallPassText->text[3] = '0';
        }
        if (wallPassText->text[3] == '0' && (int) (((duration - (1000000 * (int) (duration / 1000000))) / 100000)) == 1) {
            wallPassText->text[3] = '9';
            if (duration < 1000000)
                wallPassText->text[1] = '4';
        }
        else if ((duration / 100000) > 0 &&  10 - (int) (((duration - (1000000 * (int) (duration / 1000000))) / 100000)) < (int) wallPassText->text[3] - '0') {
            wallPassText->text[3] -= 1;
        }
        if (duration > wallPassTime) {
            hasWallPassRunOut = true;
            wallPassText->text[1] = '0';
            wallPassText->text[3] = '0';
        }
    }
    return 0;
}

void PlayerStats::decreaseBombs()
{
    bombCount--;
    if (bombCount == 0)
        bombsText->replaceText("x" + std::to_string(bombCount), RED);
    else
        bombsText->replaceText("x" + std::to_string(bombCount), _textColor);
}

void PlayerStats::increaseBombs()
{
    bombCount++;
    bombsText->replaceText("x" + std::to_string(bombCount), _textColor);
}

void PlayerStats::reset()
{
    bombCount = 3;
    bombMax = 3;
    isWallPassActive = false;
    hasWallPassRunOut = true;
    fireCount = 1;
    moveSpeedLevel = 0;

    bombsText->replaceText("x" + std::to_string(bombCount), _textColor);
    fireText->replaceText("x" + std::to_string(fireCount));
    speedText->replaceText("x" + std::to_string(moveSpeedLevel));
    wallPassText->text = "x0.0s";
}
