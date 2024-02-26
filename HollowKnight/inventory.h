#pragma once
#include "IManager.h"
#include "Item.h"
#include "Canvas.h"
#include "Button.h"

#define PATH_HEALTH_MASK "UIs/HealthMasks/HealthMask_"

class Inventory : public IManager<int, Item>
{
	Canvas* canvas;
	Vector2i gridSize;
	Vector2f cellSize;
	vector<Button*> buttons;
	int stackSize;

	//TODO move
	ShapeWidget* pointer = nullptr;

	//TODO move
	int maskCount = 0;
	ShapeWidget* maskWidget = nullptr;

private:
	string ComputeHealthMaskPath() const
	{
		return PATH_HEALTH_MASK + to_string(maskCount) + ".png";
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

	void AddItem(const int _count, const string _path, const ItemType& _type, const RarityType& _rarity = RARITY_COMMON);
	void CreateItemData(const std::string& _path, const ItemType& _type, const RarityType& _rarity);
};