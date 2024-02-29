#include "Canvas.h"
#include "Widget.h"
#include "HUD.h"
Canvas::Canvas(const string& _name, const FloatRect& _rect, const vector<Widget*>& _widgets)
				: IManagable(_name)
{
	Register();

	isVisible = true;
	rect = _rect;
	widgets = _widgets;
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
	widgets.push_back(_widget);
}

void Canvas::DeleteWidget()
{
	widgets.pop_back();
}

