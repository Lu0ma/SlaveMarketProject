#include "Map.h"
#include "Actor.h"
#include "CollectableActor.h"
#include "Lift.h"
#include "Macro.h"
#include "FileLoader.h"
#include "TextureManager.h"
#include "Game.h"
#include "Item.h"
#include "Enemy.h"
#include "Boss.h"
#include "Mob.h"
#include "InteractableActor.h"
#include "FalseKnight.h"
#include "Game.h"


#define PATH_BENCH "Map/Bench.png"
#define PATH_STAND "/UIs/Shop/Stand.png"
#define PATH_PNJ "/Characters/PNJ/PNJA.png"
#define PATH_MERCHAND "/Characters/PNJ/Merchand.png"
#define PATH_DRAGON "Animations/dragon.png"
#define PATH_GRUB "/Animations/Grub.png"

Map::Map()
{
	//pnj = new PNJ(ShapeData(Vector2f(150.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_PNJ));
	//grub = new Grub(ShapeData(Vector2f(950.0f, 0.0f), Vector2f(75.0f, 100.0f), PATH_GRUB));
	//dragon = new Dragon(ShapeData(Vector2f(700.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_DRAGON));
	//bench = new Bench(ShapeData(Vector2f(300.0f, 5.0f), Vector2f(176.0, 80.0f), PATH_BENCH));
	//merchand = new Merchand(ShapeData(Vector2f(500.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_MERCHAND));
	currentLevel = 1;
}

Map::~Map()
{
	for (ShapeObject* _object : drawables)
	{
		delete _object;
	}
}


MapData Map::LoadMapData(const string& _path)
{
	MapData _data;
	const string& _symbol = " = ";

#pragma region Background
	_data.backgroundPath = GetStringAfterSymbol(GetLineByText("BackgroundPath", _path), _symbol);
	cout << _data.backgroundPath << endl;

	const float _bgPosX = stof(GetStringAfterSymbol(GetLineByText("BackgroundPosX", _path), _symbol));
	const float _bgPosY = stof(GetStringAfterSymbol(GetLineByText("BackgroundPosY", _path), _symbol));
	_data.backgroundPos = Vector2f(_bgPosX, _bgPosY);

	const float _bgSizeX = stof(GetStringAfterSymbol(GetLineByText("BackgroundSizeX", _path), _symbol));
	const float _bgSizeY = stof(GetStringAfterSymbol(GetLineByText("BackgroundSizeY", _path), _symbol));
	_data.backgroundSize = Vector2f(_bgSizeX, _bgSizeY);

	/*const float _clampCamMinX = stof(GetStringAfterSymbol(GetLineByText("ClampCamMinX", _path), _symbol));
	const float _clampCamMinY = stof(GetStringAfterSymbol(GetLineByText("ClampCamMinY", _path), _symbol));
	_data.clampCamMin = Vector2f(_bgPosX, _bgPosY);*/

	const float _clampCamMaxX = stof(GetStringAfterSymbol(GetLineByText("ClampCamMaxX", _path), _symbol));
	const float _clampCamMaxY = stof(GetStringAfterSymbol(GetLineByText("ClampCamMaxY", _path), _symbol));
	_data.clampCamMax = Vector2f(_bgPosX, _bgPosY);

	

#pragma endregion

	int _index;

#pragma region Items

	const string& _itemSymbol = "items = [";
	const int _itemIndex = GetIndexByText(_itemSymbol, _path);
	_index = _itemIndex + 2;
	bool _isEndOfItem;
	do
	{
		// Recupérer les informations de l'item, augmenter l'index a chaque fois
		const string& _itemName = GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol);
		_index++;
		const float _itemPositionX = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _itemPositionY = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _itemSizeX = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _itemSizeY = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const string& _itemPath = GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol);
		cout << _itemPath << endl;
		_index++;
		const string& _itemDesc = GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol);
		_index++;
		const float _range = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const ItemType& _itemType = static_cast<ItemType>(stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol)));
		_index++;

		CollectableActor* _item =
			new CollectableActor(STRING_ID(_itemName), ShapeData(Vector2f(_itemPositionX, _itemPositionY), Vector2f(_itemSizeX, _itemSizeY), _itemPath),
				_range, _itemDesc, _itemName, _itemType);
		//CollectableActor* _item = new CollectableActor(_itemName, ShapeData(, Vector2f(_itemSizeX, _itemSizeY), _itemPath), _range, _itemType);
		// itemData.push_back(_item->GetItemData());
		_index += 2;
		_isEndOfItem = ContainsText("]", GetLineByIndex(_index - 1, _path));
		cout << "ITEM CREE" << endl;
	} while (!_isEndOfItem);


