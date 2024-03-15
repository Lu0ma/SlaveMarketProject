#include "PauseMenu.h"
#include "MenuManager.h"
#include "Game.h"
#include "HUD.h"

#define PATH_PAUSE_MENU "UIs/Menus/PauseMenu/Background.png"

PauseMenu::PauseMenu() : Menu("PauseMenu", nullptr)
{
	buttons = vector<Button*>();
	quitToMenu = new QuitToMenu(this);
}


void PauseMenu::Init()
{
	canvas->SetVisibilityStatus(false);

	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	#pragma region Background

	ShapeWidget* _image = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_PAUSE_MENU));
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
		ButtonData("CONTINUE", [&]() {
			SetStatus(false);
			Game::GetPlayer()->CloseAllMenus(true);
		}),
		ButtonData("OPTIONS", [&]() {
			SetStatus(false);
			OptionsMenu* _options = MenuManager::GetInstance().GetMenu<OptionsMenu>();
			_options->SetOwner(this);
			_options->SetStatus(true);
		}),
		ButtonData("QUIT TO MENU", [&]() {
			SetStatus(false);
			quitToMenu->SetStatus(true);
		}),
	};

	const Vector2f& _buttonSize = Vector2f(100.0f, 50.0f);
	const float _gridPosY = _windowSize.y * 0.42f;
	const float _gapY = 0.0f;

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

		Label* _title = new Label(TextData(_allData[_index].text, Vector2f(_halfWindowX, _buttonPos.y), FONT, 22));
		_button->SetForeground(_title);
		canvas->AddWidget(_title);
	}

	#pragma endregion

	#pragma region Pointer

	Menu::Init();
	MovePointers(buttons.front());

	#pragma endregion
}