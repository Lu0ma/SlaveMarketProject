#include "Button.h"
#include <iostream>

Button::Button(const ShapeData& _data, const ButtonData& _buttonData) : ShapeWidget(_data)
{
	isSelected = false;
	isHovered = false;
	isHeld = false;
	foreground = nullptr;
	data = _buttonData;
}


bool Button::OnPressed()
{
	isSelected = true;
	isHeld = true;

	if (data.pressedCallback)
	{
		data.pressedCallback();
		return true;
	}
	
	return false;
}

void Button::OnHeld()
{
	if (!isHeld) return;

	if (data.releasedCallback)
	{
		data.releasedCallback();
	}
}

void Button::OnReleased()
{
	if (!isSelected) return;

	isSelected = false;
	isHeld = false;

	if (data.heldCallback)
	{
		data.heldCallback();
	}
}

void Button::OnHovered()
{
	isHovered = true;

	if (data.hoveredCallback)
	{
		data.hoveredCallback();
	}
}

void Button::OnUnhovered()
{
	isHovered = false;

	if (data.unHoveredCallback)
	{
		data.unHoveredCallback();
	}
}


void Button::Execute(const Event& _event)
{

}