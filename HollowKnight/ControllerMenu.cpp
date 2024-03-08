#include "ControllerMenu.h"
#include "Game.h"

#define PATH_CONTROLLER "UIs/Menus/Options/Controller/Background.png"

ControllerMenu::ControllerMenu(Menu* _owner) : Menu("Controller", _owner)
{

}


void ControllerMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	#pragma region Background

	ShapeWidget* _background = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_CONTROLLER));
	canvas->AddWidget(_background);

	#pragma endregion

	#pragma region Back

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _buttonPosY = _windowSize.y * 0.9f;
	const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);

	Button* _backButton = new Button(ShapeData(_buttonPos, _buttonSize, ""));
	_backButton->GetData().pressedCallback = [&]() {
		owner->SetStatus(true);
		canvas->SetVisibilityStatus(false);
	};
	_backButton->GetDrawable()->setFillColor(Color::Transparent);
	canvas->AddWidget(_backButton);

	Label* _buttonText = new Label(TextData("BACK", Vector2f(_halfWindowX, _buttonPos.y), FONT, 20));
	_backButton->SetForeground(_buttonText);
	canvas->AddWidget(_buttonText);

	Menu::Init();
	const Vector2f& _pointerPos = Vector2f(_halfWindowX, _buttonPos.y);
	const float _pointerSizeX = _buttonSize.x * 0.25f;
	const float _pointerSizeY = _buttonSize.y * 0.15f;
	pointerLeft->SetShapePosition(_pointerPos + Vector2f(-_pointerSizeX, _pointerSizeY));
	pointerRight->SetShapePosition(_pointerPos + Vector2f(_pointerSizeX, _pointerSizeY));

	#pragma endregion
}