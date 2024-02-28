#pragma once
#include "Actor.h"
#include "PlayerStat.h"
#include "Inventory.h"

using namespace std;

class Player : public Actor
{
	PlayerStat* stats;
	Inventory* inventory;

	//TODO move
	Merchand* merchand;
	PlayerMovementComponent* movement;
	Canvas* canvas;
	Label* healthBar;
	Label* manaBar;
	Label* geosCountText;
	bool isPlay;

public:
	PlayerStat* GetStats() const
	{
		return stats;
	}
	Inventory* GetInventory() const
	{
		return inventory;
	}
	
	void SetVisibilityPlayerStats(bool _isVisible)
	{
		stats->isVisible = _isVisible;
	}

	bool IsPlay(bool _isPlay)
	{
		return isPlay = _isPlay;
	}
public:
	Player(const string& _name, const ShapeData& _data);

private:
	void SetupPlayerInput();

public:
	void Init();


private:
	void Right();
	void Left();
	void Up();
	void SwitchStatue();
};