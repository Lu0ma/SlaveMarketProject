#include "Audio.h"
#include "Game.h"
#include "MusicManager.h"
#include "SoundManager.h"
#include "HUD.h"

#define PATH_BACKGROUND "UIs/Menus/Background.png"
#define PATH_TITLE_ICON "UIs/Menus/TitleIcon.png"
#define PATH_POINTER "../Menu/Audio/Pointer.png"
#define FONT "Font.ttf"
#define PATH_MINUS "../Menu/Audio/Minus.png"
#define PATH_PLUS "../Menu/Audio/Plus.png"
#define PATH_LINE "../Menu/Audio/music_line.png"
#define PATH_INDICATOR "../Menu/Audio/Indicator.png"

Audio::Audio(Menu* _owner) : Menu("Audio", _owner)
{
	buttons = vector<Button*>();
	pointer = nullptr;
	value = 0;
	maxValue = 0;
	minValue = 0;
	factor = 0;
}

Audio::~Audio()
{
	delete pointer;

	for (Button* _button : buttons)
	{
		delete _button;
	}
	for (auto& _widget : indicators)
	{
		delete _widget.second;
	}
}

void Audio::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

#pragma region Background

	ShapeWidget* _background = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);

#pragma endregion

#pragma region Title

	const float _tilePosY = _windowSize.y * 0.15f;
	Label* _title = new Label(TextData("Audio", Vector2f(_halfWindowX, _tilePosY), FONT, 32));
	canvas->AddWidget(_title);

	const float _tileIconPosY = _tilePosY + 50.0f;
	ShapeWidget* _titleIcon = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _tileIconPosY), Vector2f(765.0f, 78.0f), PATH_TITLE_ICON));
	_titleIcon->GetDrawable()->setScale(0.6f, 0.6f);
	canvas->AddWidget(_titleIcon);

#pragma endregion

#pragma region Volumes

	struct ButtonInfo
	{
		string name;
		function<void()> callback;
	};

	struct AudioButtonData
	{
		string title;
		ButtonInfo minusButton;
		ButtonInfo plusButton;

		AudioButtonData(const string& _title, const ButtonInfo& _minusButton, const ButtonInfo& _plusButton)
		{
			title = _title;
			minusButton = _minusButton;
			plusButton = _plusButton;
		};
	};

	const vector<AudioButtonData>& _audioButtonsData = {
		{
			AudioButtonData("Master Volume:",
			{"-", [&]() {
				MusicManager::GetInstance().AdjustAllVolume(-10.0f);
				SoundManager::GetInstance().AdjustAllVolume(-10.0f);
				MoveIndicator("0", -10.0f);
				}
			},
			{"+", [&]() {
				MusicManager::GetInstance().AdjustAllVolume(10.0f);
				SoundManager::GetInstance().AdjustAllVolume(10.0f);
				MoveIndicator("0",10.0f);
				}
			}),
			AudioButtonData("Sound Volume:",
			{"-", [&]() {
				SoundManager::GetInstance().AdjustAllVolume(-10.0f);
				MoveIndicator("1",-10.0f);
				}
			},
			{"+", [&]() {
				SoundManager::GetInstance().AdjustAllVolume(10.0f);
				MoveIndicator("1",10.0f);
				}
			}),
			AudioButtonData("Music Volume:",
			{"-", [&]() {
				MusicManager::GetInstance().AdjustAllVolume(-10.0f);
				MoveIndicator("2",-10.0f);

				}
			},
			{"+", [&]() {
				MusicManager::GetInstance().AdjustAllVolume(10.0f);
				MoveIndicator("2",10.0f);

				}
			}),
		}
	};

	const Vector2f& _buttonSize = Vector2f(600.0f, 70.0f);
	const float _gapY = _buttonSize.y * 20.0f / 100.0f;
	const float _gridPosY = _windowSize.y * 0.35f;

	const int _dataCount = static_cast<int>(_audioButtonsData.size());

	for (int _i = 0; _i < _dataCount; _i++)
	{
		float _buttonPosY = _gridPosY + _buttonSize.y * _i + _gapY * _i;
		const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);
		const Vector2f& _buttonSize = Vector2f(25.0f, 25.0f);
		const Vector2f& _hoverSize = Vector2f(600.0f, 70.0f);
		Button* _button = new Button(ShapeData(_buttonPos, _hoverSize, ""));

		_button->GetData().hoveredCallback = [&]()
			{
				if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
				{
					const Vector2f& _position = _hoveredButton->GetDrawable()->getPosition();
					pointer->SetShapePosition(_position);
				}
			};
		Button* _buttonMinus = new Button(ShapeData(Vector2f(_buttonPos.x, _buttonPos.y), _buttonSize, PATH_MINUS));
		_buttonMinus->GetData().pressedCallback = _audioButtonsData[_i].minusButton.callback;

		Button* _buttonPlus = new Button(ShapeData(Vector2f(_buttonPos.x + 200.0f, _buttonPos.y), _buttonSize, PATH_PLUS));
		_buttonPlus->GetData().pressedCallback = _audioButtonsData[_i].plusButton.callback;

		_button->GetDrawable()->setFillColor(Color::Transparent);
		buttons.push_back(_button);
		buttons.push_back(_buttonMinus);
		buttons.push_back(_buttonPlus);
		canvas->AddWidget(_button);
		canvas->AddWidget(_buttonMinus);
		canvas->AddWidget(_buttonPlus);

		Label* _title = new Label(TextData(_audioButtonsData[_i].title, Vector2f(_halfWindowX / 1.25f, _buttonPos.y - 10.0f), FONT, 20));
		_button->SetForeground(_title);
		canvas->AddWidget(_title);

		const float _volumeBarPosX = _buttonPos.x + 100.0f;
		const float _volumeBarSizeX = 100.0f;
		factor = _volumeBarSizeX;
		ShapeWidget* _volumeBar = new ShapeWidget(ShapeData(Vector2f(_volumeBarPosX, _buttonPos.y), Vector2f(_volumeBarSizeX, 2.0f), PATH_LINE));
		canvas->AddWidget(_volumeBar);
		minValue = _volumeBarPosX - 50.0f;
		maxValue = minValue + _volumeBarSizeX;

		const Vector2f& _sizeIndicator = Vector2f(67.0f / 1.25f, 67.0f / 1.25f);
		const Vector2f& _positionIndicator = Vector2f(_volumeBarPosX, _buttonPos.y - 25.0f);

		ShapeWidget* _indicator = new ShapeWidget(ShapeData(_positionIndicator, _sizeIndicator, PATH_INDICATOR));
		indicators.insert(make_pair(to_string(_i), _indicator));
		canvas->AddWidget(_indicator);

	}

