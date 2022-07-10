/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#include "bomberman.hpp"

#ifndef BOMBERMAN_ROTATION_HPP
#define BOMBERMAN_ROTATION_HPP

class Rotation {
    public:
    Rotation(long unsigned int rotateDelay = 25000, Vector3 initialRotation = {0, 0, 0}, Vector3 rotationVelocity = {0, 1.5, 0});
    ~Rotation() = default;

    void rotate();
    float getRotationAngle();

    Vector3 rotation;
    private:
    std::chrono::steady_clock::time_point timer;
    long unsigned int _delay;
    Vector3 _rotationVector;
};

#endif //BOMBERMAN_ROTATION_HPP
