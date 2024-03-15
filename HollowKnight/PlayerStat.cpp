#include "PlayerStat.h"
#include "PlayerAnimationComponent.h"
#include "PlayerMovementComponent.h"
#include "Game.h"
#include "TextureManager.h"
#include"FxManager.h"
#include "Timer.h"

#include <iostream>
#include"Game.h"
#include"DeathMob.h"

#define PATH_MANA_FULL "UIs/Player/Mana/ManaBar_Full.png"
#define PATH_MANA_EMPTY "UIs/Player/Mana/ManaBar_Empty.png"
#define PATH_GEO "UIs/Inventory/Geo.png"
#define FONT "Font.ttf"
#define PATH_DEATHMOB "Animations/DeathMob.png"

PlayerStat::PlayerStat(Player* _player) : Menu("PlayerStat", nullptr)
{
	currentLifesCount = 0;
	currentMaxLifesCount = 0;
	lifeWigets = vector<ShapeWidget*>();

	manaBar = nullptr;
	manaUsed = 0.0f;
	manaUsedLifespan = 3.0f;
	resetManaTimer = nullptr;

	geosCount = 0;
	geosCountText = nullptr;

	animation = _player->GetComponent<PlayerAnimationComponent>();
	movement = _player->GetComponent<PlayerMovementComponent>();

	numberOfDeath = 0;
}


void PlayerStat::Init()
{
	#pragma region Mana

	const Vector2f& _manaPos = Vector2f(150.0f, 80.0f);
	const Vector2f& _manaSize = Vector2f(200.0f, 130.0f);
	manaBar = new ProgressBar(ShapeData(_manaPos, _manaSize, PATH_MANA_EMPTY),
							  PATH_MANA_FULL, ProgressType::PT_BOTTOM);
	canvas->AddWidget(manaBar);
	canvas->AddWidget(manaBar->GetForeground());

	#pragma endregion

	#pragma region Life

	for (int _index = 0; _index < 3; _index++)
	{
		AddLife();
	}

	#pragma endregion

	#pragma region Geos

	const Vector2f& _geoPos = _manaPos + Vector2f(35.0f, 50.0f);
	const Vector2f& _geoSize = Vector2f(40.0f, 40.0f);
	ShapeWidget* _geoIcon = new ShapeWidget(ShapeData(_geoPos, _geoSize, PATH_GEO));
	canvas->AddWidget(_geoIcon);

	const Vector2f& _geoTextPos = _geoPos + Vector2f(25.0f, -5.0f);
	geosCountText = new Label(TextData(to_string(geosCount), _geoTextPos, FONT, 22), AT_LEFT);
	canvas->AddWidget(geosCountText);

	#pragma endregion
}


void PlayerStat::UseMana(const float _factor)
{
	const float _direction = Game::GetPlayer()->GetDrawable()->getScale().x;
	if (manaBar->GetCurrentValue() - _factor <= 0.0f)
	{
		animation->GetCurrentAnimation()->RunAnimation("StopRight", _direction);
		return;
	}

	FxManager::GetInstance().Run("FxChargingMana");
	animation->GetCurrentAnimation()->RunAnimation("RemoveMana", _direction);

	if (resetManaTimer) resetManaTimer->Stop();
	resetManaTimer = new Timer([&]() { StopUsingMana(); }, seconds(manaUsedLifespan));

	manaUsed += _factor;
	manaBar->ChangeValue(-_factor);

	if (manaUsed >= int(manaBar->GetMaxValue() / 3.0f))
	{
		FxManager::GetInstance().Run("FxMana");
		UpdateLife(1);
		StopUsingMana();
	}
}

void PlayerStat::StopUsingMana()
{
	manaUsed = 0.0f;
	resetManaTimer->Reset();
}

void PlayerStat::UpdateLife(const int _count)
{
	const int _currentLife = currentLifesCount + (_count < 0 ? -1 : 0);
	if (_currentLife >= currentMaxLifesCount || _currentLife < 0) return;

	if (ShapeWidget* _widget = lifeWigets[_currentLife])
	{
		const string& _path = ComputeLifePath(_count > 0);
		TextureManager::GetInstance().Load(_widget->GetObject(), _path);
	}

	currentLifesCount += _count;

	if (currentLifesCount == 0)
	{
		Death();
	}
}

void PlayerStat::AddLife()
{
	const Vector2f& _manaPos = Vector2f(150.0f, 80.0f);
	const Vector2f& _lifeSize = Vector2f(40.0f, 40.0f);
	const float _startLifePosX = _lifeSize.x + 145.0f;
	const float _lifePosY = _manaPos.y - 20.0f;
	const float _lifeGapX = 10.0f;

	const float _lifePosX = _startLifePosX + _lifeSize.x * currentMaxLifesCount + _lifeGapX * currentMaxLifesCount;
	ShapeWidget* _life = new ShapeWidget(ShapeData(Vector2f(_lifePosX, _lifePosY), _lifeSize, ComputeLifePath(false)));
	lifeWigets.push_back(_life);
	canvas->AddWidget(_life);

	currentMaxLifesCount++;
	UpdateLife(1);
}

void PlayerStat::UpdateGeos(const int _factor)
{
	geosCount += _factor;
	geosCountText->SetString(to_string(geosCount));
}


void PlayerStat::Death()
{
	numberOfDeath++;

	////TODO remove
	//for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
	//{
	//	if (DeathMob* _death = dynamic_cast<DeathMob*>(_actor))
	//	{
	//		// _death->SetToRemove(true);
	//		_death->GetDrawable()->setScale(Vector2f(0.0f, 0.0f)); ///TODO CHANGE
	//	}
	//}

	//Player* _player = Game::GetPlayer();
	//Vector2f _lastPos = _player->GetShapePosition();
	//DeathMob* _deathMob = new DeathMob("Death" + to_string(numberOfDeath), ShapeData(_lastPos, Vector2f(100.0f, 100.0f), PATH_DEATHMOB));
	//_deathMob->Init();

	if (Bench* _bench = Game::GetMap()->GetBench())
	{
		const Vector2f& _benchPos = _bench->GetShapePosition();
		Game::GetPlayer()->SetShapePosition(_benchPos);
	}

	//for (int _index = 0; _index < currentMaxLifesCount; _index++)
	//{
	//	_player->GetStats()->UpdateLife(1);
	//} 

	UpdateGeos(-geosCount);
}