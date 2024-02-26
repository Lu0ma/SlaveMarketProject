#pragma once
#include "Widget.h"
#include "ShapeObject.h"

class ShapeWidget : public Widget
{
protected:
	ShapeObject* shapeObject;

public:
	virtual ShapeObject* GetObject() const override
	{
		return shapeObject;
	}
	virtual Shape* GetDrawable() const override
	{
		return shapeObject->GetDrawable();
	}
	virtual void SetShapePosition(const Vector2f& _position)
	{
		GetDrawable()->setPosition(_position);
	}

public:
	ShapeWidget(const ShapeData& _data);
};