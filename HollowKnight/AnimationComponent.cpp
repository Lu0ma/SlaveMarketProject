#include "AnimationComponent.h"
#include <iostream>
#include "TextureManager.h"
#include "Actor.h"

AnimationComponent::AnimationComponent(Actor* _owner) : Component(_owner)
{
    currentAnimation = nullptr;
    animationNames = vector<string>();
}


void AnimationComponent::InitAnimations(const vector<AnimationData>& _animationsData)
{
    Shape* _shape = owner->GetDrawable();

    int _index = 0;

    for (const AnimationData& _data : _animationsData)
    {
        animationNames.push_back(_data.name);
        new Animation(_data.name, this, _shape, _data);

        if (_index == 0)
        {
            RunAnimation(_data.name, 1.0f);
        }

        _index++;
    }
}


void AnimationComponent::RunAnimation(const string& _name, const float _directionX)
{
    for (Animation* _animation : GetAllValues())
    {
        if (_name == _animation->GetID())
        {
            if (currentAnimation)
            {
                if(_name == currentAnimation->GetID()) return;

                //system("cls");
                //cout << "Stop : " << currentAnimation->GetID() << endl;
                currentAnimation->Stop();
            }

            //cout << "Start : " << _animation->GetData().name << endl;
            currentAnimation = _animation;
            _animation->Start(_directionX);
        }
    }
}