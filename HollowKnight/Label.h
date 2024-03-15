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
	AligmentText alignement;
		 
public:
	virtual void SetString(const string& _text)
	{
		textObject->GetDrawable()->setString(_text);
		SetAlignement(alignement);
	}
	void SetAlignement(const AligmentText& _aligement)
	{
		alignement = _aligement;
		const FloatRect& _bounds = textObject->GetDrawable()->getLocalBounds();
		const float _originX = _aligement == AT_LEFT ? _bounds.left
							 : _aligement == AT_CENTER ? _bounds.width / 2.0f
							 : _bounds.width;
		textObject->GetDrawable()->setOrigin(_originX, _bounds.top); // alignement Y
	}

public:
	Label(const TextData& _data, const AligmentText& _aligement = AT_CENTER, const WidgetType& _type = WT_UI);
};