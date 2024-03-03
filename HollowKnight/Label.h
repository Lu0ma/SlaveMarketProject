#pragma once
#include "TextWidget.h"

enum AligmentText
{
	AT_LEFT,
	AT_CENTER,
	AT_RIGHT,
};

class Label : public TextWidget
{
public:
	void SetString(const string& _text)
	{
		textObject->GetDrawable()->setString(_text);
	}
	void SetAlignement(const AligmentText& _aligment)
	{
		const FloatRect& _bounds = textObject->GetDrawable()->getLocalBounds();
		const float _originX = _aligment == AT_LEFT ? _bounds.left
							 : _aligment == AT_CENTER ? _bounds.width / 2.0f
							 : _bounds.width;
		textObject->GetDrawable()->setOrigin(_originX, _bounds.height / 2.0f);
	}

public:
	Label(const TextData& _data, const AligmentText& _aligment = AT_CENTER);
};