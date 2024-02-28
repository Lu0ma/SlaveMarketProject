#pragma once
#include "Actor.h"
#include "Inventory.h"
#include "Merchand.h"
#include "PlayerMovementComponent.h"
using namespace std;

struct PlayerStat
{
	int health;
	int maxHealth;

	int mana;
	int maxMana;

	int geosCount;

	bool isVisible ;

public:
	PlayerStat(int _health, int _maxHealth, int _mana, int _maxMana, int _geosCount, int _isVisible = false)
	{
		health = _health;
		maxHealth = _maxHealth;
		mana = _mana;
		maxMana = _maxMana;
		geosCount = _geosCount;
		isVisible = _isVisible;
	}

public:
	void Healing()
	{
		int minManaHealing = 2;
		if (mana< minManaHealing|| health>= maxHealth)
		{
			return;
		}

		mana -= minManaHealing;
		health += 1;

		if (health>= maxHealth)
		{
			health = maxHealth;
		}
	}
};

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
	void InitStats();

public:
	virtual void Update(const float _deltaTime) override;
	void Init();

private:
	void Right();
	void Left();
	void Up();

	void SwitchStatue();
};