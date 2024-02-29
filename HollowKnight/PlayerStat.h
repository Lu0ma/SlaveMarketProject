#pragma once
#include "Canvas.h"
#include "ProgressBar.h"
#include "Label.h"

#define PATH_LIFE "UIs/Player/Life/Life_"

class PlayerStat
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

	int damages;

public:
	int GetDamages()const
	{
		return damages;
	}

	int GetCurrentLife()const
	{
		return currentLifesCount;
	}

	int GetMaxLife()const
	{
		return currentMaxLifesCount;
	}
	
     void SetCurrentLife(const int _newLife)
	 {
		 currentLifesCount = _newLife;
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
	PlayerStat();

public:
	void Init();

	void UseMana(const float _factor);
	void UpdateLife(const int _count);
	void AddLife();
	void AddGeos(const int _factor);
};