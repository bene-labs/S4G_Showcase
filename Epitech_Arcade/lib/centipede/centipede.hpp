/*
** EPITECH PROJECT, 2024
** nibbler
** File description:
** Created by benedikt,
*/

#ifndef NIBBLER_SNAKE_HPP
#define NIBBLER_SNAKE_HPP

#include <chrono>
#include "centipedeSegments.hpp"


class Centipedes {
    public:
    enum ScreenData {
        WIDTH = 1200,
        HEIGHT = 960,
        TILE_HEIGHT = 40,
        TILE_WIDTH = 40
    };

    explicit Centipedes(int minSize = 7, int maxSize = 15);
    ~Centipedes();

    void spawn(std::pair<int, int> position = {-40, 0});
    void move();
    void draw(IGraphics *lib);
    void increaseSize();
    void setDirection(const std::vector<std::pair<int, int>>& box_positions);
    void updateSegmentDirections();
    bool isCollisionWithObject(std::pair<int, int> position, \
        bool completeCollison);
    bool isCollisionWithPlayer(std::pair<int, int> position);
    bool isCollisionWithSelf();
    bool isOutOfBounds();
    void setSizes(int min, int max);
    bool allDead();

    std::pair<int, int> handleProjectileColision(const std::vector<std::pair<int, int>>& projectilePosition);

    std::vector<std::pair<int, int>> getAllSegmentPositions();

    void *sprites[4][4];
    int kilCount = 0;
    int fullKills = 0;

    private:

   /* std::chrono::steady_clock::time_point last_move_time = std::chrono::steady_clock::now();
    double moves_per_second = 0.25;*/
    bool movedThisFrame = false;

    bool isAnyCollisionWithGivenPositions(std::vector<std::pair<int, int>> box_positions);
    bool isAnyDirectionalTileCollision(
        const std::vector<std::pair<int, int>> &box_positions,
        CentipedeSegments::Direction direction, CentipedeSegments *Segments
    );

    std::vector<CentipedeSegments *> segments;
    std::map<std::pair<CentipedeSegments::Direction, CentipedeSegments::Direction>, int> SegmentCornerCases;

    int _minSize;
    int _maxSize;
};
#endif //centipede_cetipede_HPP
