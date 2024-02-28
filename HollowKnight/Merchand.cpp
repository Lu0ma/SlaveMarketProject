#include "Merchand.h"
#include "Game.h"

#define PATH_SHOP "UIs/Shop/Shop.png"
#define FONT "Font.ttf"

Merchand::Merchand() : NPC()
{
	GetDrawable()->setFillColor(Color::Transparent);
}

void Merchand::Init()
{
	canvas = new Canvas("Shop", FloatRect(0, 0, 1, 1));

	const Vector2f& _windowSize = Game::GetWindowSize();
	const Vector2f& _halfWindowSize = Game::GetWindowSize() / 2.0f;

	/*cellSize = Vector2f(50.0f, 50.0f);
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
	}*/

	#pragma region Background

	const Vector2f& _shopSize = Vector2f(_halfWindowSize.x * 0.8f, _windowSize.y);
	const Vector2f& _shopPos = Vector2f(_halfWindowSize.x + _shopSize.x / 2.0f, _halfWindowSize.y);
	ShapeWidget* _shop = new ShapeWidget(ShapeData(_shopPos, _shopSize, PATH_SHOP));
	canvas->AddWidget(_shop);

	#pragma endregion

	struct SellItem
	{
		Item* 
		int price;
	};

	#pragma region Grid



	

	#pragma endregion

	#pragma region Description

	const Vector2f& _descriptionPos = Vector2f(_shopPos.x + _shopSize.x * 0.15f, _shopPos.y);
	const Vector2f& _descriptionSize = Vector2f(_shopSize.x / 2.0f, _shopSize.y * 0.6f);
	/*ShapeWidget* _description = new ShapeWidget(ShapeData(_descriptionPos, _descriptionSize, ""));
	canvas->AddWidget(_description);*/

	#pragma region Title

	const float _descriptionTitlePosX = _descriptionPos.x - _descriptionSize.x * 0.2f;
	const float _descriptionTitlePosY = _descriptionPos.y - _descriptionPos.y / 2.0f;
	const Vector2f& _descriptionTitlePos = Vector2f(_descriptionTitlePosX, _descriptionTitlePosY);
	descriptionTitle = new Label(TextData("Shade Cloak", _descriptionTitlePos, FONT, 26));
	canvas->AddWidget(descriptionTitle);

	#pragma endregion

	#pragma region Text

	const float _descriptionTextPosX = _descriptionTitlePosX - _descriptionSize.x * 0.2f;
	const float _descriptionTextPosY = _descriptionTitlePosY + _descriptionSize.y * 0.15f;
	const Vector2f& _descriptionLabelPos = Vector2f(_descriptionTextPosX, _descriptionTextPosY);
	descriptionText = new Label(TextData("coucou\nc'est moi", _descriptionLabelPos, FONT, 18));
	canvas->AddWidget(descriptionText);

	#pragma endregion

	#pragma endregion
}

//void Merchand::BuyItem()
//{
//
//}