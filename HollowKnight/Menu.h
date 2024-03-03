#pragma once
#include "Canvas.h"
#include "ShapeWidget.h"
#include "Label.h"

class Menu
{
	bool isInit;

protected:
	Canvas* canvas;
	Menu* owner;

public:
	void SetStatus(const bool _status)
	{
		if (!isInit)
		{
			Init();
			isInit = true;
		}

		canvas->SetVisibilityStatus(_status);
	}

public:
	Menu(const string& _name, Menu* _owner = nullptr);

public:
	virtual void Init() = 0;
};