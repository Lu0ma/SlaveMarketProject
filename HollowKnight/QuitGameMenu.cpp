#include "QuitGameMenu.h"
#include "Game.h"
#include "HUD.h"

#define PATH_QUIT_GAME_MENU "UIs/Menus/QuitGameMenu/Background.png"

QuitGameMenu::QuitGameMenu(Menu* _owner) : Menu("QuitGame", _owner)
{
	buttons = vector<Button*>();
}


void QuitGameMenu::Init()
{
	canvas->SetVisibilityStatus(false);

	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	#pragma region Background

	ShapeWidget* _image = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_QUIT_GAME_MENU));
	canvas->AddWidget(_image);

	#pragma endregion

	#pragma region Grid

	struct ButtonData
	{
		string text;
		function<void()> callback;

		ButtonData(const string& _text, const function<void()>& _callback)
		{
			text = _text;
			callback = _callback;
		}
	};

	const vector<ButtonData>& _allData = {
		ButtonData("Yes", [&]() {
			Game::Close();
		}),
		ButtonData("No", [&]() {
			SetStatus(false);
			dynamic_cast<TitleMenu*>(owner)->SetStatus(true);
		}),
	};

	const Vector2f& _buttonSize = Vector2f(100.0f, 50.0f);
	const float _gridPosY = _windowSize.y * 0.5f;
	const float _gapY = 20.0f;

	const int _buttonsCount = (int)_allData.size();
	for (int _index = 0; _index < _buttonsCount; _index++)
	{
		const float _buttonPosY = _gridPosY + _buttonSize.y * _index + _gapY * _index;
		const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);
		Button* _button = new Button(ShapeData(_buttonPos, _buttonSize, ""));
		_button->GetData().hoveredCallback = [&]()
		{
			if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
			{
				MovePointers(_hoveredButton);
			}
		};
		_button->GetData().pressedCallback = _allData[_index].callback;
		_button->GetDrawable()->setFillColor(Color::Transparent);
		buttons.push_back(_button);
		canvas->AddWidget(_button);

		Label* _title = new Label(TextData(_allData[_index].text, Vector2f(_halfWindowX, _buttonPos.y), FONT, 35));
		_button->SetForeground(_title);
		canvas->AddWidget(_title);
	}

	#pragma endregion

	#pragma region Pointer

	Menu::Init();
	MovePointers(buttons.front());

	#pragma endregion
}