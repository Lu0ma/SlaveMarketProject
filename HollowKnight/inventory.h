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

	ShapeWidget* pointer = nullptr;
	Label* descriptionTitle = nullptr;
	Label* descriptionText = nullptr;

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
	string ComputePath(const string& _path, const int _index) const
	{
		return _path + to_string(_index) + ".png";
	}
public:
	void Toggle()
	{
		canvas->SetVisibilityStatus(!canvas->IsVisible());
	}

public:
	Inventory();

private:
	Button* GetFirstAvailableButton() const;
	Item* FindItemData(const string& _path);

	void UpdateCount(ShapeWidget* _widget, int& _count, const string& _path,
		const int _max, const int _factor = 1);
	void UpdateTexture(ShapeWidget* _widget, const string& _path);

public:
	void Init();

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