#pragma once
#include "IManagable.h"
#include "Canvas.h"
#include "ShapeWidget.h"
#include "Button.h"
#include "Label.h"
#include "ScrollBar.h"
#include "SoundData.h"

#define PATH_BACKGROUND "UIs/Menus/Background.png"
#define PATH_TITLE_ICON "UIs/Menus/TitleBarMenu.png"
#define PATH_POINTER "UIs/Menus/Pointer.png"
#define FONT "Font.ttf"

class Menu : public IManagable<string>
{
	bool isInit;
	SoundData* sound;
protected:
	Canvas* canvas;
	ShapeWidget* pointerLeft;
	ShapeWidget* pointerRight;
	Button* backButton;
	Menu* owner;
public:
	virtual void SetStatus(const bool _status, const bool _applyToWidgets = true)
	{
		if (!isInit)
		{
			Init();
			isInit = true;
		}

		canvas->SetVisibilityStatus(_status, _applyToWidgets);
	}
	void SetOwner(Menu* _owner)
	{
		owner = _owner;
	}
	bool IsActive() const
	{
		return isInit && canvas->GetVisibilityStatus();
	}

public:
	Menu(const string& _name, Menu* _owner = nullptr);

private:
	virtual void Register() override;

protected:
	void MovePointers(Button* _button);
	void MovePointers(const Vector2f& _position, const Vector2f& _size);

public:
	virtual void Init();
};