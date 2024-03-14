#include "ScrollBar.h"
#include "Game.h"

#define PATH_BAR "UIs/Menus/Achievements/ScrollBar/Bar.png"
#define PATH_BUTTON "UIs/Menus/Achievements/ScrollBar/Button.png"

ScrollBar::ScrollBar(const ShapeData& _data, const int _scrollAmount, const function<void(bool)>& _callback) : ShapeWidget(_data)
{
	callback = _callback;
	baseIndex = 0;
	scrollAmount = _scrollAmount;

	const Vector2f& _buttonSize = Vector2f(35.0f, 35.0f);
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
		ComputeByIndex(-85.0f);
		callback(true);
	}
	else return;
}

void ScrollBar::DownScroll()
{
	if (baseIndex > -scrollAmount)
	{
		baseIndex--;
		ComputeByIndex(85.0f);
		callback(false);
	}
	else return;
}

void ScrollBar::ComputeClickOnBar(const Vector2f& _position)
{
	//clique sur la bar et donne un pourcentage en fonction de la position Y du clic et de la taille de la bar
	const float _pourcentage = (_position.y - bar->GetDrawable()->getPosition().y) / bar->GetDrawable()->getGlobalBounds().height;

	//on calcule la position de la bar en fonction du pourcentage
	const float _clickOnBar = (_pourcentage * scrollAmount - baseIndex - 10) * 10;
	cout << round(_clickOnBar) << endl;

	//on met la bar au pourcentage
	ComputeByIndex(_clickOnBar);
}

void ScrollBar::ComputeByIndex(const float _destination)
{
	const float _position = GetDrawable()->getPosition().y + _destination;
	GetDrawable()->setPosition(GetDrawable()->getPosition().x, _position);
}