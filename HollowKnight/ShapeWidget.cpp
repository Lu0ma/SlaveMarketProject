#include "ShapeWidget.h"
#include "Macro.h"

ShapeWidget::ShapeWidget(const ShapeData& _data)
{
	shapeObject = new ShapeObject(_data);
	SetOriginAtMiddle(GetDrawable());
}

ShapeWidget::~ShapeWidget()
{
	delete shapeObject;
}