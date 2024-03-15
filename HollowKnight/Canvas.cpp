#include "Canvas.h"
#include "HUD.h"

Canvas::Canvas(const string& _name, const FloatRect& _rect) : IManagable(_name)
{
	Register();

	isVisible = true;
	rect = _rect;
}

Canvas::~Canvas()
{
	for (Widget* _widget : uiWidgets)
	{
		delete _widget;
	}

	for (Widget* _widget : worldWidgets)
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

	vector<Widget*>* _widgets[] = {
		&uiWidgets,
		&worldWidgets
	};

	_widgets[_widget->GetType()]->push_back(_widget);
}