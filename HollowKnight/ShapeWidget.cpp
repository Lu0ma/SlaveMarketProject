#include "ShapeWidget.h"
#include "Macro.h"

ShapeWidget::ShapeWidget(const ShapeData& _data, const WidgetType& _type) : Widget(_type)
{
	shapeObject = new ShapeObject(_data);
	SetOriginAtMiddle(GetDrawable());
}

ShapeWidget::~ShapeWidget()
{
	delete shapeObject;
}