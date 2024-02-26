#pragma once
#include "ShapeWidget.h"
#include "IManagable.h"

class ItemWidget : public ShapeWidget, public IManagable<string>
{

public:
	ItemWidget(const ShapeData& _data);
};