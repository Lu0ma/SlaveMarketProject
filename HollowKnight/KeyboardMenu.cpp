#include "KeyboardMenu.h"
#include "Game.h"

#define PATH_KEYBOARD "UIs/Menus/Options/Keyboard/Background.png"

KeyboardMenu::KeyboardMenu(Menu* _owner) : Menu("Keyboard", _owner)
{
	backButton = nullptr;
}


void KeyboardMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	#pragma region Background

	ShapeWidget* _background = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_KEYBOARD));
	canvas->AddWidget(_background);

	#pragma endregion

	#pragma region Back

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _buttonPosY = _windowSize.y * 0.9f;
	const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);

	backButton = new Button(ShapeData(_buttonPos, _buttonSize, ""));
	backButton->GetData().pressedCallback = [&]() {
		owner->SetStatus(true);
		canvas->SetVisibilityStatus(false);
	};
	backButton->GetDrawable()->setFillColor(Color::Transparent);
	canvas->AddWidget(backButton);

	Label* _buttonText = new Label(TextData("BACK", Vector2f(_halfWindowX, _buttonPos.y), FONT, 20));
	backButton->SetForeground(_buttonText);
	canvas->AddWidget(_buttonText);

	pointer = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _buttonPos.y), Vector2f(_buttonSize.x, _buttonSize.y), PATH_POINTER));
	canvas->AddWidget(pointer);

	#pragma endregion
}