#pragma once
#include "InteractableActor.h"

class PNJ : public InteractableActor
{
	int soundIndex;
public:
	PNJ(const ShapeData& _data);

public:
	virtual void Update(const float _deltaTime) override;
};