#include "PlayerInfo.h"
#include "Game.h"

PlayerInfo::PlayerInfo(int _health, int _maxHealth, int _mana, int _maxMana, int _geosCount, int _visibility) : TextWidget(TextData(to_string(health) + "/" + to_string(maxHealth), Vector2f(20.0f, 20.0f), "TrajanProRegular.ttf"))
{
	health = _health;
	maxHealth = _maxHealth;
	mana = _mana;
	maxMana = _maxMana;
	geosCount = _geosCount;
	visibility = _visibility;

	InitInfo();
}

void PlayerInfo::Healing()
{
	int minManaHealing= 1;

	if (minManaHealing < mana)
	{
		return;
	}

	mana -= minManaHealing;
	health += 1;
}

void PlayerInfo::InitInfo()
{
	canvas = new Canvas("PlayerInfo", FloatRect(0, 0, 1, 1));

	const Vector2f& _windowSize = Game::GetWindowSize();
	healthBar = new TextWidget(TextData(to_string(health) + "/" + to_string(maxHealth), Vector2f(_windowSize.x / 100.0f * 1.0f, _windowSize.y / 100.0f * 1.0f), "TrajanProRegular.ttf"));
	manaBar = new TextWidget(TextData(to_string(mana) + "/" + to_string(maxMana), Vector2f(_windowSize.x / 100.0f * 1.0f, _windowSize.y / 100.0f * 5.0f), "TrajanProRegular.ttf"));
	geosCountText = new TextWidget(TextData(to_string(geosCount), Vector2f(_windowSize.x / 100.0f * 1.0f, _windowSize.y / 100.0f * 10.0f), "TrajanProRegular.ttf"));

	canvas->AddWidget(healthBar);
	canvas->AddWidget(manaBar);
	canvas->AddWidget(geosCountText);
}

void PlayerInfo::UpdateInfo()
{
}
