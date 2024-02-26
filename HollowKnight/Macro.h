#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <string>

using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define STRING_ID(name) name + to_string(GetUniqueID())
#define SIZE(vector) static_cast<int>(vector.size())

int GetUniqueID();
float Length(Vector2f& _vector);
void Normalize(Vector2f& _vector);
float Distance(const Vector2f& _first, const Vector2f& _second);
void SetOriginAtMiddle(Shape* _shape);

template <typename T>
T Random(const T _max, const T _min = T(0))
{
	return int(rand() % (int)_max) + _min;
}

template <typename T>
bool IsEqual(const T& _first, const T& _second, const float _minRange = 0.001f)
{
	return abs(_second - _first) <= _minRange;
}

template <typename T>
bool Contains(T* _valueToFind, const vector<T*>& _vector)
{
	for (T* _value : _vector)
	{
		if (_value == _valueToFind) return true;
	}

	return false;
}