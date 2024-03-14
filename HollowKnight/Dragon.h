#pragma once
#include "Actor.h"

class Dragon : public Actor
{
public:
	Dragon(const ShapeData& _data);

public:
	void PlayMusic();
};