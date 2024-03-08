#include "ProgressLabel.h"
#include <conio.h>
#include "Timer.h"
#include "Macro.h"

void ProgressLabel::SetVisible(const bool _status)
{
	if (_status)
	{
		GetDrawable()->setFillColor(Color::Red);
		const string& _text = GetDrawable()->getString();
		GetDrawable()->setString("");
		SetString(_text);
	}

	Widget::SetVisible(_status);
}

ProgressLabel::ProgressLabel(const TextData& _data, const float _charDuration,
							 const AligmentText& _aligement)
						   : Label(_data, _aligement)
{
	charDuration = _charDuration;
	text = "";
	letterIndex = 0;
}

//void ProgressLabel::SetString(const string& _text)
//{
//	// j'affiche toutes les charDuration un char supplémentaire
//
//	const int _textSize = static_cast<int>(_text.size());
//	const float _displayDuration = charDuration * _textSize;
//
//	//timer = new Timer([&]() { Label::SetString(displayedLetters); }, seconds(charDuration), false, true);
//
//	for (const string& _word : GetWords(_text, true))
//	{
//		for (char _letter : _word)
//		{
//			displayedLetters += _letter;
//			new Timer([&]() { 
//				Label::SetString(displayedLetters); }, seconds(charDuration));
//
//			if (_kbhit())
//			{
//				system("cls");
//				cout << "Skip la cinématique !" << endl;
//				return;
//			}
//		}
//
//		cout << " ";
//	}
//}

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
			cout << _letter << endl;
			displayedLetters += _letter;
			Label::SetString(displayedLetters);
			letterIndex++;
			new Timer([&]() { 
				SetString(text); }, seconds(charDuration));
			return;
		}
	}
}