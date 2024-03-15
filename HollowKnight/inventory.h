#pragma once
#include "Menu.h"
#include "IManager.h"
#include "Item.h"

#define PATH_HEALTH_MASK "UIs/Inventory/HealthMasks/HealthMask_"
#define PATH_VESSEL "UIs/Inventory/Vessels/Vessel_"
#define PATH_MIRROR "UIs/Inventory/Mirrors/Mirror_"
#define PATH_SWORD "UIs/Inventory/Swords/Sword_"
#define PATH_VENGEFUL "UIs/Inventory/Vengefuls/Vengeful_"
#define PATH_SLAM "UIs/Inventory/Slams/Slam_"
#define PATH_SHRIEK "UIs/Inventory/Shrieks/Shriek_"

class Inventory : public Menu, public IManager<int, Item>
{
	Vector2i gridSize;
	Vector2f cellSize;
	Vector2f windowSize;
	Vector2f halfSize;
	float gridSizeX;
	float gridSizeY;

	vector<Button*> buttons;
	int stackSize;

	Label* descriptionTitle;
	Label* descriptionText;

	int maskCount;
	ShapeWidget* maskWidget;

	int vesselCount;
	ShapeWidget* vesselWidget;

	int mirrorLevel;
	ShapeWidget* mirrorWidget;

	ShapeWidget* coreWidget;

	bool isVengefulActive;
	ShapeWidget* vengefulWidget;

	bool isSlamActive;
	ShapeWidget* slamWidget;

	bool isShriekActive;
	ShapeWidget* shriekWidget;

	int swordLevel;
	ShapeWidget* swordWidget;

	bool isWhirlwindUnlocked;
	ShapeWidget* whirlwindWidget;

	bool isUppercutUnlocked;
	ShapeWidget* uppercutWidget;

	bool isDashActive;
	ShapeWidget* dashWidget;

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
	virtual void SetStatus(const bool _status, const bool _applyToWidgets = true) override
	{
		Menu::SetStatus(_status, _applyToWidgets);
		pointerLeft->SetVisible(Count() > 0);
	}

public:
	Inventory();

private:
	Button* GetFirstAvailableButton() const;
	Item* FindItemData(const string& _path);

public:
	void Init();

	void Background();
	void Grid();
	void Equippements();
	void Description();
	void Separator();

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