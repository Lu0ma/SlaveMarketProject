#pragma once
#include <SFML/Graphics.hpp>
#include "ShapeObject.h"
#include "Bench.h"
#include "Merchand.h"
#include "InteractableActor.h"
#include "Lift.h"
#include"Dragon.h"
#include"Grub.h"
#include"PNJ.h"
#include "CollectableActor.h"

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
	vector<CollectableActor*> items;
};

enum PlatformType
{
	PT_THIN,
	PT_MID,
	PT_WIDE,
};

struct PlatformData
{
	Vector2f position;
	PlatformType type;

	PlatformData(const Vector2f& _position, const PlatformType& _type)
	{
		position = _position;
		type = _type;
	}
};

class Map
{
	Grub* grub;
	Dragon* dragon;
	Bench* bench;
	Merchand* merchand;
	PNJ* pnj;
	vector<PlatformData> platformsData;
	vector<ShapeObject*> drawables;
	vector<Lift*> lifts;
	int currentLevel;

public:
	Dragon* GetDragon()const
	{
		return dragon;
	}
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
	Grub* GetGrub()
	{
		return grub;
	}

public:
	Map();
	~Map();

private:
	MapData LoadMapData(const string& _path);

	void InitPlatforms();

	void ComputePlatformType(const PlatformType& _type, Vector2f& _size, string& _path)
	{
		if (_type == PT_THIN)
		{
			_size = Vector2f(134.0f, 85.0f);
			_path = PATH_THIN;
		}
		else if (_type == PT_MID)
		{
			_size = Vector2f(198.0f, 85.0f);
			_path = PATH_MID;
		}
		else if (_type == PT_WIDE)
		{
			_size = Vector2f(263.0f, 85.0f);
			_path = PATH_WIDE;
		}

	}

public:
	void Init();
};