#pragma once
#include <SFML/Graphics.hpp>
#include "ShapeObject.h"
#include "Bench.h"
#include "Merchand.h"
#include "InteractableActor.h"
#include "Lift.h"
#include"Dragon.h"

using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PATH_THIN "Levels/Thin.png"
#define PATH_MID "Levels/Mid.png"
#define PATH_WIDE "Levels/Wide.png"

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

enum PlatformType
{
	PT_THIN,
	PT_MID,
	PT_WIDE,
};

struct PlateformData
{
	Vector2f position;
	PlatformType type;

	PlateformData(const Vector2f& _position, const PlatformType& _type)
	{
		position = _position;
		type = _type;
	}
};

class Map
{
	Dragon* dragon;
	Bench* bench;
	Merchand* merchand;
	InteractableActor* pnj;
	ShapeObject* background;
	ShapeObject* barrack;

	vector<PlateformData> plateformsData;

	vector<ShapeObject*> drawables;
	vector<Lift*> lifts;

public:
	Bench* GetBench() const
	{
		return bench;
	}
	vector<ShapeObject*> GetAllDrawables() const
	{
		return drawables;
	}
	vector<Lift*> GetAllLifts() const
	{
		return lifts;
	}

public:
	Map();
	~Map();

private:
	MapData LoadMapData(const string& _path);

	void InitPlateforms();
	 
	//TODO REMOVE ABSOLUTLY
	void InitPlateformsGUEZ();

	void ComputePlatformType(const PlatformType& _type, Vector2f& _size, string& _path)
	{
		if (_type == PT_THIN)
		{
			_size = Vector2f(134.0f, 85.0f);
			_path = PATH_THIN;
		}
	}

public:
	void Init();
};