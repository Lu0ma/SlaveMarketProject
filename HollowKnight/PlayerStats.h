#pragma once
//#include "Stat.h"
#include "ProgressBar.h"

struct PlayerStats
{
	//ChangingStat* health;
	//float regenCooldown;
	//ChangingStat* mana;
	//ChangingStat* thirst;
	//ChangingStat* hunger;

	PlayerStats(ProgressBar* _healthBar, ProgressBar* _manaBar,
				ProgressBar* _thirstBar, ProgressBar* _hungerBar)
	{
		/*health = new ChangingStat(1.0f, _healthBar);
		regenCooldown = 3.0f;
		mana = new ChangingStat(0.2f, _manaBar);
		thirst = new ChangingStat(-1.0f, _thirstBar);
		hunger = new ChangingStat(-0.3f, _hungerBar);*/
	}

	void UseMana(const float _mana)
	{
		//mana->Update(_mana);
	}

	void Drink(const float _water)
	{
		//thirst->Update(_water);
	}

	void Eat(const float _food)
	{
		//hunger->Update(_food);
	}

	void StopHealthRegen()
	{
		/*if (!health->updateTimer) return;

		health->updateTimer->Stop();
		new Timer([this]()
		{
			health->updateTimer = health->StartUpdateTimer();
		}, seconds(regenCooldown));*/
	}
};