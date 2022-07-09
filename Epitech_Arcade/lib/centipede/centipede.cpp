/*
** EPITECH PROJECT, 2024
** nibbler
** File description:
** Created by benedikt,
*/

#include <random>
#include "centipede.hpp"

Centipedes::Centipedes(int minSize, int maxSize)
{
    std::pair<int, int> position = {  -40, 0};
    SegmentCornerCases[std::make_pair<CentipedeSegments::Direction, CentipedeSegments::Direction>(CentipedeSegments::RIGHT, CentipedeSegments::UP)] = 3;
    SegmentCornerCases[std::make_pair<CentipedeSegments::Direction, CentipedeSegments::Direction>(CentipedeSegments::DOWN, CentipedeSegments::LEFT)] = 3;
    SegmentCornerCases[std::make_pair<CentipedeSegments::Direction, CentipedeSegments::Direction>( CentipedeSegments::DOWN, CentipedeSegments::RIGHT)] = 2;
    SegmentCornerCases[std::make_pair<CentipedeSegments::Direction, CentipedeSegments::Direction>(CentipedeSegments::LEFT, CentipedeSegments::UP)] = 2;
    SegmentCornerCases[std::make_pair<CentipedeSegments::Direction, CentipedeSegments::Direction>(CentipedeSegments::RIGHT, CentipedeSegments::DOWN)] = 1;
    SegmentCornerCases[std::make_pair<CentipedeSegments::Direction, CentipedeSegments::Direction>(CentipedeSegments::UP, CentipedeSegments::LEFT)] = 1;
    SegmentCornerCases[std::make_pair<CentipedeSegments::Direction, CentipedeSegments::Direction>(CentipedeSegments::UP, CentipedeSegments::RIGHT)] = 0;
    SegmentCornerCases[std::make_pair<CentipedeSegments::Direction, CentipedeSegments::Direction>(CentipedeSegments::DOWN, CentipedeSegments::LEFT)] = 3;

    setSizes(minSize, maxSize);
    spawn(position);
}

Centipedes::~Centipedes()
{
}

void Centipedes::move()
{
   /* std::chrono::steady_clock::time_point this_call_time = std::chrono::steady_clock::now();

   if (std::chrono::duration_cast<std::chrono::duration<double>>(
        this_call_time - last_move_time).count() < moves_per_second) {
        movedThisFrame = false;
        return;
    }
    */
    movedThisFrame = true;
    for (auto segment : segments)
        segment->move();
}

void Centipedes::draw(IGraphics *lib)
{
    for (auto segment : segments)
        segment->draw(sprites, lib,
        SegmentCornerCases);
}

void Centipedes::increaseSize()
{
    for (auto segment : segments)
        segment->add_new_segment();
}

void Centipedes::setDirection(const std::vector<std::pair<int, int>>& box_positions)
{
   if (!movedThisFrame)
        return;
    for (auto segment : segments) {
        if ((segment->getDirection() == CentipedeSegments::DOWN || segment->getDirection() == CentipedeSegments::UP) &&
            segment->_isTurnQueued) {
            segment->setDirections(segment->_turn);
            segment->_isTurnQueued = false;
        } else if ((segment->getDirection() == CentipedeSegments::RIGHT && \
    segment->getPosition().first >= ScreenData::WIDTH - ScreenData::TILE_WIDTH) \
 || isAnyDirectionalTileCollision(box_positions, CentipedeSegments::RIGHT,
            segment)) {
            segment->setDirections(CentipedeSegments::DOWN); //or box to right
            segment->_turn = CentipedeSegments::LEFT;
            segment->_isTurnQueued = true;
        } else if ((segment->getDirection() == CentipedeSegments::LEFT && \
    segment->getPosition().first <= 0) ||
            isAnyDirectionalTileCollision(box_positions,
                CentipedeSegments::LEFT, segment)) {
            segment->setDirections(CentipedeSegments::DOWN);
            segment->_turn = CentipedeSegments::RIGHT;
            segment->_isTurnQueued = true;
        }
    }
}

void Centipedes::updateSegmentDirections()
{
   if (!movedThisFrame)
        return;
    for (auto segment : segments)
        segment->updateDirections();
}

bool Centipedes::isCollisionWithObject(std::pair<int, int> position,
    bool completeCollison)
{
    for (auto segment : segments) {
        if (segment->isAnyCollision(position, completeCollison))
            return true;
    }
    return false;
}

