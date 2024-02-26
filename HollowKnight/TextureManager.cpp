#include "TextureManager.h"
#include <iostream>

void TextureManager::Load(Shape*& _shape, const string& _path, const bool _isRepeated, const bool _smooth)
{
	if (_path == "") return;

	TextureData* _textureData = Get(_path);
	if (!_textureData)
	{
		_textureData = new TextureData(_path);
		if (!_textureData->loadFromFile("Assets/Textures/" + _path))
		{
			cerr << "La texture n'a pas été correctement chargée !" << endl;
		}

		_textureData->setRepeated(_isRepeated);
		_textureData->setSmooth(_smooth);
	}

	RectangleShape* _newShape = new RectangleShape(_shape ? dynamic_cast<RectangleShape&>(*_shape) : RectangleShape());
	_newShape->setTexture(_textureData);
	if (_shape) delete _shape;
	_shape = _newShape;
}

void TextureManager::LoadWithRect(Shape*& _shape, const string& _path, const IntRect& _rect, const bool _isRepeated, const bool _smooth)
{
	Load(_shape, _path, _isRepeated, _smooth);
	_shape->setTextureRect(_rect);
}