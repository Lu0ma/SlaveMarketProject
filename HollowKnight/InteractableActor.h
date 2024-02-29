#pragma once
#include "Actor.h"
#include "Canvas.h"
#include "Label.h"

class InteractableActor : public Actor
{
	bool canVerify;
	bool Active;
	Canvas* cursor;
	Canvas* textScript;
	
public:
	void SetCanVerify(const bool _statue)
	{
		canVerify = _statue;
	}
	void SetCursorStatue(const bool _statue)
	{
		cursor->SetVisibilityStatus(_statue);
	}
	void SetTextStatue(const bool _statue)
	{
		textScript->SetVisibilityStatus(_statue);
	}
	Canvas* GetCursor() const
	{
		return cursor;
	}
	Canvas* GetTextScript()
	{
		return textScript;
	}
	
public:
	InteractableActor(const string& _name , const ShapeData& _data ,const Vector2f& _sizeDetector);

public:
	// virtual void Speak();
	virtual void Update(const float _deltaTime);
	void Verify();
	void Init();
	string Scrolling(const string& _text);
};