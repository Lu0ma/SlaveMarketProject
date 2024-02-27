#include "Item.h"
#include "Macro.h"

Item::Item(ItemWidget* _widget, const string& _fontPath) : IManagable(GetUniqueID())
{
	count = 1;
	widget = _widget;
	countText = new Label(TextData("", _widget->GetObject()->GetShapePosition() + _widget->GetObject()->GetShapeSize() / 2.0f, _fontPath, 20, Color::White));
}