#pragma endregion

#pragma region Pointer
	const Vector2f& _pointerSize = Vector2f(647.0f , 67.0f);
	const float _gridPosX = _halfWindowX + _buttonSize.x * 5.0f / 100.0f;
	pointer = new ShapeWidget(ShapeData(Vector2f(_gridPosX, _gridPosY), Vector2f(_pointerSize.x, _pointerSize.y), PATH_POINTER));
	canvas->AddWidget(pointer);
#pragma endregion

#pragma region Back

	Vector2f _backSize = Vector2f(200.0f, 50.0f);
	const float _buttonPosY = _windowSize.y * 0.9f;
	const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);

	Button* backButton = new Button(ShapeData(_buttonPos, _backSize, ""));
	backButton->GetData().pressedCallback = [&]() {
		owner->SetStatus(true);
		canvas->SetVisibilityStatus(false);
		};
	backButton->GetDrawable()->setFillColor(Color::Transparent);
	canvas->AddWidget(backButton);

	Label* _buttonText = new Label(TextData("BACK", Vector2f(_halfWindowX, _buttonPos.y), FONT, 20));
	backButton->SetForeground(_buttonText);
	canvas->AddWidget(_buttonText);

	ShapeWidget* pointer = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _buttonPos.y), Vector2f(_backSize.x, _backSize.y), PATH_POINTER));
	canvas->AddWidget(pointer);

#pragma endregion
}

void Audio::MoveIndicator(const string _key, const float _percent)
{
	value = _percent * factor / 100.0f;
	for (auto& _pair : indicators)
	{
		if (_pair.first == _key)
		{
			_pair.second->GetDrawable()->move(value, 0.0f);
			if (_pair.second->GetDrawable()->getPosition().x < minValue || _pair.second->GetDrawable()->getPosition().x > maxValue)
			{
				_pair.second->GetDrawable()->move(-value, 0.0f);
			}
		}
	}
}
