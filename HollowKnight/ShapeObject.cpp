#include "ShapeObject.h"
#include "TextureManager.h"

ShapeObject::ShapeObject(const ShapeData& _data)
{
	shape = new RectangleShape(_data.size);
	shape->setPosition(_data.position);

	TextureManager& _textureManager = TextureManager::GetInstance();
	_data.rect == IntRect() ? _textureManager.Load(this, _data.path)
							: _textureManager.LoadWithRect(this, _data.path, _data.rect);
}

ShapeObject::~ShapeObject()
{
	delete shape;
}