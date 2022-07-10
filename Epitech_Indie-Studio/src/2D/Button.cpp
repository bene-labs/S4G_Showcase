/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/
#include "Button.hpp"

#include <utility>

std::map<int, std::string> Button::specialKeys = {
    {KEY_UP, "(up)"},
    {KEY_DOWN, "(down)"},
    {KEY_RIGHT, "(right)"},
    {KEY_LEFT, "(left)"},
    {KEY_TAB, "(TAB)"},
    {KEY_INSERT, "(INSERT)"},
    {KEY_DELETE, "(DELETE)"},
    {KEY_LEFT_SHIFT, "(left-shift)"},
    {KEY_RIGHT_SHIFT, "(right-shift)"},
    {KEY_LEFT_CONTROL, "(left-control)"},
    {KEY_RIGHT_CONTROL, "(right-control)"},
    {KEY_ENTER, "(enter)"},
    {KEY_LEFT_ALT, "(left-alt)"},
    {KEY_RIGHT_ALT, "(right-alt)"},

    //keypad keys
    {KEY_KP_0, "(KP-0)"},
    {KEY_KP_1, "(KP-1)"},
    {KEY_KP_2, "(KP-2)"},
    {KEY_KP_3, "(KP-3)"},
    {KEY_KP_4, "(KP-4)"},
    {KEY_KP_5, "(KP-5)"},
    {KEY_KP_6, "(KP-6)"},
    {KEY_KP_7, "(KP-7)"},
    {KEY_KP_8, "(KP-8)"},
    {KEY_KP_9, "(KP-9)"},
    {KEY_KP_DECIMAL, "(KP-DECIMAL)"},
    {KEY_KP_DIVIDE, "(KP-DIVIDE)"},
    {KEY_KP_MULTIPLY, "(KP-MULTIPLY)"},
    {KEY_KP_SUBTRACT, "(KP-SUBTRACT)"},
    {KEY_KP_ADD, "(KP-ADD)"},
    {KEY_KP_ENTER, "(KP-ENTER)"},
    {KEY_KP_EQUAL, "(KP-EQUAL)"},

};

Button::Button(Vector2 position, Vector2 size, Font textFont, std::string text,
    BUTTON_COMMANDS onClickAction, const std::string &errorText, Color textColor, Color borderColor,
    Color borderSecondaryColor, Color mainColor, Color hoverColor, float borderThickness,
    Color errorTextColor)
{
    _position = position;
    _size = size;

    outsideRec.width = size.x;
    outsideRec.height = size.y;
    outsideRec.x = position.x;
    outsideRec.y = position.y;

    float borderSize = (size.x < size.y ?  size.x * borderThickness : size.y * borderThickness);

    insideRec.x =  position.x + borderSize;
    insideRec.y =  position.y + borderSize;
    insideRec.width = size.x - 2 * borderSize;
    insideRec.height = size.y - 2 * borderSize;

    _outsideColors[0] = borderColor;
    _outsideColors[1] = borderSecondaryColor;

    _insideColors[0] = mainColor;
    _insideColors[1] = hoverColor;


    _textColor = textColor;
    _textFont = textFont;

    if (onClickAction == INPUT || onClickAction == VOLUME_INPUT) {
        lastBlink = std::chrono::steady_clock::now();
        text += ' ';
    }

    _text = new Text(textFont, insideRec, text, textColor);
    _errorText = new Text(textFont, insideRec,  errorText, errorTextColor);
    command = onClickAction;
}

Button::~Button()
{
}

void Button::draw()
{
    if (command == INPUT || command == SINGLE_INPUT)
        DrawRectangleRec(outsideRec, _outsideColors[isSelected]);
    else
        DrawRectangleRec(outsideRec, _outsideColors[isHovered]);
    DrawRectangleRec(insideRec, _insideColors[isHovered]);
    if (_isErrorText)
        _errorText->draw();
    else
        _text->draw();
}

int Button::updateText()
{
    //GamePad 1-17

    int key = GetCharPressed();

    if (key >= 32 && key <= 125)
    {
        if (key >= 32 && key <= 125) {
            if (command == SINGLE_INPUT)
                _text->text = (char)std::toupper(key);

            else
                _text->text.insert(_text->text.size() - 1, 1, (char)key);
            _text->autoResizeText();
            if (command == SINGLE_INPUT) return SINGLE_INPUT;
        }
    }

    // special keys
    if (command == SINGLE_INPUT) {
        key = GetKeyPressed();
        if (specialKeys.find(key) != specialKeys.end()) {
            _text->text = specialKeys[key];
            _text->autoResizeText();
            return SINGLE_INPUT;
        }

        int gamePadButton = GetGamepadButtonPressed();

        if (gamePadButton >= 1 && gamePadButton <= 17) {
            _text->text = "GamePad " + std::to_string(gamePadButton) + " ";
            _text->autoResizeText();
            return SINGLE_INPUT;
        }
    }
    if (command == SINGLE_INPUT)
        return -1;
    if (IsKeyPressed(KEY_BACKSPACE) && _text->text.size() > 1) {
            _text->text.erase(_text->text.size() - 2, 1);
            _text->autoResizeText();
    }
    if (_isTextPromptBlink)
        _text->text[_text->text.size() - 1] = '_';
    else
        _text->text[_text->text.size() - 1] = ' ';

    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::microseconds>(now - lastBlink).count() >= blinkDelay) {
        _isTextPromptBlink = !_isTextPromptBlink;
        lastBlink = now;
    }
    return -1;
}


int Button::update()
{
    _text->update();
    _errorText->update();

    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= _position.x && mousePos.x <= _position.x + _size.x && \
    mousePos.y >= _position.y && mousePos.y <= _position.y + _size.y) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (command == INPUT || command == SINGLE_INPUT) {
                isSelected = 1;
            } else {
                return (command);
            }
        }
        isHovered = 1;
    } else {
        isHovered = 0;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isSelected = 0;
            _isErrorText = false;
            if (command == INPUT) {
                _isTextPromptBlink = true;
                _text->text[_text->text.size() - 1] = ' ';
            }
        }
    }

    if (isSelected) {
        if (command == INPUT || command == SINGLE_INPUT)
            return updateText();
    }
    return -1;
}

void Button::setText(std::string newText)
{
    _text->replaceText(std::move(newText));
}

void Button::setColors(Color borderColor, Color borderHoverColor, Color mainColor, Color hoverColor)
{
    _insideColors[0] = mainColor;
    _insideColors[1] = hoverColor;
    _outsideColors[0] = borderColor;
    _outsideColors[1] = borderHoverColor;
}

void Button::setError()
{
    _isErrorText = true;
}

std::string Button::getText()
{
    return _text->text;
}