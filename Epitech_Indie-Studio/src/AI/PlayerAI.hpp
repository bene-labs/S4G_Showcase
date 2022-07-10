/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

/*
###########
#         #
# # # # # #
#         #
# # # # # #
#         #
###########
 */

#ifndef BOMBERMAN_PLAYERAI_HPP
#define BOMBERMAN_PLAYERAI_HPP

#include "../Game.hpp"

typedef struct position {
    int x;
    int y;
} vector2D_t;

class PlayerAI {
    enum BOARD {
        WIDTH = 21,
        HEIGHT = 13,
        BOMB = -10
    };

    public:
    enum DESIRED_OBJECTS {
        NONE = -9,
        CHEST = -8,
        SAFE_SPACE = -7,
        POWER_UP = -2,
        ENEMY_PLAYER = -1,

    };

    PlayerAI(Player *parent);

    void update(std::list<IGameObject *> objects);
    private:

    bool checkPositionIsGoal(int x, int y);

    void determineGoal();
    int calcPath(vector2D_t goal, int x, int y, int curDistance, int maxDistance = 1000);
    //int calcPathRec(vector2D_t goal, vector2D_t startIntersection, int maxDistance = 1000);

    std::list<IGameObject *> objects;
    Player *_parent;
    vector2D_t _pos;
    vector2D_t _goal;
    int distanceToGoal;
    DESIRED_OBJECTS _goalType;
    int _distanceToGoal;
    std::vector<std::vector<int>> valueMap;
    std::vector<std::vector<int>> valueMapBuffer;

    std::vector<std::pair<vector2D_t, std::pair<int, int>>> intersections;
    std::vector<std::vector<int>> pathMap;
    std::vector<std::vector<int>> pathMapBuffer;
};

#endif //BOMBERMAN_PLAYERAI_HPP