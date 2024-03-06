#pragma once
#include "Object.h"

class Widget
{
	bool isVisible;

public:
	virtual void SetVisible(const bool _status)
	{
		isVisible = _status;
	}
	bool IsVisible() const
	{
		return isVisible;
	}
	virtual Object* GetObject() const = 0;
	virtual Drawable* GetDrawable() const = 0;

public:
	Widget();
	virtual ~Widget() {}
};