#pragma endregion

#pragma region Platform

	/*const string& _platformSymbol = "platforms = [";
	const int _platformIndex = GetIndexByText(_platformSymbol, _path);
	_index = _platformIndex + 2;

	bool _isEndOfPlatform;
	do
	{
		const int _platformPositionX = stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const int _platformPositionY = stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		PlatformType _platformType = static_cast<PlatformType>(stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol)));
		_index++;
		PlatformData _platform = PlatformData(Vector2f((float)_platformPositionX, (float)_platformPositionY), _platformType);
		platformsData.push_back(_platform);
		_index += 2;
		_isEndOfPlatform = ContainsText("]", GetLineByIndex(_index - 1, _path));

	} while (!_isEndOfPlatform);*/

#pragma endregion

#pragma region Grounds

	const string& _groundSymbol = "grounds = [";
	const int _groundIndex = GetIndexByText(_groundSymbol, _path);
	_index = _groundIndex + 2;
	bool _isEndOfGround;
	do
	{
		// Recupérer les informations du ground, augmenter l'index a chaque fois
		const float _groundPositionX = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _groundPositionY = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _groundSizeX = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _groundSizeY = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const CollisionType& _groundCollisionType = static_cast<CollisionType>(stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol)));
		_index++;

		// Créer avec les infos
		Actor* _ground = new Actor(STRING_ID("Ground"), ShapeData(Vector2f(_groundPositionX, _groundPositionY), Vector2f(_groundSizeX, _groundSizeY), ""), _groundCollisionType);
		_ground->GetDrawable()->setFillColor(Color::Red);

		_index += 2;
		_isEndOfGround = ContainsText("]", GetLineByIndex(_index - 1, _path));
	} while (!_isEndOfGround);

#pragma endregion

#pragma region Enemies 

	const string& _enemySymbol = "enemies = [";
	const int _enemyIndex = GetIndexByText(_enemySymbol, _path);
	_index = _enemyIndex + 2;
	bool _isEndOfEnemy;
	int _enemyIndexType = 0; // Initialize with a default value
	do
	{
		// Recupérer les informations du ground, augmenter l'index a chaque fois
		const EnemyType& _enemyType = static_cast<EnemyType>(stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol)));
		_index++;
		if (_enemyType == BOSS)
		{
			const BossType& _enemyIndexType = static_cast<BossType>(stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol)));
		}
		else if (_enemyType == MOB)
		{
			const MobType& _enemyIndexType = static_cast<MobType>(stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol)));
		}
		_index++;
		const float _enemyPositionX = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _enemyPositionY = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _enemySizeX = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _enemySizeY = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const string& _enemyPath = GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol);
		_index++;

		// Créer avec les infos
		if (_enemyIndexType == (int)BOSS)
		{
			FalseKnight* _falseKnight = new FalseKnight(ShapeData(Vector2f(_enemyPositionX, _enemyPositionY), Vector2f(_enemySizeX, _enemySizeY)));
			_falseKnight->Init();
			_falseKnight->GetDrawable()->setFillColor(Color::Transparent);
			// new Boss(ShapeData(Vector2f(_enemyPositionX, _enemyPositionY), Vector2f(_enemySizeX, _enemySizeY)));
		}
		else if (_enemyIndexType == (int)MOB)
		{
			new Mob(ShapeData(Vector2f(_enemyPositionX, _enemyPositionY), Vector2f(_enemySizeX, _enemySizeY), _enemyPath));
		}
		else
		{
			cout << "EPIC FAIL" << endl;
		}

		_index += 2;
		_isEndOfEnemy = ContainsText("]", GetLineByIndex(_index - 1, _path));
	} while (!_isEndOfEnemy);

