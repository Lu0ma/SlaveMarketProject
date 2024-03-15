#include "TextObject.h"
#include "FontManager.h"

TextObject::TextObject(const TextData& _data)
{
	text = new Text();

	FontManager::GetInstance().Load(text, _data.path);
	text->setPosition(_data.position);
	text->setString(_data.text);
	text->setCharacterSize(_data.size);
	text->setFillColor(_data.color);
}

TextObject::~TextObject()
{
	delete text;
}