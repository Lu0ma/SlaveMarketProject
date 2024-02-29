#pragma once
#include "Component.h"
#include "IManager.h"
#include "Animation.h"

class AnimationComponent : public Component, public IManager<string, Animation>
{
    Animation* currentAnimation;
    vector<string> animationNames;

public:
    Animation* GetCurrentAnimation() const
    {
        return currentAnimation;
    }
    const vector<string>& GetAnimationNames()
    {
        return animationNames;
    }

public:
    AnimationComponent(Actor* _owner, const vector<AnimationData>& _animationsData);

private:
    void InitAnimations(const vector<AnimationData>& _animationsData);

public:
    void RunAnimation(const string& _name);
};