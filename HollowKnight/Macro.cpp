#include "Macro.h"
#include <ctime>
#include <cstdlib>
#include <random>

int GetUniqueID()
{
	static int _id = 0;
	return _id++;
}

float Length(Vector2f& _vector)
{
	return sqrt(_vector.x * _vector.x + _vector.y * _vector.y);
}

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

int Random(const int _max, const int _min)
{
	random_device _rd;
	mt19937 _seed(_rd());
	uniform_int_distribution<int> _distribution(_min, _max);
	return _distribution(_seed);
}

Vector2f operator*(const Vector2f& _first, const Vector2f& _second)
{
	return Vector2f(_first.x * _second.x, _first.y * _second.y);
}
