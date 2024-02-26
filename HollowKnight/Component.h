#pragma once

class Actor;

class Component
{
protected:
	Actor* owner;

public:
	Component(Actor* _owner);

public:
	virtual void Update(const float _deltaTime) { };
};