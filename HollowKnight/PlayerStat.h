#pragma once
#include "Canvas.h"
#include "ProgressBar.h"
#include "Label.h"

class PlayerStat
{
	Canvas* canvas;
	
	// Life
	vector<ShapeWidget*> lifeWigets;

	// Mana
	ProgressBar* manaBar;

	// Geos
	int geosCount;
	Label* geosCountText;

private:
	int GetLifesCount() const
	{
		return static_cast<int>(lifeWigets.size());
	}

public:
	PlayerStat();

public:
	void Init();

	void UseMana(const float _factor);
	void UpdateLife(const int _count);
	void AddGeos(const float _factor);
};