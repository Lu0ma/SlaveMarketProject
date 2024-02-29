#pragma once
#include "Actor.h"
#include "Canvas.h"
#include "Label.h"
class InteractableActor : public Actor
{
	bool canVerify;
	bool Active;
	Canvas* canvas;
	
public:
	InteractableActor(const string& _name , const ShapeData& _data ,const Vector2f& _sizeDetector);
public:
	// virtual void Speak();

	Canvas* GetCanvas() const
	{
		return canvas;
	}
	void SetCanVerify(const bool _statue)
	{
		canVerify = _statue;
	}
	void SetCanvaStatue(const bool _statue)
	{
		canvas->SetVisibilityStatus(_statue);
	}
	virtual void Update(const float _deltaTime);

	void Verify();

	void Init();
};

