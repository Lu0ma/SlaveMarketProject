#pragma once
#include "InteractableActor.h"

class PNJ : public InteractableActor
{

public:
	PNJ(const ShapeData& _data);

public:
	virtual void Init() override;
};