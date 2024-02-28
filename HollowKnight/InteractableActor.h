#pragma once
#include "Actor.h"
#include "Canvas.h"
class InteractableActor : public Actor
{
	CircleShape* sensorArea;
	static FloatRect detector;
	static Canvas* canvas;
public:
	InteractableActor(const string& _name , const ShapeData& _data ,const Vector2f& _sizeDetector);
public:
	// virtual void Speak();
	virtual void Update(const float _deltaTime);

	static void Verify();
};

