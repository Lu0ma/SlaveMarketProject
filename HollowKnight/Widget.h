#pragma once
#include "Object.h"

enum WidgetType
{
	WT_UI,
	WT_WORLD
};

class Widget
{
	bool isVisible;
	bool applyShader;
	WidgetType type;

public:
	virtual void SetVisible(const bool _status)
	{
		isVisible = _status;
	}
	void SetCanApplyShader(const bool _applyShader)
	{
		applyShader = _applyShader;
	}
	bool IsVisible() const
	{
		return isVisible;
	}
	bool CanApplyShader() const
	{
		return applyShader;
	}
	WidgetType GetType() const
	{
		return type;
	}
	virtual Object* GetObject() const = 0;
	virtual Drawable* GetDrawable() const = 0;

public:
	Widget(const WidgetType& _type = WT_UI);
	virtual ~Widget() {}
};