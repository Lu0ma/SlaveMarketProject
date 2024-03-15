#include "TextureManager.h"
#include <iostream>

void TextureManager::Load(ShapeObject* _object, const string& _path, const bool _isRepeated, const bool _smooth)
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

	Shape* _oldShape = _object->GetDrawable();
	RectangleShape* _newShape = new RectangleShape(_oldShape ? dynamic_cast<RectangleShape&>(*_oldShape) : RectangleShape());
	_newShape->setTexture(_textureData);
	_object->SetShape(_newShape);
}

void TextureManager::Load(Sprite* _sprite, const string& _path, const bool _isRepeated, const bool _smooth)
{
	if (_path == "") return;

	TextureData* _textureData = Get(_path);

	if (!_textureData)
	{
		_textureData = new TextureData(_path);
		if (!_textureData->loadFromFile("Fichier/" + _path))
		{
			cerr << "La texture n'a pas été correctement chargée !" << endl;
		}

		_textureData->setRepeated(_isRepeated);
		_textureData->setSmooth(_smooth);

		_sprite->setTexture(*_textureData);
		_textureData->SetRect(_sprite->getTextureRect());
	}

	else
	{
		_sprite->setTexture(*_textureData);
	}

	_sprite->setTextureRect(_textureData->GetRect());
}

void TextureManager::LoadWithRect(ShapeObject* _object, const string& _path, const IntRect& _rect, const bool _isRepeated, const bool _smooth)
{
	Load(_object, _path, _isRepeated, _smooth);
	_object->GetDrawable()->setTextureRect(_rect);
}