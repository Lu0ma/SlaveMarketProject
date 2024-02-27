#pragma once
#include "IManagable.h"
#include "ItemWidget.h"
#include "Button.h"
#include "Label.h"

struct ItemData
{
	string path;
	string title;
	string text;
};

class Item : public IManagable<int>
{
	int count;
	ItemWidget* widget;
	Label* countText;

public:
	void UpdateCount(const int _factor)
	{
		count += _factor;

		if (count > 1)
		{
			countText->SetString(to_string(count));
		}
	}
	bool IsEmpty() const
	{
		return count == 0;
	}
	int GetCount() const
	{
		return count;
	}
	string GetPath() const
	{
		return widget->GetID();
	}
	Label* GetCountText() const
	{
		return countText;
	}

public:
	Item(ItemWidget* _widget, const string& _fontPath);
};

