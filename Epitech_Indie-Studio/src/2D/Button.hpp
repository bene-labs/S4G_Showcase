/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#ifndef BOMBERMAN_BUTTON_HPP
#define BOMBERMAN_BUTTON_HPP

#include "../bomberman.hpp"
#include "Text.hpp"
#include "IGameObject2D.hpp"

class Button : public IGameObject2D {
    public:
    static std::map<int, std::string> specialKeys;


    enum BUTTON_STATE {
        IDLE,
        HOVERED,
        SELECTED
    };

    enum BUTTON_COMMANDS {
        ONE_PLAYER = 1,
        TWO_PLAYER = 2,
        THREE_PLAYER = 3,
        FOUR_PLAYER = 4,
        IGNORE = 1000,
        LOAD_GAME_SELECT = 1001,
        START_NEW_GAME = 1002,
        CONTINUE_GAME = 1003,
        INPUT = 1004,
        SINGLE_INPUT = 1005,
        LOAD_SETTINGS = 1006,
        UPDATE_KEY_BINDINGS = 107,
        VOLUME_INPUT = 108,
        BACK = 109
    };

    Button(Vector2 position, Vector2 size, Font textFont, std::string text = "press",
        BUTTON_COMMANDS onClickAction = IGNORE, const std::string &errorText = "error",
        Color textColor = BLACK, Color borderColor = WHITE, Color borderSecondaryColor = LIGHTGRAY,
        Color mainColor = DARKBLUE, Color hoverColor = BLUE, float borderThickness = .05f,
        Color errorTextColor = {117, 5, 5, 255}
    );
    ~Button();

    void setColors(Color borderColor = WHITE, Color borderHoverColor = LIGHTGRAY,
        Color mainColor = DARKBLUE, Color hoverColor = BLUE);
    void setError();
    void draw() override;
    int update() override;

    void setText(std::string newText);
    std::string getText();
    Text *_text;
    BUTTON_COMMANDS command;

    protected:
    int updateText();

    Rectangle outsideRec;
    Rectangle insideRec;
    //BUTTON_STATE state;

    int isSelected = 0;
    int isHovered = 0;
    bool _isErrorText = false;

    bool _isTextPromptBlink = true;
    long long blinkDelay = 300000;
    std::chrono::steady_clock::time_point lastBlink;

    Text *_errorText;
    Font _textFont;
    Color _textColor;

    std::map<int, Color> _insideColors;
    std::map<int, Color> _outsideColors;
};

#endif //BOMBERMAN_BUTTON_HPP
