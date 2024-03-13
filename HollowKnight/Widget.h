#pragma once
#include "Object.h"

class Widget
{
	bool isVisible;
	bool applyShader;

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
	virtual Object* GetObject() const = 0;
	virtual Drawable* GetDrawable() const = 0;

public:
	Widget();
	virtual ~Widget() {}
};