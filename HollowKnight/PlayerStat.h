#pragma once
#include "Menu.h"
#include "ProgressBar.h"
#include "Timer.h"

#define PATH_LIFE "UIs/Player/Life/Life_"

class Player;
class PlayerAnimationComponent;
class PlayerMovementComponent;

class PlayerStat : public Menu
{
	// Life
	int currentLifesCount;
	int currentMaxLifesCount;
	vector<ShapeWidget*> lifeWigets;

	// Mana
	ProgressBar* manaBar;
	float manaUsed;
	float manaUsedLifespan;
	Timer* resetManaTimer;

	// Geos
	int geosCount;
	Label* geosCountText;

	// Components
	PlayerAnimationComponent* animation;
	PlayerMovementComponent* movement;

	int numberOfDeath;

public:
	void SetCurrentLife(const int _newLife)
	{
		currentLifesCount = _newLife;
	}
	int GetCurrentLife() const
	{
		return currentLifesCount;
	}
	int GetMaxLife() const
	{
		return currentMaxLifesCount;
	}
	int GetGeos() const
	{
		return geosCount;
	}
private:
	string ComputeLifePath(const bool _toAdd) const
	{
		return PATH_LIFE + to_string(_toAdd) + ".png";
	}

public:
	PlayerStat(Player* _player);

public:
	void Init();
	void UseMana(const float _factor);
	void StopUsingMana();
	void UpdateLife(const int _count);
	void AddLife();
	void UpdateGeos(const int _factor);
	void Death();
};