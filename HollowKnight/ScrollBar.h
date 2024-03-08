#pragma once
#include "ShapeWidget.h"

class ScrollBar : public ShapeWidget
{
	vector<Widget*> widgets;

public:
	ScrollBar(const ShapeData& _data, const vector<Widget*>& _widgets = vector<Widget*>());

public:

};