#pragma once
#include "TextWidget.h"

class Label : public TextWidget
{
public:
	void SetString(const string& _text)
	{
		textObject->GetDrawable()->setString(_text);
	}

public:
	Label(const TextData& _data);
};