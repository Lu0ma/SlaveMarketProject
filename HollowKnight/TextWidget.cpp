#include "TextWidget.h"
#include "FontManager.h"

TextWidget::TextWidget(const TextData& _data, const WidgetType& _type) : Widget(_type)
{
	textObject = new TextObject(_data);
}