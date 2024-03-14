#include "Widget.h"

Widget::Widget(const WidgetType& _type)
{
	isVisible = true;
	applyShader = false;
	type = _type;
}