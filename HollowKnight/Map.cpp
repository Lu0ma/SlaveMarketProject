#include "Map.h"
#include "Macro.h"
#include "FileLoader.h"

#define LEVEL "Assets/Levels/SubLevel_"

Map::Map()
{

	bench = new Bench();
	bench->Init();

	merchand = new Merchand(ShapeData(Vector2f(300.0f, 0.0f), Vector2f(100.0f, 100.0f), "PATH_MARCHAND"));
	merchand->Init();

	pnj = new NPC(STRING_ID("Villager"), ShapeData(Vector2f(150.0f, 0.0f), Vector2f(100.0f, 100.0f), "PATH_PNJ"));
	pnj->Init();

	background = nullptr;
}

MapData Map::LoadMapData(const string& _path)
{
	MapData _data;
	const string& _symbol = " = ";
	
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

	return _data;
}

void Map::Init()
{
	//for (int _index = 1; _index <= 1; _index++)
	//{
	//	const MapData& _data = LoadMapData(LEVEL + to_string(_index) + ".txt");
	//	cout << _data.backgroundPath << endl;
	//}
	
	background = new ShapeObject(ShapeData(Vector2f(-640.0f, -360.0f), Vector2f(2340.0f, 985.0f), "/Levels/Environment_GROUND.png"));
}