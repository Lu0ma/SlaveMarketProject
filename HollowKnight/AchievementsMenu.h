#pragma once
#include "Menu.h"
#include "ScrollBar.h"

struct AchievementData
{
	string title;
	string description;
};

struct Achievement
{
	ShapeWidget* widget;
	vector<Label*> labels;

	Achievement(ShapeWidget* _widget, const vector<Label*>& _labels)
	{
		widget = _widget;
		labels = _labels;
	}

	void SetVisible(bool _visible)
	{
		widget->SetVisible(_visible);

		for (Label* _label : labels)
		{
			_label->SetVisible(_visible);
		}
	}

	void SetPosition(const Vector2f& _position)
	{
		widget->GetDrawable()->setPosition(_position);

		for (Label* _label : labels)
		{
			_label->GetDrawable()->setPosition(_position);
		}
	}

	void Move(const Vector2f& _offset)
	{
		widget->GetDrawable()->move(_offset);

		for (Label* _label : labels)
		{
			_label->GetDrawable()->move(_offset);
		}
	}
};

class AchievementsMenu : public Menu
{
	ScrollBar* handle;
	ShapeWidget* boxOfView;
	vector<AchievementData> allData;
	vector<Achievement*> achievements;

	//TODO move into Scrollbar
	int elementsShownCount = 6;
	int firstElementIndexShown = 0;

public:
	virtual void SetStatus(const bool _status)
	{
		Menu::SetStatus(_status);
		UpdateVisibility();
	}

public:
	AchievementsMenu(Menu* _owner);

private:
	void UpdateVisibility();

public:
	virtual void Init() override;
	void ComputeScroll(const vector<AchievementData>& _data, const bool _scrollType);
};