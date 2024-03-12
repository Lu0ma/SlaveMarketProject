#include "ScrollBar.h"
#include "Game.h"

#define PATH_BAR "UIs/Menus/Achievements/ScrollBar/Bar.png"

ScrollBar::ScrollBar(const ShapeData& _data, const int _scrollAmount) : ShapeWidget(_data)
{
	
	baseIndex = 0;
	scrollAmount = _scrollAmount;

	
	bar = new ShapeWidget(ShapeData(Vector2f(_data.position.x, _data.position.y + 175.0f), Vector2f(_data.size.x, _data.size.y + 340.0f), PATH_BAR));
}

void ScrollBar::UpdateScroll(const Event& _event)
{
		if (_event.mouseWheelScroll.delta == 1) UpScroll();
		else DownScroll();
}

void ScrollBar::UpScroll()
{
	if (baseIndex < 0)
	{
		baseIndex++;
		ComputeByIndex(-50.0f);
	}
	else return;
}

void ScrollBar::DownScroll()
{
	if (baseIndex > -scrollAmount)
	{
		baseIndex--;
		ComputeByIndex(50.0f);
	}
	else return;
}

void ScrollBar::ComputeClickOnBar(const Vector2f& _position)
{

}

void ScrollBar::ComputeByIndex(const float _destination)
{
		const float _position = GetDrawable()->getPosition().y + _destination;
		GetDrawable()->setPosition(GetDrawable()->getPosition().x, _position);
}
