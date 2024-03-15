#pragma once

class Actor;

class Component
{
protected:
	Actor* owner;

public:
	Actor* GetOwner() { return owner; }

public:
	Component(Actor* _owner);

public:
	virtual void Init() { };
	virtual void Update(const float _deltaTime) { };
};