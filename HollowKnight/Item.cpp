#include "Item.h"
#include "Macro.h"

Item::Item(ItemWidget* _widget, const string& _fontPath) : IManagable(GetUniqueID())
{
	count = 1;
	widget = _widget;
	countText = new Label(TextData(to_string(count), _widget->GetObject()->GetShapePosition(), _fontPath, 20, Color::Red));
}