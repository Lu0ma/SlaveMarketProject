#pragma once
#include "Actor.h"
#include "Canvas.h"
#include "ShapeWidget.h"
#include "Label.h"

class InteractableActor : public Actor
{
	Canvas* canvas;
	ShapeWidget* cursor;
	Label* textScript;

private:
	bool NeedToVerify() const
	{
		return textScript->IsVisible();
	}

public:
	ShapeWidget* GetCursor() const 
	{
		return cursor;
	}
	Label* GetTextScript() const 
	{
		return textScript;
	}
	
public:
	InteractableActor(const string& _name, const ShapeData& _data);

private:
	virtual void Register() override;
	void Verify();

protected:
	virtual void CloseDiscussion();

public:
	virtual void Init() override;
	virtual void Update(const float _deltaTime);
	virtual void OpenDiscussion();
};