#include "Item.h"

ItemWidget::ItemWidget(const ShapeData& _data, const string& _title, const string& _text)
					 : ShapeWidget(_data), IManagable(_data.path)
{
	title = _title;
	text = _text;
}