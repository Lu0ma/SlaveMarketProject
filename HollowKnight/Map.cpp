#include "Map.h"
#include "Macro.h"
#include "FileLoader.h"

#define LEVEL "Assets/Levels/SubLevel_"
#define PATH_MARCHAND "/UIs/Shop/Stand.png"
#define PATH_PNJ "/UIs/PNJ/PNJ.png"

Map::Map()
{

	bench = new Bench();

	merchand = new Merchand(ShapeData(Vector2f(300.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_MARCHAND));
	pnj = new NPC(STRING_ID("Villager"), ShapeData(Vector2f(150.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_PNJ));

	pnj = new InteractableActor(STRING_ID("Villageois"), ShapeData(Vector2f(150.0f, 0.0f), Vector2f(100.0f, 100.0f), " "));

	merchand = new Merchand(ShapeData(Vector2f(300.0f, 0.0f), Vector2f(100.0f, 100.0f),""), vector<string>());

	background = nullptr;

	barrack = nullptr;
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
	bench->Init();
	pnj->Init();
	merchand->Init();

	background = new ShapeObject(ShapeData(Vector2f(-300.0f, -SCREEN_HEIGHT + 35.0f), Vector2f(2340.0f, 985.0f), "/Levels/Environment_GROUND.png"));
	drawables.push_back(background);


	//TODO move
	barrack = new ShapeObject(ShapeData(Vector2f(1915.0f, -SCREEN_HEIGHT - 30.0f), Vector2f(3613.0f, 908.0f), "/Levels/Environment.png"));
	drawables.push_back(barrack);

	//TODO modify ?
	ShapeObject* _ground = new ShapeObject(ShapeData(Vector2f(-150.0f, 49.5f), Vector2f(5550.0f, 10.0f), ""));
	_ground->GetDrawable()->setFillColor(Color::Red);
	drawables.push_back(_ground);
	
}