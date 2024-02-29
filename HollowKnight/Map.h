#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct WallData
{
	Vector2f position;
	Vector2f size;
	string path;
};

struct MapData
{
	string backgroundPath;
	Vector2f backgroundPos;
	Vector2f backgroundSize;

	Vector2f clampCamMin;
	Vector2f clampCamMax;

	vector<WallData> walls;
};

class Map
{

private:
	MapData LoadMapData(const string& _path);

public:
	void Init();
};