#pragma endregion

#pragma region NPCS
	const string& _npcSymbol = "npcs = [";
	const int _npcIndex = GetIndexByText(_npcSymbol, _path);
	_index = _npcIndex + 2;
	bool _isEndOfNPC;

	do
	{
		// Recupérer les informations de npc, augmenter l'index a chaque fois
		const NPCType& _npcType = static_cast<NPCType>(stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol)));
		_index++;
		const float _npcPositionX = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _npcPositionY = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _npcSizeX = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _npcSizeY = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const string& _npcText = GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol);
		_index++;

		if (_npcType == MERCHAND)
		{
			new Merchand(ShapeData(Vector2f(_npcPositionX, _npcPositionY), Vector2f(_npcSizeX, _npcSizeY)));
		}
		else if (_npcType == NPC)
		{
			new PNJ(ShapeData(Vector2f(_npcPositionX, _npcPositionY), Vector2f(_npcSizeX, _npcSizeY)));
		}

		_index += 2;
		_isEndOfNPC = ContainsText("]", GetLineByIndex(_index - 1, _path));
	} while (!_isEndOfNPC);
#pragma endregion

#pragma region Environment

	const string& _environmentSymbol = "Environment = [";
	const int _environmentIndex = GetIndexByText(_environmentSymbol, _path);
	_index = _environmentIndex + 2;
	bool _isEndOfEnvironment;

	do
	{
		const float _environmentPositionX = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _environmentPositionY = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _environmentSizeX = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const float _environmentSizeY = stof(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const string& _environmentPath = GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol);
		_index++;

		ShapeObject(ShapeData(Vector2f(_environmentPositionX, _environmentPositionY),
			Vector2f(_environmentSizeX, _environmentSizeY), _environmentPath));


		_index += 2;
		_isEndOfEnvironment = ContainsText("]", GetLineByIndex(_index - 1, _path));
	} while (!_isEndOfEnvironment);

#pragma endregion


	InitPlatforms();
	return _data;
}

void Map::InitPlatforms()
{
	Vector2f _size;
	string _filePath;
	for (int _index = 0; _index < platformsData.size(); _index++)
	{
		ComputePlatformType(platformsData[_index].type, _size, _filePath);

		Actor* _actor = new Actor(STRING_ID("Plateform"), ShapeData(platformsData[_index].position, _size, _filePath), CT_BLOCK);
	}
}

void Map::Init()
{
	MapData _mapdata = LoadMapData(GetLevelFromIndex(currentLevel));
	//bench->Init();
	//merchand->	Init();
	//pnj->Init();



	// BACKGROUND LOAD
	ShapeObject* _background = new ShapeObject(ShapeData(_mapdata.backgroundPos + Vector2f(0, -_mapdata.backgroundSize.y + 220), _mapdata.backgroundSize, _mapdata.backgroundPath));
	_background->GetDrawable()->setOrigin(0.0f, 0.0f);
	drawables.push_back(_background);

	////TODO move
	//ShapeObject* _barrack = new ShapeObject(ShapeData(Vector2f(1915.0f, -SCREEN_HEIGHT - 100.0f + 20.0f), Vector2f(3613.0f, 908.0f), "Levels/Environment.png"));
	//_barrack->GetDrawable()->setOrigin(0.0f, 0.0f);
	//drawables.push_back(_barrack);

	////TODO move ARRENE
	//ShapeObject* _arena = new ShapeObject(ShapeData(Vector2f(3721.5f, -SCREEN_HEIGHT - 200.0f + 20.0f), Vector2f(1920.0f, 1080.0f), "Levels/Arena.jpg"));
	//_arena->GetDrawable()->setOrigin(0.0f, 0.0f);
	//drawables.push_back(_arena);

	/*Lift* _lift = new Lift(ShapeData(Vector2f(-350.0f, 500.0f), Vector2f(250.0f, 250.0f), "Lift.png"));
	lifts.push_back(_lift);*/
}