/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/
#include "Rotation.hpp"

Rotation::Rotation(unsigned long rotateDelay, Vector3 initialRotation, Vector3 rotationVelocity) :
_delay(rotateDelay), _rotationVector(rotationVelocity), rotation(initialRotation)
{
    timer = std::chrono::steady_clock::now();
}

void Rotation::rotate()
{
    auto now = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::microseconds>(now - timer).count() >= _delay) {
        timer = now;
        rotation = {rotation.x + _rotationVector.x, rotation.y + _rotationVector.y, rotation.z + _rotationVector.z};
    }
}

float Rotation::getRotationAngle()
{
    if (rotation.x != 0)
        return rotation.x;
    if (rotation.y != 0)
        return rotation.y;
    if (rotation.z != 0)
        return rotation.z;
    return 0;
}
