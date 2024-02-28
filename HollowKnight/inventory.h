#pragma once
#include "IManager.h"
#include "Item.h"
#include "Canvas.h"
#include "Button.h"
//#include "Game.h"
#define PATH_HEALTH_MASK "UIs/Inventory/HealthMasks/HealthMask_"
#define PATH_VESSEL "UIs/Inventory/Vessels/Vessel_"
#define PATH_MIRROR "UIs/Inventory/Mirrors/Mirror_"
#define PATH_SWORD "UIs/Inventory/Swords/Sword_"
#define PATH_VENGEFUL "UIs/Inventory/Vengefuls/Vengeful_"
#define PATH_SLAM "UIs/Inventory/Slams/Slam_"
#define PATH_SHRIEK "UIs/Inventory/Shrieks/Shriek_"

class Inventory : public IManager<int, Item>
{
	Canvas* canvas;
	Vector2i gridSize;
	Vector2f cellSize;
	vector<Button*> buttons;
	int stackSize;

	//TODO move
	ShapeWidget* pointer = nullptr;
	Label* descriptionTitle = nullptr;
	Label* descriptionText = nullptr;

	//TODO move
	int maskCount = 0;
	ShapeWidget* maskWidget = nullptr;

	int vesselCount = 0;
	ShapeWidget* vesselWidget = nullptr;

	int mirrorLevel = 0;
	ShapeWidget* mirrorWidget = nullptr;

	ShapeWidget* coreWidget = nullptr;

	bool isVengefulActive = false;
	ShapeWidget* vengefulWidget = nullptr;

	bool isSlamActive = false;
	ShapeWidget* slamWidget = nullptr;

	bool isShriekActive = false;
	ShapeWidget* shriekWidget = nullptr;

	int swordLevel = 0;
	ShapeWidget* swordWidget = nullptr;

	bool isWhirlwindUnlocked = false;
	ShapeWidget* whirlwindWidget = nullptr;

	bool isUppercutUnlocked = false;
	ShapeWidget* uppercutWidget = nullptr;

	bool isDashActive = false;
	ShapeWidget* dashWidget = nullptr;

private:
	string ComputeHealthMaskPath() const
	{
		return PATH_HEALTH_MASK + to_string(maskCount) + ".png";
	}
	string ComputeVesselPath() const
	{
		return PATH_VESSEL + to_string(vesselCount) + ".png";
	}
	string ComputeMirrorPath() const
	{
		return PATH_MIRROR + to_string(mirrorLevel) + ".png";
	}
	string ComputeSwordPath() const
	{
		return PATH_SWORD + to_string(swordLevel) + ".png";
	}
	string ComputeVengefulPath() const
	{
		return PATH_VENGEFUL + to_string(isVengefulActive) + ".png";
	}
	string ComputeSlamPath() const
	{
		return PATH_SLAM + to_string(isSlamActive) + ".png";
	}
	string ComputeShriekPath() const
	{
		return PATH_SHRIEK + to_string(isShriekActive) + ".png";
	}

public:
	Inventory();

private:
	Button* GetFirstAvailableButton() const;
	Item* FindItemData(const string& _path);

public:
	void Init();
	void Toggle()
	{
		canvas->SetVisibilityStatus(!canvas->IsVisible());
	}

	void UpdateMaskCount(const int _factor);
	void UpdateVesselCount(const int _factor);
	void UpdateMirrorLevel(const int _factor);
	void UpdateSwordLevel(const int _factor);
	void SetVengefulStatus(const bool _status);
	void SetSlamStatus(const bool _status);
	void SetShriekStatus(const bool _status);

	void AddItem(const int _count, const ItemData& _data);
	void CreateItemData(const ItemData& _data);
};