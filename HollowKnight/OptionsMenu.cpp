#include "OptionsMenu.h"
#include "Game.h"
#include "HUD.h"

#define PATH_BACKGROUND "UIs/Menus/Background.png"
#define PATH_TITLE_ICON "UIs/Menus/TitleIcon.png"
#define PATH_POINTER "UIs/Menus/Options/Pointer.png"
#define FONT "Font.ttf"

OptionsMenu::OptionsMenu(Menu* _owner) : Menu("OptionsMenu", _owner)
{
	buttons = vector<Button*>();
	pointer = nullptr;
}


void OptionsMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	#pragma region Background

	ShapeWidget* _background = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);
	
	#pragma endregion

	#pragma region Title
	
	const float _tilePosY = _windowSize.y * 0.15f;
	Label* _title = new Label(TextData("OPTIONS", Vector2f(_halfWindowX, _tilePosY), FONT, 32));
	canvas->AddWidget(_title);

	const float _tileIconPosY = _tilePosY + 50.0f;
	ShapeWidget* _titleIcon = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _tileIconPosY), Vector2f(765.0f, 78.0f), PATH_TITLE_ICON));
	_titleIcon->GetDrawable()->setScale(0.6f, 0.6f);
	canvas->AddWidget(_titleIcon);

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
		ButtonData("GAME", [&]() {
			cout << "GAME" << endl;
			//canvas->SetVisibilityStatus(false);
		}),
		ButtonData("AUDIO", [&]() {
			cout << "AUDIO" << endl;
			//canvas->SetVisibilityStatus(false);
		}),
		ButtonData("VIDEO", [&]() {
			cout << "VIDEO" << endl;
			//canvas->SetVisibilityStatus(false);
		}),
		ButtonData("CONTROLLER", [&]() {
			cout << "CONTROLLER" << endl;
			//canvas->SetVisibilityStatus(false);
		}),
		ButtonData("KEYBOARD", [&]() {
			cout << "KEYBOARD" << endl;
			//canvas->SetVisibilityStatus(false);
		}),
		ButtonData("BACK", [&]() {
			owner->SetStatus(true);
			canvas->SetVisibilityStatus(false);
		})
	};

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _gapY = _buttonSize.y * 15.0f / 100.0f;
	const float _gridPosY = _windowSize.y * 0.35f;

	const int _dataCount = (int)_allData.size();
	for (int _index = 0; _index < _dataCount; _index++)
	{
		float _buttonPosY = _gridPosY + _buttonSize.y * _index + _gapY * _index;
		_buttonPosY += _index == _dataCount - 1 ? _windowSize.y * 0.15f : 0.0f;
		const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);
		Button* _button = new Button(ShapeData(_buttonPos, _buttonSize, ""));
		_button->GetData().hoveredCallback = [&]()
		{
			if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
			{
				const Vector2f& _position = _hoveredButton->GetDrawable()->getPosition();
				pointer->SetShapePosition(_position);
			}
		};
		_button->GetData().pressedCallback = _allData[_index].callback;

		_button->GetDrawable()->setFillColor(Color::Transparent);
		buttons.push_back(_button);
		canvas->AddWidget(_button);

		Label* _title = new Label(TextData(_allData[_index].text, Vector2f(_halfWindowX, _buttonPos.y), FONT, 20));
		_button->SetForeground(_title);
		canvas->AddWidget(_title);
	}

	pointer = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _gridPosY), Vector2f(_buttonSize.x, _buttonSize.y), PATH_POINTER));
	canvas->AddWidget(pointer);

	#pragma endregion
}