bool Centipedes::isCollisionWithSelf()
{
    /*
    for (auto segment : segments)
    return segment->isSelfCollision();*/
    return false;
}

std::vector<std::pair<int, int>> Centipedes::getAllSegmentPositions()
{
    std::vector<std::pair<int, int>> res;
    for (auto segment : segments) {
        std::vector<std::pair<int, int>> positions = segment->getAllPositions();
        res.insert(res.end(), positions.begin(), positions.end());
    }
    return res;
}

bool Centipedes::isOutOfBounds()
{

    int i = 0;
    for (auto it = segments.begin(); it != segments.end(); it++, i++) {
        std::pair<int, int> position = segments[i]->getPosition();
        if (position.second >= ScreenData::HEIGHT) {
            if (!segments[i]->spawnedBySplit)
                this->fullKills++;
            segments.erase(it);
            return true;
        }
    }
    return false;
}

bool Centipedes::isAnyCollisionWithGivenPositions(
    std::vector<std::pair<int, int>> box_positions
)
{
    for (auto position : box_positions) {
        if (isCollisionWithObject(position, false))
            return true;
    }
    return false;
}

bool Centipedes::isAnyDirectionalTileCollision(
    const std::vector<std::pair<int, int>> &box_positions,
    CentipedeSegments::Direction direction, CentipedeSegments *Segments)
{
    std::pair<int, int> position = Segments->getPosition();
    for (auto box_position : box_positions) {
        switch (direction) {
        case CentipedeSegments::RIGHT:
            if (position.first + TILE_WIDTH == box_position.first && position.second == box_position.second)
                return true;
            break;
        case CentipedeSegments::LEFT:
            if (position.first == box_position.first + TILE_WIDTH && position.second == box_position.second)
                return true;
            break;
        default:
            break;
        }
    }
    return false;
}

std::pair<int, int> Centipedes::handleProjectileColision(
    const std::vector<std::pair<int, int>>& projectilePosition)
{
    int i = 0;
    for (auto it = segments.begin(); it != segments.end(); it++, i++) {
        std::vector<std::pair<int, int>> positionsSegment = segments[i]->getAllPositions();
        for (auto position1 : positionsSegment) {
            for (auto position2 : projectilePosition) {
                if (CentipedeSegments::isCollision(position1, position2, true)) {
                    std::pair<CentipedeSegments *, CentipedeSegments *> splitRes = segments[i]->splitFromPosition(position2);
                    if (splitRes.first == nullptr && splitRes.second == nullptr) {
                        if (!segments[i]->spawnedBySplit)
                            fullKills++;
                        kilCount++;
                        segments.erase(it);
                    } else if (splitRes.first == nullptr) {
                        if (!segments[i]->spawnedBySplit)
                            fullKills++;
                        kilCount++;
                        segments.erase(it);
                        segments.push_back(splitRes.second);
                    } else if (splitRes.second != nullptr) {
                        *it = splitRes.first;
                        segments.push_back(splitRes.second);
                    } else {
                        *it = splitRes.first;
                        kilCount++;
                    }
                    return position2;
                }
            }
        }
    }
    return std::pair<int, int>(-100, -100);
}

void Centipedes::setSizes(int min, int max)
{
    _minSize = min;
    _maxSize = max;
}

void Centipedes::spawn(std::pair<int, int> position)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(_minSize, _maxSize);
    segments.push_back(new CentipedeSegments(position, CentipedeSegments::HEAD, CentipedeSegments::RIGHT, distr(gen)));
}

bool Centipedes::allDead()
{
    if (segments.empty())
        return true;
    return false;
}

bool Centipedes::isCollisionWithPlayer(std::pair<int, int> position)
{
    int x = position.first;
    int y = position.second;

    for (auto segment : segments) {
        for (auto position2 : segment->getAllPositions()) {
            if (CentipedeSegments::isCollision(position, segment->getPosition(),
                true) \
                || CentipedeSegments::isCollision(position2, {x + 40, y}, true) ||
                CentipedeSegments::isCollision(position2, {x + 80, y}, true) ||
                CentipedeSegments::isCollision(position2, {x, y + 40}, true) ||
                CentipedeSegments::isCollision(position2, {x + 40, y + 40},true) ||
                CentipedeSegments::isCollision(position2, {x + 80, y + 40},true))
                return true;
        }
    }
    return false;
}
