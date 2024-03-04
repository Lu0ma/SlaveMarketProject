#pragma once
#include "Actor.h"
#include "Canvas.h"
#include "ShapeWidget.h"
#include "Label.h"

class InteractableActor : public Actor
{
	Canvas* canvas;
	bool isOpen;

	// Interaction
	ShapeWidget* interactionBG;
	Label* interactionText;

	// Discussion
	ShapeWidget* discussionBG;
	Label* discussionText;


public:
	void SetIsOpen(const bool _status)
	{
		isOpen = _status;
	}

public:
	InteractableActor(const string& _name, const ShapeData& _data);

private:
	virtual void Register() override;
	void Verify();

public:
	virtual void Init() override;
	virtual void Update(const float _deltaTime);
	virtual void OpenDiscussion();
	virtual void CloseDiscussion();
};