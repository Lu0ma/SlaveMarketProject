#pragma once
#include "Component.h"
#include "Canvas.h"
#include "ProgressBar.h"
#include "Label.h"
#include "PlayerAnimationComponent.h"
#include "PlayerMovementComponent.h"

#define PATH_LIFE "UIs/Player/Life/Life_"

class PlayerStat : public Component
{
	Canvas* canvas;
	
	// Life
	int currentLifesCount;
	int currentMaxLifesCount;
	vector<ShapeWidget*> lifeWigets;

	// Mana
	ProgressBar* manaBar;

	// Geos
	int geosCount;
	Label* geosCountText;

	// Components
	PlayerAnimationComponent* animation;
	PlayerMovementComponent* movement;

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
	void Toggle()
	{
		canvas->SetVisibilityStatus(!canvas->IsVisible());
	}

public:
	PlayerStat(Actor* _owner);

public:
	void Init();

	void UseMana(const float _factor);
	void StopUsingMana();
	void UpdateLife(const int _count);
	void AddLife();
	void UpdateGeos(const int _factor);
};