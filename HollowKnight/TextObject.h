#pragma once
#include "Object.h"
#include <iostream>
using namespace std;

struct TextData : public Data
{
	string text;
	int size;
	Color color;
	Time time;

	TextData() = default;
	TextData(const string& _text, const Vector2f& _position, const string& _path = "",
		const int _size = 16, const Color& _color = Color::White) : Data(_position, _path)
	{
		text = _text;
		size = _size;
		color = _color;
	}
};

class TextObject : public Object
{
protected:
	Text* text;

public:
	virtual Text* GetDrawable() const override
	{
		return text;
	}
	Vector2f GetShapePosition() const
	{
		if (!text) return Vector2f();
		return text->getPosition();
	}
	Vector2f GetShapeSize() const
	{
		if (!text) return Vector2f();
		return text->getGlobalBounds().getSize();
	}

public:
	TextObject(const TextData& _data);
	~TextObject();
};