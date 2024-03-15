#pragma once
#include "ItemWidget.h"
#include "Button.h"

class CharmWidget : public ItemWidget
{
	Button* owner;

public:
	CharmWidget(const ShapeData& _data, const string& _title,
		const string& _text, Button* _owner);

public:
	void ResetPosition();
};