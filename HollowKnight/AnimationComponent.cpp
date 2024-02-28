#include "AnimationComponent.h"
#include <iostream>
#include "TextureManager.h"
#include "Actor.h"

AnimationComponent::AnimationComponent(Actor* _owner, const string& _path, const vector<AnimationData>& _animationsData,
    const AnimationDirection& _direction) : Component(_owner)
{
    InitAnimations(_path, _animationsData);
    currentIndex = -1;
    direction = _direction;
}

void AnimationComponent::InitAnimations(const string& _path, const vector<AnimationData>& _animationsData)
{
    for (const AnimationData& _data : _animationsData)
    {
        Shape* _shape = owner->GetDrawable();
        TextureManager::GetInstance().LoadWithRect(_shape, _path, IntRect(Vector2i(_data.start), Vector2i(_data.size)));
        owner->SetShape(_shape);
        new Animation(_data.name, this, _shape, _data);        
    }
}

void AnimationComponent::Update(const float _deltaTime)
{
    const int _newIndex = GetNextIndex(direction);
    if (currentIndex == _newIndex) return;

    system("cls");

    if (currentIndex != -1)
    {
        Animation* _currentAnimation = GetCurrentAnimation();
        if (!_currentAnimation) return;
        cout << "Stop : " << _currentAnimation->GetData().name << endl;
        _currentAnimation->Stop();
        currentIndex = -1;
    }

    Animation* _animation = GetAllValues()[_newIndex];
    cout << "Start : " << _animation->GetData().name << endl;
    _animation->Start();
    currentIndex = _newIndex;
}