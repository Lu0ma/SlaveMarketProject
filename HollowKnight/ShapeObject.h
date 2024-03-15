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
		if (shape) delete shape;
		shape = _shape;
	}
	void SetShapePosition(const Vector2f& _position)
	{
		shape->setPosition(_position);
	}
	void SetShapeSize(const Vector2f& _size)
	{
		const Vector2i& _position = Vector2i(shape->getLocalBounds().getPosition());
		shape->setTextureRect(IntRect(_position, Vector2i(_size)));
	}
	virtual Shape* GetDrawable() const override
	{
		return shape;
	}
	Shape* GetShape() const
	{
		return shape;
	}
	Vector2f GetShapePosition() const
	{
		if (!shape) return Vector2f();
		return shape->getPosition();
	}
	Vector2f GetShapeSize() const
	{
		if (!shape) return Vector2f();
		return shape->getGlobalBounds().getSize();
	}

public:
	ShapeObject(const ShapeData& _data);
	~ShapeObject();
};