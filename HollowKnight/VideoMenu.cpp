#include "VideoMenu.h"
#include "Game.h"

VideoMenu::VideoMenu(Menu* _owner) : Menu("VideoMenu", _owner)
{
	buttons = vector<Button*>();
	brightness = new BrightnessMenu(this);
}


void VideoMenu::ChangeResolution()
{

}

void VideoMenu::ToggleFullScreen()
{

}

void VideoMenu::ChangeParticule()
{

}


void VideoMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	#pragma region Background
	
	ShapeWidget* _background = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);

	#pragma endregion

	#pragma region Title

	const float _titlePosY = _windowSize.y * 0.1f;
	Label* _title = new Label(TextData("Video", Vector2f(_halfWindowX, _titlePosY), FONT, 36));
	canvas->AddWidget(_title);

	const float _titleBarPosY = _titlePosY + 75.0f;
	const Vector2f& _titleBarSize = Vector2f(_windowSize.x * 0.4f, 50.0f);
	const float _halfTitleBarSizeX = _titleBarSize.x * 0.45f;
	ShapeWidget* _titleBar = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _titleBarPosY), _titleBarSize, PATH_TITLE_ICON));
	canvas->AddWidget(_titleBar);

	#pragma endregion

	#pragma region Grid

	struct VideoButtonData
	{
		string title;
		function<void()> callback;
		string description;
	};

	const vector<VideoButtonData>& _buttons = {
		{
			"Resolution:",
			[&]() { ChangeResolution(); },
			""
		},
		{
			"Full Screen:",
			[&]() { ToggleFullScreen(); },
			""
		},
		{
			"Particule Effects:",
			[&]() { ChangeParticule(); },
			"Reduce to improve performance on lower end machines."
		},
		{
			"Frame Rate:",
			[&]() { ChangeParticule(); },
			"Reduce to improve performance on lower end machines."
		},
		{
			"Brightness:",
			[&]() {
				canvas->SetVisibilityStatus(false);
				brightness->SetStatus(true);
			},
			"Reduce to improve performance on lower end machines."
		},
	};

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _gapY = _buttonSize.y * 15.0f / 100.0f;
	const float _gridPosY = _titleBarPosY + 75.0f;

	const int _dataCount = (int)_buttons.size();
	for (int _index = 0; _index < _dataCount; _index++)
	{
		float _buttonPosY = _gridPosY + _buttonSize.y * _index + _gapY * _index;
		_buttonPosY += _index == _dataCount - 1 ? _gapY : 0.0f;
		const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);
		Button* _button = new Button(ShapeData(_buttonPos, _buttonSize, ""));
		_button->GetData().hoveredCallback = [&]()
		{
			if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
			{
				MovePointers(_hoveredButton);
			}
		};
		_button->GetData().pressedCallback = _buttons[_index].callback;

		_button->GetDrawable()->setFillColor(Color::Transparent);
		buttons.push_back(_button);
		canvas->AddWidget(_button);

		const float _buttonTitlePosX = _halfWindowX - _halfTitleBarSizeX;
		Label* _title = new Label(TextData(_buttons[_index].title, Vector2f(_buttonTitlePosX, _buttonPos.y), FONT, 22), AT_LEFT);
		canvas->AddWidget(_title);

		const float __valueTextPosX = _halfWindowX + _halfTitleBarSizeX;
		Label* _valueText = new Label(TextData("On", Vector2f(__valueTextPosX, _buttonPos.y), FONT, 16), AT_RIGHT);
		canvas->AddWidget(_valueText);

		Label* _description = new Label(TextData(_buttons[_index].description, Vector2f(_halfWindowX, _buttonPos.y + 35.0f), FONT, 14));
		canvas->AddWidget(_description);
	}

	Menu::Init();
	MovePointers(buttons.front());

	#pragma endregion

	#pragma region Back

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
}