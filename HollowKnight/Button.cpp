#include "Button.h"
#include <iostream>

Button::Button(const ShapeData& _data/*, const AllButtonData& _buttonData*/) : ShapeWidget(_data)
{
	//allData = _buttonData;
	isSelected = false;
	isHovered = false;
	isHeld = false;
	foreground = nullptr;
}


void Button::OnPressed()
{
	isSelected = true;
	isHeld = true;
}

void Button::OnHeld()
{
	if (!isHeld) return;
}

void Button::OnReleased()
{
	if (!isSelected) return;

	isSelected = false;
	isHeld = false;
}

void Button::OnHovered()
{
	isHovered = true;
}

void Button::OnUnhovered()
{
	isHovered = false;
}


void Button::Execute(const Event& _event)
{

}
