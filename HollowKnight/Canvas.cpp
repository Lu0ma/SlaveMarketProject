#include "Canvas.h"
#include "HUD.h"

Canvas::Canvas(const string& _name, const FloatRect& _rect, const vector<Widget*>& _widgets)
				: IManagable(_name)
{
	Register();

	isVisible = true;
	rect = _rect;
	widgets = _widgets;
}

Canvas::~Canvas()
{
	for (Widget* _widget : widgets)
	{
		delete _widget;
	}
}


void Canvas::Register()
{
	HUD::GetInstance().Add(id, this);
}

void Canvas::AddWidget(Widget* _widget)
{
	if (Button* _button = dynamic_cast<Button*>(_widget))
	{
		HUD::GetInstance().AddButton(_button);
	}

	if (ScrollBar* _scrollBar = dynamic_cast<ScrollBar*>(_widget))
	{
		HUD::GetInstance().AddScrollBar(_scrollBar);
	}

	widgets.push_back(_widget);
}

void Canvas::DeleteWidget()
{
	widgets.pop_back();
}