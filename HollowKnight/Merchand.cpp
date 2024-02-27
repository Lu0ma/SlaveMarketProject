#include "Merchand.h"

Merchand::Merchand() : NPC()
{
	cellSize = Vector2f(50.0f, 50.0f);
	OpenShop();
}

void Merchand::Toggle()
{
	// canvas->SetVisibilityStatus(canvas->IsVisible() ? false : true);
}

void Merchand::OpenShop()
{
	canvas = new Canvas("Shop", FloatRect(0, 0, 1, 1));

	const Vector2f& _startGridPos = Vector2f(200.0f, 100.0f);
	const Vector2i& _gridSize = Vector2i(3, 3);

	for (int _row = 0; _row < _gridSize.y; ++_row)
	{
		for (int _column = 0; _column < _gridSize.x; ++_column)
		{
			const float _posX = _startGridPos.x + _column * cellSize.x;
			const float _posY = _startGridPos.y + _row * cellSize.y;

			Button* _button = new Button(ShapeData(Vector2f(_posX, _posY), Vector2f(cellSize.x, cellSize.y)));
			_button->GetObject()->GetDrawable()->setOutlineThickness(-1.0f);
			_button->GetObject()->GetDrawable()->setOutlineColor(Color::Black);
			canvas->AddWidget(_button);
		}
	}
	canvas->SetVisibilityStatus(true);
	BuyItem();
}

void Merchand::BuyItem()
{

}
