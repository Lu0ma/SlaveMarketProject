#include "Map.h"
#include "Actor.h"
#include "CollectableActor.h"
#include "Lift.h"
#include "Macro.h"
#include "FileLoader.h"

#define LEVEL "Assets/Levels/SubLevel_1.txt"
#define PATH_BENCH "Map/Bench.png"
#define PATH_STAND "/UIs/Shop/Stand.png"
#define PATH_PNJ "/Characters/PNJ/PNJA.png"
#define PATH_MERCHAND "/Characters/PNJ/Merchand.png"
#define PATH_DRAGON "/Animations/walla.png"
#define PATH_GRUB "/Animations/Grub.png"

Map::Map()
{
	pnj = new PNJ(ShapeData(Vector2f(150.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_PNJ));
	grub = new Grub(ShapeData(Vector2f(950.0f, 0.0f), Vector2f(75.0f, 100.0f), PATH_GRUB));
	dragon = new Dragon(ShapeData(Vector2f(700.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_DRAGON));
	bench = new Bench(ShapeData(Vector2f(300.0f, 5.0f), Vector2f(176.0, 80.0f), PATH_BENCH));
	merchand = new Merchand(ShapeData(Vector2f(500.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_MERCHAND));
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

	//background
	_data.backgroundPath = GetStringAfterSymbol(GetLineByText("BackgroundPath", _path), _symbol);

	const float _bgPosX = stof(GetStringAfterSymbol(GetLineByText("BackgroundPosX", _path), _symbol));
	const float _bgPosY = stof(GetStringAfterSymbol(GetLineByText("BackgroundPosY", _path), _symbol));
	_data.backgroundPos = Vector2f(_bgPosX, _bgPosY);

	const float _bgSizeX = stof(GetStringAfterSymbol(GetLineByText("BackgroundSizeX", _path), _symbol));
	const float _bgSizeY = stof(GetStringAfterSymbol(GetLineByText("BackgroundSizeY", _path), _symbol));
	_data.backgroundPos = Vector2f(_bgSizeX, _bgSizeY);

	const float _clampCamMinX = stof(GetStringAfterSymbol(GetLineByText("ClampCamMinX", _path), _symbol));
	const float _clampCamMinY = stof(GetStringAfterSymbol(GetLineByText("ClampCamMinY", _path), _symbol));
	_data.clampCamMin = Vector2f(_bgPosX, _bgPosY);

	const float _clampCamMaxX = stof(GetStringAfterSymbol(GetLineByText("ClampCamMaxX", _path), _symbol));
	const float _clampCamMaxY = stof(GetStringAfterSymbol(GetLineByText("ClampCamMaxY", _path), _symbol));
	_data.clampCamMax = Vector2f(_bgPosX, _bgPosY);

	//walls
	const string& _wallSymbol = "walls = [";
	const int _wallIndex = GetIndexByText(_wallSymbol, _path);
	int _index = _wallIndex + 2;

	bool _isEndOfWalls;
	do 
	{
		const int _wallPositionX = stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		const int _wallPositionY = stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));
		_index++;
		PlatformType _wallType = static_cast<PlatformType>(stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol)));
		_index++;
		PlatformData _platform = PlatformData(Vector2f((float)_wallPositionX, (float)_wallPositionY), _wallType);
		platformsData.push_back(_platform);
		_index +=2;
		_isEndOfWalls = ContainsText("]", GetLineByIndex(_index - 1, _path));

	} while (!_isEndOfWalls);

	InitPlateforms();
	return _data;
}

void Map::InitPlateforms()
{
	Vector2f _size;
	string _filePath;
	for (int _index = 0; _index < platformsData.size(); _index++)
	{
		ComputePlatformType(platformsData[_index].type, _size, _filePath);
		new Actor(STRING_ID("Plateform"), ShapeData(platformsData[_index].position, _size, _filePath), CT_BLOCK);
	}
}

void Map::Init()
{
	LoadMapData(LEVEL);
	bench->Init();
	merchand->Init();
	pnj->Init();

	ShapeObject* _background = new ShapeObject(ShapeData(Vector2f(-300.0f, -SCREEN_HEIGHT), Vector2f(2340.0f, 985.0f), "Levels/Environment_GROUND.png"));
	_background->GetDrawable()->setOrigin(0.0f, 0.0f);
	drawables.push_back(_background);

	//TODO move
	ShapeObject* _barrack = new ShapeObject(ShapeData(Vector2f(1915.0f, -SCREEN_HEIGHT - 100.0f + 20.0f), Vector2f(3613.0f, 908.0f), "Levels/Environment.png"));
	_barrack->GetDrawable()->setOrigin(0.0f, 0.0f);
	drawables.push_back(_barrack);

	//TODO move
	ShapeObject* _arena = new ShapeObject(ShapeData(Vector2f(3721.5f, -SCREEN_HEIGHT - 200.0f + 20.0f), Vector2f(1920.0f, 1080.0f), "Levels/Arena.jpg"));
	_arena->GetDrawable()->setOrigin(0.0f, 0.0f);
	drawables.push_back(_arena);

	//TODO modify ?
	Actor* _ground = new Actor("Ground", ShapeData(Vector2f(-100.0f, 0.0f), Vector2f(20000.0f, 10.0f), ""), CT_BLOCK);
	_ground->GetDrawable()->setFillColor(Color::Red);

	new CollectableActor(STRING_ID("Vessel"), ShapeData(Vector2f(-250.0f, 30.5f), Vector2f(50.0f, 50.0f), "UIs/Inventory/Vessels/Vessel_3.png"),
		30.0f, "Vessel", "Le truc qui regen la mana", IT_VESSEL);

	new CollectableActor(STRING_ID("Item"), ShapeData(Vector2f(-350.0f, 30.5f), Vector2f(50.0f, 50.0f), "UIs/Inventory/Item.png"),
		30.0f, "Item", "Ceci est un item", IT_ITEM);

	new CollectableActor(STRING_ID("ItemE"), ShapeData(Vector2f(-400.0f, 30.5f), Vector2f(50.0f, 50.0f), "UIs/Inventory/Item.png"),
		30.0f, "Item", "Ceci est un ", IT_ITEM);

	new CollectableActor(STRING_ID("Item2"), ShapeData(Vector2f(-450.0f, 30.5f), Vector2f(50.0f, 50.0f), "UIs/Inventory/Item.png"),
		30.0f, "Item", "Ceci", IT_ITEM);

	Lift* _lift = new Lift(ShapeData(Vector2f(-350.0f, 500.0f), Vector2f(250.0f, 250.0f), "Lift.png"));
	lifts.push_back(_lift);
}