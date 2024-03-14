#include "Macro.h"
#include <ctime>
#include <cstdlib>
int GetUniqueID()
{
	static int _id = 0;
	return _id++;
}

float Length(Vector2f& _vector)
{
	return sqrt(_vector.x * _vector.x + _vector.y * _vector.y);
}

//inline float Randn()
//{
//	return -1 + 2 * ((float)rand()) / RAND_MAX;
//}

void Normalize(Vector2f& _vector)
{
	_vector /= Length(_vector);
}

float Distance(const float _first, const float _second)
{
	return abs(_first - _second);
}

float Distance(const Vector2f& _first, const Vector2f& _second)
{
	return sqrtf(pow(_second.x - _first.x, 2.0f) + pow(_second.y - _first.y, 2.0f));
}


void SetOriginAtMiddle(Shape* _shape)
{
	const Vector2f& _size = _shape->getGlobalBounds().getSize();
	_shape->setOrigin(_size / 2.0f);
}

string GetLevelFromIndex(const int _index)
{
	return "Assets/Levels/SubLevel_" + to_string(_index) + ".txt";
}

vector<string> GetWords(const string& _text, const bool _withSpaces)
{
	vector<string> _words;
	string _word;

	for (const char _letter : _text)
	{
		if (_letter == ' ' || _letter == ',' || _letter == '\n')
		{
			if (_word != "")
			{
				_words.push_back(_word);
				_word = "";
			}

			if (!_withSpaces)
			{
				continue;
			}
		}

		_word += _letter;
	}

	_words.push_back(_word);

	return _words;
}