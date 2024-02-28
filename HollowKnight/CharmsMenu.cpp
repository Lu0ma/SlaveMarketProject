#include "CharmsMenu.h"
#include "Game.h"

#define PATH_BACKGROUND "UIs/Charms/Charms.png"

#define PATH_SKILL_SLOT "UIs/Charms/SkillSlot.png"

#define PATH_NOTCH_UNUSED "UIs/Charms/Notch_0.png"
#define PATH_NOTCH_USED "UIs/Charms/Notch_1.png"

#define PATH_SELECTED_CHARMS "UIs/Charms/Select_Charms.png"

#define PATH_SEPARATOR "UIs/Inventory/Separator.png"

#define PATH_POINTER "UIs/Charms/Pointer.png"

CharmsMenu::CharmsMenu()
{
	canvas = nullptr;
	gridSize = Vector2i(10, 4);
	slotSize = Vector2f(30.0f, 30.0f);
	notchSize = Vector2f(20.0f, 20.0f);
	charmsSelectSize = Vector2f(30.0f, 30.0f);
	notches = 3;
	charms = 1;
}

void CharmsMenu::Init()
{
	canvas = new Canvas("PlayerCharms", FloatRect(0, 0, 1, 1));
	canvas->SetVisibilityStatus(false);

	const Vector2f& _windowSize = Game::GetWindowSize();
	const Vector2f& _halfSize = _windowSize / 2.0f;
	
#pragma region BackGround

	ShapeWidget* _background = new ShapeWidget(ShapeData(_halfSize, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);

#pragma endregion

	const Vector2f& _gridPos = _halfSize / 4.0f;
	const Vector2f& _gapSlot = Vector2f(35.0f, 35.0f);
	const float _spacingY = _halfSize.y * 0.8f;

#pragma region Slots

	for (int _row = 0; _row < gridSize.y; _row++)
	{
		for (int _column = 0; _column < gridSize.x; _column++)
		{
			const float _posX = _gridPos.x + _column * slotSize.x + (_row % 2 != 0 ? _gapSlot.x/2.0f + 2 * slotSize.x /3.0f : 0.0f) + _gapSlot.x * _column;
			const float _posY = _spacingY + _gridPos.y + _row * slotSize.y + _gapSlot.y * _row;
			ShapeWidget* _slot = new ShapeWidget(ShapeData(Vector2f(_posX, _posY), slotSize, PATH_SKILL_SLOT));

			canvas->AddWidget(_slot);
		}
	}

#pragma endregion

#pragma region Separator
	const float _spacingX = gridSize.x * slotSize.x;
	const float _spacingSeparatorY = _halfSize.y * 0.95f;
	ShapeWidget* _line = new ShapeWidget(ShapeData(Vector2f(_gridPos.x + _spacingX, _spacingSeparatorY), Vector2f(35.0f, 589.0f), PATH_SEPARATOR));
	_line->GetDrawable()->setRotation(90.0f);
	canvas->AddWidget(_line);

#pragma endregion

	const float _gapNotchX = 5.0f;
	const float _spacingNotchY = _halfSize.y * 0.85f;

#pragma region Notches

	for (int _row = 0; _row < notches; _row++)
	{
		const float _posX = _gridPos.x + _row * slotSize.x + _gapNotchX * _row;
		const float _posY = _spacingNotchY;
		ShapeWidget* _notch = new ShapeWidget(ShapeData(Vector2f(_posX, _posY), notchSize, PATH_NOTCH_UNUSED));
		canvas->AddWidget(_notch);
	}

#pragma endregion

#pragma region Notches_Text
	const float _spacingNotchTextY = _halfSize.y * 0.7f;
	const Vector2f& _posText = Vector2f(_gridPos.x - 10.0f, _spacingNotchTextY);
	TextWidget* _text = new TextWidget(TextData("Notches", _posText, "TrajanProRegular.ttf"));
	canvas->AddWidget(_text);
#pragma endregion

#pragma region Selected_Charms

	for (int _row = 0; _row < charms; _row++)
	{
		Button* _charms = new Button(ShapeData(Vector2f(_gridPos.x + 35.0f, _spacingY + _row * slotSize.y - _halfSize.y * 0.30f), charmsSelectSize, PATH_SELECTED_CHARMS), ButtonData());

		canvas->AddWidget(_charms);
	}

#pragma endregion

#pragma region Equipped_Text

	TextWidget* _equippedText = new TextWidget(TextData("Equipped", Vector2f(_posText.x, _spacingY + slotSize.y - _halfSize.y * 0.60f), "TrajanProRegular.ttf"));

	canvas->AddWidget(_equippedText);

#pragma endregion



}
