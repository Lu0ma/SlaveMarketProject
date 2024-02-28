#include "Animation.h"
#include "AnimationComponent.h"
#include "Timer.h"
#include "Macro.h"

Animation::Animation(const string& _name, AnimationComponent* _owner, Shape* _shape,
    const AnimationData& _data) : IManagable(_name)
{
    owner = _owner;
    shape = _shape;
    data = _data;
    Register();
}

void Animation::Register()
{
    owner->Add(id, this);
}

void Animation::SetNext()
{
    if (!CanNext())
    {
        if (!data.canLoop)
        {
            Stop();
            return;
        }

        Reset();
    }

    currentIndex++;

    const Vector2i& _start = GetNewStart();
    const int _sizeX = static_cast<int>(data.size.x);
    const int _sizeY = static_cast<int>(data.size.y);
    const IntRect& _rect = IntRect(_start.x, _start.y, _sizeX, _sizeY);
    shape->setTextureRect(_rect);
}

Vector2i Animation::GetNewStart()
{
    int _x = static_cast<int>(data.start.x);
    int _y = static_cast<int>(data.start.y);

    switch (data.readDirection)
    {
    case READ_DOWN:
        _y += static_cast<int>(currentIndex * data.size.y);
        break;

    case READ_RIGHT:
        _x += static_cast<int>(currentIndex * data.size.x);
        break;

    default:
        break;
    }

    return Vector2i(_x, _y);
}

void Animation::Start()
{
    SetNext();
    timer = new Timer(this, &Animation::SetNext, seconds(data.timeBetween), true, data.canLoop);
}

void Animation::Reset()
{
    currentIndex = -1;
}

void Animation::Stop()
{
    if (!timer) return;
    timer->Stop();
}