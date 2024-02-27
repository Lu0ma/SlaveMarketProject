#pragma once
#include "ShapeWidget.h"
#include "IManagable.h"

class ItemWidget : public ShapeWidget, public IManagable<string>
{
	string title;
	string text;

public:
	string GetTitle() const
	{
		return title;
	}
	string GetText() const
	{
		return text;
	}

public:
	ItemWidget(const ShapeData& _data, const string& _title, const string& _text);
};