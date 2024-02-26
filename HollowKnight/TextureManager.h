#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "TextureData.h"

class TextureManager : public Singleton<TextureManager>, public IManager<string, TextureData>
{
public:
	void Load(Shape*& _shape, const string& _path, const bool _isRepeated = false, const bool _smooth = true);
	void LoadWithRect(Shape*& _shape, const string& _path, const IntRect& _rect, const bool _isRepeated = false, const bool _smooth = true);
};