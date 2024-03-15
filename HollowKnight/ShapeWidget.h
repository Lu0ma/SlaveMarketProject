#pragma once
#include "Widget.h"
#include "ShapeObject.h"

class ShapeWidget : public Widget
{
protected:
	ShapeObject* shapeObject;

public:
	virtual void SetShapePosition(const Vector2f& _position)
	{
		GetDrawable()->setPosition(_position);
	}
	virtual ShapeObject* GetObject() const override
	{
		return shapeObject;
	}
	virtual Shape* GetDrawable() const override
	{
		return shapeObject->GetDrawable();
	}
	virtual Vector2f GetShapePosition()
	{
		return GetDrawable()->getPosition();
	}

public:
	ShapeWidget(const ShapeData& _data, const WidgetType& _type = WT_UI);
	~ShapeWidget();
};