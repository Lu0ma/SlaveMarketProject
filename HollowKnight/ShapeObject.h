#pragma once
#include "Object.h"

struct ShapeData : public Data
{
	Vector2f size = Vector2f();
	IntRect rect = IntRect();

	ShapeData() {}
	ShapeData(const Vector2f& _position, const Vector2f& _size,
			  const string& _path = "", const IntRect& _rect = IntRect())
			  : Data(_position, _path)
	{
		size = _size;
		rect = _rect;
	}
};

class ShapeObject : public Object
{
protected:
	Shape* shape;

public:
	void SetShape(Shape* _shape)
	{
		shape = _shape;
	}
	void SetShapePosition(const Vector2f& _position)
	{
		shape->setPosition(_position);
	}
	virtual Shape* GetDrawable() const override
	{
		return shape;
	}
	Vector2f GetShapePosition() const
	{
		if (!shape) return Vector2f();
		return shape->getPosition();
	}
	Vector2f GetShapePositionMiddle() const
	{
		if (!shape) return Vector2f();
		return Vector2f(shape->getPosition().x, shape->getPosition().y);
	}
	Vector2f GetShapeSize() const
	{
		if (!shape) return Vector2f();
		return shape->getGlobalBounds().getSize();
	}

public:
	ShapeObject(const ShapeData& _data);
};

