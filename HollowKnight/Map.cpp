#include "Map.h"
#include "Actor.h"
#include "Macro.h"
#include "FileLoader.h"

#define LEVEL "Assets/Levels/SubLevel_"
#define PATH_MARCHAND "/UIs/Shop/Stand.png"
#define PATH_PNJ "/UIs/PNJ/PNJ.png"

#define PATH_THIN "Levels/Thin.png"
#define PATH_MID "Levels/Mid.png"
#define PATH_WIDE "Levels/Wide.png"

Map::Map()
{
	bench = new Bench();
	pnj = new NPC(STRING_ID("Villageois"), ShapeData(Vector2f(150.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_PNJ));
	merchand = new Merchand(ShapeData(Vector2f(500.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_MARCHAND), vector<string>());
	background = nullptr;

	//TODO move
	barrack = nullptr;

	plateformsData = {
		{
			Vector2f(0.0f, 85.0f),
			PT_THIN,
		},
		{
			Vector2f(0.0f, 0.0f),
			PT_MID,
		},
		{
			Vector2f(0.0f , -85.0f),
			PT_WIDE,
		}
	};
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

	//analyser toutes les lignes, ligne par ligne a partir de _wallIndex + 1
	for (int _index = _wallIndex + 1, char _char = 0; _index < _path.size(); _index++)
	{
		const int _clampCamMaxY = stoi(GetStringAfterSymbol(GetLineByIndex(_index, _path), _symbol));

	}

	
	return _data;
}

void Map::InitPlateforms()
{

	for (int _index = 0; _index < plateformsData.size(); _index++)
	{
		Actor* _plateform = new Actor(STRING_ID("Plateform"), ShapeData(Vector2f(plateformsData[_index].position), Vector2f(plateformsData[_index].), plateformsData[_index].));
		drawables.push_back(_plateform);
	}
}

void Map::RetrievePlatformData(Vector2f& _size, string& _path)
{

}


void Map::Init()
{
	//for (int _index = 1; _index <= 1; _index++)
	//{
	//	const MapData& _data = LoadMapData(LEVEL + to_string(_index) + ".txt");
	//	cout << _data.backgroundPath << endl;
	//}

	bench->Init();
	pnj->Init();
	merchand->Init();

	background = new ShapeObject(ShapeData(Vector2f(-300.0f, -SCREEN_HEIGHT + 35.0f), Vector2f(2340.0f, 985.0f), "/Levels/Environment_GROUND.png"));
	drawables.push_back(background);

	//TODO move
	barrack = new ShapeObject(ShapeData(Vector2f(1915.0f, -SCREEN_HEIGHT - 30.0f), Vector2f(3613.0f, 908.0f), "/Levels/Environment.png"));
	drawables.push_back(barrack);

	//TODO modify ?
	Actor* _ground = new Actor("Ground", ShapeData(Vector2f(-150.0f, 49.5f), Vector2f(5550.0f, 10.0f), ""));
	_ground->GetDrawable()->setFillColor(Color::Transparent);

	InitPlateforms();

}