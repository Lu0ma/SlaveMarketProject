#pragma once
#include "ShapeWidget.h"
#include <functional>

using namespace std;

//struct AllButtonData
//{
//	ButtonData pressedData;
//	ButtonData heldData;
//	ButtonData releasedData;
//	ButtonData hoveredData;
//	ButtonData unhoveredData;
//
//public:
//	AllButtonData(const ButtonData& _pressedData = ButtonData(Color::White, 3.0f, Color::Red),
//				  const ButtonData& _heldData = ButtonData(Color::White, 3.0f, Color::Red),
//				  const ButtonData& _releasedData = ButtonData(Color::White, 3.0f, Color::Red),
//				  const ButtonData& _hoveredData = ButtonData(Color::White, 3.0f, Color::Red),
//				  const ButtonData& _unhoveredData = ButtonData(Color::White, 3.0f, Color::Red))
//	{
//		pressedData = _pressedData;
//		heldData = _heldData;
//		releasedData = _releasedData;
//		hoveredData = _hoveredData;
//		unhoveredData = _unhoveredData;
//	}
//};

class Button : public ShapeWidget
{
	bool isSelected;
	bool isHeld;
	bool isHovered;
	Widget* foreground;
	function<void()> callback;
	//AllButtonData allData;

public:
	bool IsSelected() const
	{
		return isSelected;
	}
	bool IsHovered() const
	{
		return isHovered;
	}
	void SetForeground(Widget* _foreground)
	{
		foreground = _foreground;
	}
	Widget* GetForeground() const
	{
		return foreground;
	}

public:
	Button(const ShapeData& _data/*, const AllButtonData& _buttonData = AllButtonData()*/);

public:
	void OnPressed();
	void OnHeld();
	void OnReleased();
	void OnHovered();
	void OnUnhovered();

	void Execute(const Event& _event);
};