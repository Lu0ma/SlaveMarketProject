#include "TextWidget.h"
#include "FontManager.h"

TextWidget::TextWidget(const TextData& _data)
{
	textObject = new TextObject(_data);
}