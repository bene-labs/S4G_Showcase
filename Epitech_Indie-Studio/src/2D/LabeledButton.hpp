/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#ifndef BOMBERMAN_LABELEDBUTTON_HPP
#define BOMBERMAN_LABELEDBUTTON_HPP

#include "Button.hpp"

//for use on settings screen
class LabeledButton : public Button {
    public:
    LabeledButton(Vector2 position, Vector2 size, Font textFont, std::string text = "press",
        std::string label = "button:", Vector2 labelOffset = {-50, 0}, Vector2 moseWheelMovement = {0, 0},
        BUTTON_COMMANDS onClickAction = IGNORE, const std::string &errorText = "error",
        Color textColor = DARKBLUE, Color borderColor = BLUE, Color borderSecondaryColor = DARKBLUE,
        Color mainColor = BLACK, Color hoverColor = DARKGRAY, float borderThickness = .05f,
        Color errorTextColor = {117, 5, 5, 255}
    );
    LabeledButton(Vector2 position, Vector2 size, Font textFont, int keyCode = 0,
        std::string label = "button:", Vector2 labelOffset = {-50, 0}, Vector2 moseWheelMovement = {0, 0},
        BUTTON_COMMANDS onClickAction = IGNORE, const std::string &errorText = "error",
        Color textColor = DARKBLUE, Color borderColor = BLUE, Color borderSecondaryColor = DARKPURPLE,
        Color mainColor = BLACK, Color hoverColor = DARKGRAY, float borderThickness = .05f,
        Color errorTextColor = {117, 5, 5, 255}
    );

    Text *labelText;
    std::string realValue;
    float scrollSpeed = 5;

    void draw() override;
    int update() override;

    std::string getValue() const;

    private:
    Vector2 _mouseWheelMovement;
};

#endif //BOMBERMAN_LABELEDBUTTON_HPP
