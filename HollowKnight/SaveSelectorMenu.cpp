#include "SaveSelectorMenu.h"
#include "Game.h"

#define PATH_BUTTON "UIs/Menus/SaveSelectorMenu/Selector.png"

SaveSelectorMenu::SaveSelectorMenu(Menu* _owner) : Menu("SaveSelector", _owner)
{
	//Game::GetPlayer()->Init(); TODO: deplacer dans la callback du click d'un bouton
	saveNumber = 4;
}

void SaveSelectorMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

#pragma region Background

	ShapeWidget* _background = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);

#pragma endregion

#pragma region Title

	const float _titlePosY = _windowSize.y * 0.1f;
	Label* _title = new Label(TextData("Select Profile", Vector2f(_halfWindowX, _titlePosY), FONT, 36));
	canvas->AddWidget(_title);

	const float _titleBarPosY = _titlePosY + 75.0f;
	const Vector2f& _titleBarSize = Vector2f(_windowSize.x * 0.4f, 50.0f);
	const float _halfTitleBarSizeX = _titleBarSize.x * 0.45f;
	ShapeWidget* _titleBar = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _titleBarPosY), _titleBarSize, PATH_TITLE_ICON));
	canvas->AddWidget(_titleBar);

#pragma endregion

#pragma region BackButton
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

	Menu::Init();
	MovePointers(backButton);
#pragma endregion


#pragma region Saves
	vector<string> _allData = {
		"1.",
		"2.",
		"3.",
		"4.",
	};
	const float _saveButtonX = _halfWindowX * 0.9f;
	const Vector2f _saveButtonSize = Vector2f(650.0f, 100.0f);
	for (int _index = 0; _index < saveNumber; _index++)
	{
		float _gapY = _saveButtonSize.y * _index;
		float _saveButtonY = _windowSize.y * 0.35f + _gapY;

		Button* _button = new Button(ShapeData(Vector2f(_saveButtonX, _saveButtonY), _saveButtonSize, PATH_BUTTON));


		_button->GetData().hoveredCallback = [&]() {
			if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
			{
				MovePointers(_hoveredButton);
			}
		};

		_button->GetData().pressedCallback = [&]() {
			//cout << "bouton"  << endl;
			canvas->SetVisibilityStatus(false);
			Game::GetPlayer()->Init();
		};
		

		buttons.push_back(_button);
		canvas->AddWidget(_button);
		float _labelPosX = _saveButtonX - _saveButtonSize.x * 0.4f - 20.0f;
		Label* _saveNumber = new Label(TextData(_allData[_index], Vector2f(_labelPosX, _saveButtonY - 20.0f), FONT, 36));
		_button->SetForeground(_saveNumber);
		canvas->AddWidget(_saveNumber);
	}

	for (int _index = 0; _index < saveNumber; _index++)
	{
		float _gapY = _saveButtonSize.y * _index;
		float _saveButtonY = _windowSize.y * 0.35f + _gapY;
		float _clearPosX = _saveButtonX + _saveButtonSize.x * 0.75f;
		Button* _clearButton = new Button(ShapeData(Vector2f(_clearPosX, _saveButtonY), _saveButtonSize, ""));
		_clearButton->GetData().hoveredCallback = [&]() {
			if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
			{
				MovePointers(_hoveredButton);
			}
		};

		_clearButton->GetData().pressedCallback = [&]() {
			cout << "Clear" << endl;
			};
		_clearButton->GetDrawable()->setFillColor(Color::Transparent);
		Label* _clear = new Label(TextData("Clear Save", Vector2f(_clearPosX, _saveButtonY), FONT, 24));
		_clearButton->SetForeground(_clear);
		buttons.push_back(_clearButton);
		canvas->AddWidget(_clearButton);
		canvas->AddWidget(_clear);
	}
	Menu::Init();
	MovePointers(buttons.front());
#pragma endregion
}
