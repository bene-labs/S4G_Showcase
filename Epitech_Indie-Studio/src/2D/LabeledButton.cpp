/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/
#include "LabeledButton.hpp"

LabeledButton::LabeledButton(Vector2 position, Vector2 size, Font textFont, std::string text,
    std::string label, Vector2 labelOffset, Vector2 moseWheelMovement,
    BUTTON_COMMANDS onClickAction, const std::string &errorText, Color textColor, Color borderColor,
    Color borderSecondaryColor, Color mainColor, Color hoverColor, float borderThickness,
    Color errorTextColor
) : Button(position, size, textFont, text, onClickAction, errorText, textColor, borderColor, borderSecondaryColor,
mainColor, hoverColor, borderThickness)
{
    Rectangle labelRec = {outsideRec.x + labelOffset.x, outsideRec.y + labelOffset.y, \
(labelOffset.x == 0 ? outsideRec.width : abs(labelOffset.x)), (labelOffset.y == 0 ? outsideRec.height : abs(labelOffset.y))};
    realValue = text;
    _mouseWheelMovement = moseWheelMovement;
    labelText = new Text(textFont, labelRec, std::move(label), textColor);
}

void LabeledButton::draw()
{
    labelText->draw();
    if (command == INPUT || command == SINGLE_INPUT || command == VOLUME_INPUT)
        DrawRectangleRec(outsideRec, _outsideColors[isSelected]);
    else
        DrawRectangleRec(outsideRec, _outsideColors[isHovered]);
    DrawRectangleRec(insideRec, _insideColors[isHovered]);
    if (_isErrorText)
        _errorText->draw();
    else
        _text->draw();
}

int LabeledButton::update()
{
    insideRec.y -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.y;
    outsideRec.y -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.y;
    _text->_position.y -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.y;
    labelText->_position.y -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.y;
    insideRec.x -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.x;
    outsideRec.x -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.x;
    _text->_position.x -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.x;
    labelText->_position.x -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.x;
    _position.x -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.x;
    _position.y -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.y;
    _text->_textRect.x -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.x;
    _text->_textRect.y -= (GetMouseWheelMove()*scrollSpeed) * _mouseWheelMovement.y;


    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= _position.x && mousePos.x <= _position.x + _size.x && \
    mousePos.y >= _position.y && mousePos.y <= _position.y + _size.y) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (command == INPUT || command == SINGLE_INPUT || command == VOLUME_INPUT) {
                isSelected = 1;
            } else {
                return (command);
            }
        }
        isHovered = 1;
    } else {
        isHovered = 0;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            _isErrorText = false;
            if (command == INPUT || command == VOLUME_INPUT) {
                _isTextPromptBlink = true;
                _text->text[_text->text.size() - 1] = ' ';
                if (isSelected && _text->text != realValue) {
                    int text_value = std::atoi(_text->text.c_str());
                    if ((command == INPUT && text_value >= 1 && text_value <= 5000) || (command == VOLUME_INPUT && text_value >= 0 && text_value <= 500)) {
                        if (command == INPUT && labelText->text.find("\n(restart to apply)") == std::string::npos) {
                            labelText->text.append("\n(restart to apply)");
                            labelText->autoResizeText();
                        }
                        _text->text = std::to_string(text_value) + " ";
                        realValue = _text->text;
                        _text->autoResizeText();
                        if (command == VOLUME_INPUT) return VOLUME_INPUT;
                    } else if (((command == INPUT && text_value > 5000) || (command == VOLUME_INPUT && text_value > 500))) {
                        if (command == INPUT && labelText->text.find("\n(restart to apply)") == std::string::npos) {
                            labelText->text.append("\n(restart to apply)");
                            labelText->autoResizeText();
                        }
                        _text->text = (command == INPUT ? std::string("5000") : std::string("500")) + " ";
                        realValue = _text->text;
                        _text->autoResizeText();
                        if (command == VOLUME_INPUT) return VOLUME_INPUT;
                    } else {
                        _text->text = realValue;
                        _text->autoResizeText();
                    }
                }
            } else if (command == SINGLE_INPUT) {
                realValue = _text->text;
            }
            isSelected = 0;
        }
    }

    if (isSelected) {
        if (command == INPUT || command == SINGLE_INPUT || command == VOLUME_INPUT)
            return updateText();
    }
    return -1;
}

std::string LabeledButton::getValue() const
{
    return realValue;
}

LabeledButton::LabeledButton(Vector2 position, Vector2 size, Font textFont, int keyCode,
    std::string label, Vector2 labelOffset, Vector2 moseWheelMovement,
    Button::BUTTON_COMMANDS onClickAction, const std::string &errorText, Color textColor,
    Color borderColor, Color borderSecondaryColor, Color mainColor, Color hoverColor,
    float borderThickness, Color errorTextColor
    ): Button(position, size, textFont, "", onClickAction, errorText, textColor, borderColor, borderSecondaryColor,
    mainColor, hoverColor, borderThickness)
{
    Rectangle labelRec = {outsideRec.x + labelOffset.x, outsideRec.y + labelOffset.y, outsideRec.width, outsideRec.height};
    if (keyCode >= 32 && keyCode <= 125) {
        realValue = (char) keyCode;
        _text->text = realValue;
        _text->autoResizeText();
    } else {
        if (specialKeys.find(keyCode) != specialKeys.end()) {
            realValue = specialKeys[keyCode];
            _text->text = realValue;
            _text->autoResizeText();
        } else {
            realValue = specialKeys[0];
            _text->text = realValue;
            _text->autoResizeText();
        }
    }
    _mouseWheelMovement = moseWheelMovement;
    labelText = new Text(textFont, labelRec, std::move(label), textColor);
}