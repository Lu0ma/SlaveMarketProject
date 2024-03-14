#pragma once
#include "Label.h"

class ProgressLabel : public Label
{
	float charDuration;
	string text;
	string displayedLetters;
	int letterIndex;

public:
	virtual void SetVisible(const bool _status) override;

public:
	ProgressLabel(const TextData& _data, const float _charDuration, const string& _text,
				  const AligmentText& _aligement = AT_CENTER, const WidgetType& _type = WT_UI);

public:
	virtual void SetString(const string& _text) override;
};