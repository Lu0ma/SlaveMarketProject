#include "AnimationComponent.h"
#include <iostream>
#include "TextureManager.h"
#include "Actor.h"

AnimationComponent::AnimationComponent(Actor* _owner, const vector<AnimationData>& _animationsData)
                                     : Component(_owner)
{
    currentAnimation = nullptr;
    InitAnimations(_animationsData);
}


void AnimationComponent::InitAnimations(const vector<AnimationData>& _animationsData)
{
    Shape* _shape = owner->GetDrawable();

    int _index = 0;

    for (const AnimationData& _data : _animationsData)
    {
        new Animation(_data.name, this, _shape, _data);

        if (_index == 0)
        {
            RunAnimation(_data.name);
        }

        _index++;
    }
}


void AnimationComponent::RunAnimation(const string& _name)
{
    for (Animation* _animation : GetAllValues())
    {
        if (_name == _animation->GetID())
        {
            if (currentAnimation)
            {
                //system("cls");
                //cout << "Stop : " << currentAnimation->GetID() << endl;
                currentAnimation->Stop();
            }

            //cout << "Start : " << _animation->GetData().name << endl;
            currentAnimation = _animation;
            _animation->Start();
        }
    }
}