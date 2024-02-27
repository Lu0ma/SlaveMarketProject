#include "PlayerStat.h"

#define PATH_LIFE "UIs/Player/Life.png"
#define PATH_MANA_FULL "UIs/Player/ManaBar_Full.png"
#define PATH_MANA_EMPTY "UIs/Player/ManaBar_Empty.png"
#define PATH_GEO "UIs/Inventory/Geo.png"
#define FONT "Font.ttf"

PlayerStat::PlayerStat()
{
	canvas = nullptr;
	lifeCount = 3;
	lifeWigets = vector<ShapeWidget*>();
	manaBar = nullptr;
	geosCount = 0;
	geosCountText = nullptr;
}


void PlayerStat::Init()
{
	canvas = new Canvas("PlayerStats");

	#pragma region Mana

	const Vector2f& _manaPos = Vector2f(150.0f, 80.0f);
	const Vector2f& _manaSize = Vector2f(200.0f, 130.0f);
	manaBar = new ProgressBar(ShapeData(_manaPos, _manaSize, PATH_MANA_FULL),
							  canvas, PATH_MANA_EMPTY, ProgressType::PT_LEFT);
	canvas->AddWidget(manaBar);

	#pragma endregion

	#pragma region Life

	const Vector2f& _lifeSize = Vector2f(40.0f, 40.0f);
	const float _startLifePosX = _lifeSize.x + 145.0f;
	const float _lifePosY = _manaPos.y - 20.0f;
	const float _lifeGapX = 10.0f;

	for (int _index = 0; _index < lifeCount; _index++)
	{
		const float _lifePosX = _startLifePosX + _lifeSize.x * _index + _lifeGapX * _index;
		ShapeWidget* _life = new ShapeWidget(ShapeData(Vector2f(_lifePosX, _lifePosY), _lifeSize, PATH_LIFE));
		lifeWigets.push_back(_life);
		canvas->AddWidget(_life);
	}

	#pragma endregion

	#pragma region Geos

	const Vector2f& _geoPos = _manaPos + Vector2f(35.0f, 50.0f);
	const Vector2f& _geoSize = Vector2f(40.0f, 40.0f);
	ShapeWidget* _geoIcon = new ShapeWidget(ShapeData(_geoPos, _geoSize, PATH_GEO));
	canvas->AddWidget(_geoIcon);

	const Vector2f& _geoTextPos = _geoPos + Vector2f(25.0f, -15.0f);
	geosCountText = new Label(TextData(to_string(geosCount), _geoTextPos, FONT, 22));
	canvas->AddWidget(geosCountText);

	#pragma endregion
}

void PlayerStat::UpdateLife(const int _count)
{
	const int _lifesCount = GetLifesCount();
	const int _newLifesCount = + _count;
	if (_newLifesCount >= _lifesCount) return;

	lifeWigets.
}

void PlayerStat::AddGeos(const float _factor)
{
	geosCount += _factor;
	geosCountText->SetString(to_string(geosCount));
}