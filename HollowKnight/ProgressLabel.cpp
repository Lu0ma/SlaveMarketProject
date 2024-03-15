#include "ProgressLabel.h"
#include <conio.h>
#include "Timer.h"
#include "Macro.h"

void ProgressLabel::SetVisible(const bool _status)
{
	if (_status)
	{
		letterIndex = 0;
		displayedLetters.clear();
		SetString(text);
	}

	Widget::SetVisible(_status);
}

ProgressLabel::ProgressLabel(const TextData& _data, const float _charDuration, const string& _text,
							 const AligmentText& _aligement, const WidgetType& _type)
							: Label(_data, _aligement, _type)
{
	charDuration = _charDuration;
	text = _text;
	letterIndex = 0;
}


void ProgressLabel::SetString(const string& _text)
{
	if (letterIndex == 0)
	{
		text = _text;
	}

	int _lettersCount = 0;

	for (const string& _word : GetWords(text, true))
	{
		const int _wordLettersCount = (int)_word.size();
		_lettersCount += _wordLettersCount;

		if (letterIndex <= _lettersCount)
		{
			const char _letter = _word[letterIndex - _lettersCount + _wordLettersCount];
			displayedLetters += _letter == '\0' ? ' ' : _letter;
			Label::SetString(displayedLetters);
			letterIndex++;
			new Timer([&]() { SetString(text); }, seconds(charDuration));

			return;
		}
	}
}