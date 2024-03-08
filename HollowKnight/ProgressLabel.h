#pragma once
#include "Label.h"

class ProgressLabel : public Label
{
	float charDuration;
	//Timer* timer;
	string text;
	string displayedLetters;
	int letterIndex;

public:
	virtual void SetVisible(const bool _status) override;

public:
	ProgressLabel(const TextData& _data, const float _charDuration,
				  const AligmentText& _aligement = AT_CENTER);

public:
	virtual void SetString(const string& _text) override;
};