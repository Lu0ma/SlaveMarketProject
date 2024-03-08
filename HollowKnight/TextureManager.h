#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "ShapeObject.h"
#include "TextureData.h"

class TextureManager : public Singleton<TextureManager>, public IManager<string, TextureData>
{
public:
	void Load(ShapeObject* _object, const string& _path, const bool _isRepeated = false, const bool _smooth = true);
	void Load(Sprite* _sprite, const string& _path, const bool _isRepeated = false, const bool _smooth = true);
	void LoadWithRect(ShapeObject* _object, const string& _path, const IntRect& _rect, const bool _isRepeated = false, const bool _smooth = true);
};