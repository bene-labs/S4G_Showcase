/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by Benedikt Mertes,
*/
#include "Animation.hpp"

Animation::Animation(int frames, long long int animationDelay, bool timeByFrameRate) : _maxFrames(frames), animateByFPS(timeByFrameRate)
{
    timer = std::chrono::steady_clock::now();
}

Animation::~Animation()
{
}

int Animation::getFrame()
{
    return _curFrame;
}

void Animation::increaseFrame()
{
    if (_curFrame >= _maxFrames -1)
        _curFrame = 0;
    else
        _curFrame++;
}


AnimationStates Animation::update(AnimationStates state)
{
    if (curAnimationState != state) {
        curAnimationState = state;
        switch (state) {
        case GET_UP:
            reverse = true;
            _curFrame = framesPerAnimation[GET_UP] - 1;
            break;
        default:
            _curFrame = 0;
            reverse = false;
            break;
        }
        if (framesPerAnimation.find(state) != framesPerAnimation.end()) {
            _maxFrames = framesPerAnimation[state];
        }
        if (animationDelays.find(state) != animationDelays.end()) {
            _animationDelay = animationDelays[state];
        }
    }


    if (animateByFPS && totalUpdatesCalled % _animationDelay == 0) {
        increaseFrame();
    } else if (curAnimationState != STILL) {
        std::chrono::steady_clock::time_point curTime = std::chrono::steady_clock::now();
        long long timeSinceLastAnimationFrame = std::chrono::duration_cast<std::chrono::microseconds>(curTime - timer).count();

        if (timeSinceLastAnimationFrame >= _animationDelay) {
            timer = std::chrono::steady_clock::now();
            if (reverse)
                decreaseFrame();
            else
                increaseFrame();
            if (curAnimationState == GET_UP && _curFrame == 0)
                curAnimationState = IDLE;
            else if (curAnimationState == DEATH && _curFrame >= framesPerAnimation[DEATH] - 1)
                curAnimationState = STILL;
        }
    }

    totalUpdatesCalled++;
    return curAnimationState;
}

void Animation::assignNewAnimation(int frames, long long int animationDelay, AnimationStates type)
{
    curAnimationState = type;
    _maxFrames = frames;
    _curFrame = 0;
    _animationDelay = animationDelay;
    timer = std::chrono::steady_clock::now();
}

void Animation::setFrame(int frame)
{
    _curFrame = frame;
}

void Animation::decreaseFrame()
{
    if (_curFrame <= 0)
        _curFrame = _maxFrames -1;
    else
        _curFrame--;
}

AnimationStates Animation::getState()
{
    return curAnimationState;
}
