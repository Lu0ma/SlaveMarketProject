#pragma once
#include "Actor.h"
#include "Inventory.h"
#include "Merchand.h"
#include "PlayerMovementComponent.h"
#include"AnimationComponent.h"
using namespace std;

struct PlayerStat
{
	int health;
	int maxHealth;

	int mana;
	int maxMana;

	int geosCount;

	bool isVisible ;
	int damages;

	int GetDamages()const
	{
		return damages;
	}

public:
	PlayerStat(int _health, int _maxHealth, int _mana, int _maxMana, int _geosCount, const int _damages,
		int _isVisible = false)
	{
		health = _health;
		maxHealth = _maxHealth;
		mana = _mana;
		maxMana = _maxMana;
		geosCount = _geosCount;
		damages = _damages;
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
	void SpecialAttack();
};