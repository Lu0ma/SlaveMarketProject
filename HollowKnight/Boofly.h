#pragma once
#include "Mob.h"
#include "Player.h"

class Boofly : public Mob
{
public:
	Boofly(const ShapeData& _data);

public:
	virtual void Init() override;
	virtual void Death() override;
	virtual void Attack(Player* _player) override;
};