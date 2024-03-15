#include "OptionsMenu.h"
#include "Game.h"
#include "HUD.h"

#define SOUND_CONFIRM "Ui/ui_button_confirm"

OptionsMenu::OptionsMenu(Menu* _owner) : Menu("OptionsMenu", _owner)
{
	buttons = vector<Button*>();
	audio = new AudioMenu(this);
	video = new VideoMenu(this);
	controller = new ControllerMenu(this);
	keyboard = new KeyboardMenu(this);
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
	
	const float _titlePosY = _windowSize.y * 0.1f;
	Label* _title = new Label(TextData("Options", Vector2f(_halfWindowX, _titlePosY), FONT, 36));
	canvas->AddWidget(_title);

	const float _titleBarPosY = _titlePosY + 75.0f;
	const Vector2f& _titleBarSize = Vector2f(_windowSize.x * 0.4f, 50.0f);
	ShapeWidget* _titleBar = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _titleBarPosY), _titleBarSize, PATH_TITLE_ICON));
	canvas->AddWidget(_titleBar);

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
			//canvas->SetVisibilityStatus(false);
			new SoundData(SOUND_CONFIRM, 100, false);
		}),
		ButtonData("AUDIO", [&]() {
			audio->SetStatus(true);
			canvas->SetVisibilityStatus(false);
			new SoundData(SOUND_CONFIRM, 100, false);
		}),
		ButtonData("VIDEO", [&]() {
			video->SetStatus(true);
			canvas->SetVisibilityStatus(false);
			new SoundData(SOUND_CONFIRM, 100, false);
		}),
		ButtonData("CONTROLLER", [&]() {
			controller->SetStatus(true);
			canvas->SetVisibilityStatus(false);
			new SoundData(SOUND_CONFIRM, 100, false);
		}),
		ButtonData("KEYBOARD", [&]() {
			keyboard->SetStatus(true);
			canvas->SetVisibilityStatus(false);
			new SoundData(SOUND_CONFIRM, 100, false);
		}),
		ButtonData("BACK", [&]() {
			owner->SetStatus(true);
			canvas->SetVisibilityStatus(false);
			new SoundData(SOUND_CONFIRM, 100, false);
		})
	};

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _gapY = _buttonSize.y * 15.0f / 100.0f;
	const float _gridPosY = _titleBarPosY + 75.0f;

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
				MovePointers(_hoveredButton);
				
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

	Menu::Init();
	MovePointers(buttons.front());

	#pragma endregion
}