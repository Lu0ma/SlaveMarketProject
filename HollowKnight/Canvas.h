#pragma once
#include "IManagable.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Widget;

class Canvas : public IManagable<string>
{
	bool isVisible;
	FloatRect rect;
	vector<Widget*> widgets;

public:
	bool GetVisibilityStatus()
	{
		return isVisible;
	}
	void SetVisibilityStatus(bool _status)
	{
		isVisible = _status;
	}
	bool IsVisible() const
	{
		return isVisible;
	}
	FloatRect GetRect() const
	{
		return rect;
	}
	vector<Widget*> GetWidgets() const
	{
		return widgets;
	}

public:
	Canvas(const string& _name, const FloatRect& _rect = FloatRect(0, 0, 1, 1), 
		   const vector<Widget*>& _widgets = vector<Widget*>());

private:
	virtual void Register() override;

public:
	void AddWidget(Widget* _widget);

	void DeleteWidget();
};