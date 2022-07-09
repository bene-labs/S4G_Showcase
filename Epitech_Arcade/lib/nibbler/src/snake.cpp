/*
** EPITECH PROJECT, 2024
** nibbler
** File description:
** Created by benedikt,
*/

#include "../include/snake.hpp"

Snake::Snake(int size, float speed)
{
    std::pair<int, int> position = {240 + size * 80, 400};
    SegmentCornerCases[std::make_pair<SnakeSegments::Direction, SnakeSegments::Direction>(SnakeSegments::RIGHT, SnakeSegments::UP)] = 3;
    SegmentCornerCases[std::make_pair<SnakeSegments::Direction, SnakeSegments::Direction>(SnakeSegments::DOWN, SnakeSegments::LEFT)] = 3;
    SegmentCornerCases[std::make_pair<SnakeSegments::Direction, SnakeSegments::Direction>( SnakeSegments::DOWN, SnakeSegments::RIGHT)] = 2;
    SegmentCornerCases[std::make_pair<SnakeSegments::Direction, SnakeSegments::Direction>(SnakeSegments::LEFT, SnakeSegments::UP)] = 2;
    SegmentCornerCases[std::make_pair<SnakeSegments::Direction, SnakeSegments::Direction>(SnakeSegments::RIGHT, SnakeSegments::DOWN)] = 1;
    SegmentCornerCases[std::make_pair<SnakeSegments::Direction, SnakeSegments::Direction>(SnakeSegments::UP, SnakeSegments::LEFT)] = 1;
    SegmentCornerCases[std::make_pair<SnakeSegments::Direction, SnakeSegments::Direction>(SnakeSegments::UP, SnakeSegments::RIGHT)] = 0;
    SegmentCornerCases[std::make_pair<SnakeSegments::Direction, SnakeSegments::Direction>(SnakeSegments::DOWN, SnakeSegments::LEFT)] = 3;

    segments = new SnakeSegments(position, SnakeSegments::HEAD, SnakeSegments::RIGHT, size + 1);
}

Snake::~Snake()
{
}

void Snake::move()
{
    segments->move();
}

void Snake::draw(IGraphics *lib)
{
    segments->draw(sprites, lib,
        SegmentCornerCases);
}

void Snake::increaseSize()
{
    segments->add_new_segment();
}

void Snake::setDirection(std::string input)
{
    if (input == "left" && segments->getDirection() != SnakeSegments::RIGHT)
        segments->setDirections(SnakeSegments::LEFT);
    else if (input == "up" && segments->getDirection() != SnakeSegments::DOWN)
        segments->setDirections(SnakeSegments::UP);
    else if (input == "right" && segments->getDirection() != SnakeSegments::LEFT)
        segments->setDirections(SnakeSegments::RIGHT);
    else if (input == "down" && segments->getDirection() != SnakeSegments::UP)
        segments->setDirections(SnakeSegments::DOWN);
}

void Snake::updateSegmentDirections()
{
    segments->updateDirections();
}

bool Snake::isCollisionWithObject(std::pair<int, int> position,
    bool completeCollison)
{
    return segments->isAnyCollision(position, completeCollison);
}

bool Snake::isCollisionWithSelf()
{
    return segments->isSelfCollision();
}

std::vector<std::pair<int, int>> Snake::getAllSegmentPositions()
{
    return segments->getAllPositions();
}

bool Snake::isOutOfBounds()
{
    std::pair<int, int> position = segments->getPosition();
    if (position.first >= 1200 || position.first < 0 \
|| position.second >= 960 || position.second < 0)
        return true;
    return false;
}


