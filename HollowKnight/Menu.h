#pragma once
#include "IManagable.h"
#include "Canvas.h"
#include "ShapeWidget.h"
#include "Button.h"
#include "Label.h"

#define PATH_BACKGROUND "UIs/Menus/Background.png"
#define PATH_TITLE_ICON "UIs/Menus/TitleIcon.png"
#define PATH_POINTER "UIs/Menus/Pointer.png"
#define FONT "Font.ttf"

class Menu : public IManagable<string>
{
	bool isInit;

protected:
	Canvas* canvas;
	ShapeWidget* pointer;
	Menu* owner;

public:
	virtual void SetStatus(const bool _status)
	{
		if (!isInit)
		{
			Init();
			isInit = true;
		}

		canvas->SetVisibilityStatus(_status);
	}
	bool IsActive()
	{
		return isInit && canvas->GetVisibilityStatus();
	}

public:
	Menu(const string& _name, Menu* _owner = nullptr);

public:
	virtual void Init() = 0;
};