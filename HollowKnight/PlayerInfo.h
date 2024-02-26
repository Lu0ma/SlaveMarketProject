#pragma once
#include "TextWidget.h"
#include "Canvas.h"

class PlayerInfo : public TextWidget
{
	Canvas* canvas;

	TextWidget* healthBar;
	int health;
	int maxHealth;

	TextWidget* manaBar;
	int mana;
	int maxMana;

	TextWidget* geosCountText;
	int geosCount;

	bool visibility;

public:
	void SetVisibilityPlayerInfo(bool _visibility)
	{
		visibility = _visibility;
	}
	void SetMaxHealth(int _maxHealth)
	{
		maxHealth = _maxHealth;
	}
	void SetMaxMana(int _maxMana)
	{
		maxMana = _maxMana;
	}
	void SetGeosCount(int _geosCount)
	{
		geosCount = _geosCount;
	}

	int GetMaxHealth()
	{
		return maxHealth;
	}
	int GetMaxMana()
	{
		return maxMana;
	}
	int GetGeosCount()
	{
		return geosCount;
	}
	
public:
	PlayerInfo(int _health, int _maxHealth, int _mana,int _maxMana, int _geosCount, int _visibility= true);


public:
	void Healing();
	void InitInfo();
	void UpdateInfo();


};

