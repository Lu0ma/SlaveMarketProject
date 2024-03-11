#include "ScrollBar.h"

ScrollBar::ScrollBar(const ShapeData& _data, const vector<Widget*>& _widgets) : ShapeWidget(_data)
{
	widgets = _widgets;
}