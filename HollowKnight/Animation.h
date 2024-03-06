#pragma once
#include "IManagable.h"
#include "Timer.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class AnimationComponent;

enum AnimationDirection
{
    ANIM_DIR_NONE,
    ANIM_DIR_LEFT,
    ANIM_DIR_LEFT_UP,
    ANIM_DIR_UP,
    ANIM_DIR_RIGHT_UP,
    ANIM_DIR_RIGHT,
    ANIM_DIR_RIGHT_DOWN,
    ANIM_DIR_DOWN,
    ANIM_DIR_LEFT_DOWN,
};

enum ReadDirection
{
    READ_DOWN, READ_RIGHT
};

struct AnimationData
{
    bool canLoop;
    int count;
    float timeBetween;
    string name;
    Vector2f start;
    Vector2f size;
    ReadDirection readDirection;
    string linkedAnimation;

    AnimationData() = default;
    AnimationData(const string& _name, const Vector2f& _start, const Vector2f& _size, const ReadDirection& _readDirection,
                  const bool _canLoop, const int _count, const float _timeBetween, const string& _linkedAnimation = "")
    {
        name = _name;
        start = _start;
        size = _size;
        readDirection = _readDirection;
        canLoop = _canLoop;
        count = _count;
        timeBetween = _timeBetween;
        linkedAnimation = _linkedAnimation;
    }
};


class Animation : public IManagable<string>
{
    AnimationComponent* owner;
    int currentIndex;
    string path;
    AnimationData data;
    Shape* shape;
    Timer* timer;
    float directionX;

public:
    AnimationData GetData() const
    {
        return data;
    }
    bool CanNext() const
    {
        return currentIndex < data.count - 1;
    }
    Shape* GetSprite() const
    {
        return shape;
    }
    float GetDirectionX()
    {
        return directionX;
    }
    // /!\ MUST BE 1 OR -1
    void SetDirectionX(const float _directionX)
    {
        directionX = _directionX;
    }
    void StopLoopAnimation()
    {
        data.canLoop = false;
    }
public:
    Animation(const string& _name, AnimationComponent* _owner, Shape* _shape,
        const AnimationData& _data);

private:
    virtual void Register() override;
    void SetNext();
    Vector2i GetNewStart();

public:
    void Start(const float _directionX);
    void Reset();
    void Stop();
};