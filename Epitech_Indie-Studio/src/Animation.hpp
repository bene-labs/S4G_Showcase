/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/

#ifndef BOMBERMAN_ANIMATION_HPP
#define BOMBERMAN_ANIMATION_HPP

#include "bomberman.hpp"


enum AnimationStates {
    PULSE,
    DEATH,
    IDLE,
    RUN,
    GET_UP,
    STILL
};

class Animation {
    public:
    Animation() = default;
    Animation(int frames, long long int animationDelay, bool timeByFrameRate = false);
    ~Animation();

    void assignNewAnimation(int frames, long long int animationDelay, AnimationStates type);

    void setFrame(int frame);
    AnimationStates update(AnimationStates state);
    int getFrame();
    AnimationStates getState();

    private:
    void increaseFrame();
    void decreaseFrame();

    std::chrono::steady_clock::time_point timer;

    bool animateByFPS = false;
    long long totalUpdatesCalled = 0;
    unsigned int _curFrame = 0;
    unsigned int _maxFrames = 0;
    long long int _animationDelay = 0;
    bool reverse = false;

    std::map<AnimationStates, long unsigned int> animationDelays = {
        {IDLE, 30000}, {RUN, 20000}, {DEATH, 25000}, {GET_UP, 20000}};
    std::map<AnimationStates, int> framesPerAnimation = {
        {IDLE, 175}, {RUN, 22}, {DEATH, 67}, {GET_UP, 67}};
    AnimationStates curAnimationState = IDLE;
};

#endif //BOMBERMAN_ANIMATION_HPP
