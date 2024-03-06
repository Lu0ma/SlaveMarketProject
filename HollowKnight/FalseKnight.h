#pragma once
#include "Boss.h"

class FalseKnight : public Boss
{

public:
	FalseKnight(const ShapeData& _data);

public:
	virtual void Init() override;
	virtual void Attack(Player* _player) override;
	virtual void Death() override;
};