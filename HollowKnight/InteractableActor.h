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
		return cursor && cursor->IsVisible()
			|| textScript && textScript->IsVisible();
	}
public:
	void OpenDiscussion()
	{
		cursor->SetVisible(true);
		textScript->SetVisible(false);
	}
	
public:
	InteractableActor(const string& _name, const ShapeData& _data);

private:
	void Verify();


protected:
	virtual void Register() override;
public:
	virtual void Init() override;
	virtual void Update(const float _deltaTime);
};