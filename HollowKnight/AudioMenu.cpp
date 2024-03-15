#include "AudioMenu.h"
#include "Game.h"
#include "MusicManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "Macro.h"
#include "SoundData.h"

#define PATH_MINUS "UIs/Menus/Options/Audio/Minus.png"
#define PATH_PLUS "UIs/Menus/Options/Audio/Plus.png"
#define PATH_LINE "UIs/Menus/Options/Audio/music_line.png"
#define PATH_INDICATOR "UIs/Menus/Options/Audio/Indicator.png"
#define SOUND_CLICK "Ui/ui_option_click"
#define MUSIC_SAVE "SaveOption"

AudioMenu::AudioMenu(Menu* _owner) : Menu("Audio", _owner)
{
	minValue = 0;
	maxValue = 0;
	factor = 0;

	soundValue = 50.0f;
	musicValue = 50.0f;
	masterValue = 50.0f;
	buttons = vector<Button*>();
	indicators = map<string, ShapeWidget*>();
}


void AudioMenu::Init()
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
			AudioButtonData("Master Volume",
			{"-", [&]() {
					if (MoveIndicator("Master Volume", -10.0f))
					{
						if (MoveIndicator("Sound Volume", -10.0f))
						{
							soundValue -= 10.0f;
							
							SoundManager::GetInstance().AdjustAllVolume(soundValue);
							new SoundData(SOUND_CLICK, 100, false);
							cout << "soundValue :" << soundValue << endl << endl;
						}
						if (MoveIndicator("Music Volume", -10.0f))
						{
							musicValue -= 10.0f;
							MusicManager::GetInstance().AdjustAllVolume(musicValue);
							new SoundData(SOUND_CLICK, 100, false);
							cout << "musicValue :" << musicValue << endl << endl;;
						}
						masterValue -= 10.0f;
						new SoundData(SOUND_CLICK, 100, false);
						cout << "masterValue :" << masterValue << endl << endl;;
					}
				}
			},
			{"+", [&]() {
					if (MoveIndicator("Master Volume", 10.0f))
					{
						masterValue += 10.0f;
						new SoundData(SOUND_CLICK, 100, false);
						cout << "masterValue :" << masterValue << endl << endl;;
						// Save(to_string(masterValue), MUSIC_SAVE);
					}
				}
			}),
			AudioButtonData("Sound Volume",
			{"-", [&]() {
					if (MoveIndicator("Sound Volume", -10.0f))
					{
						soundValue -= 10.0f;
						SoundManager::GetInstance().AdjustAllVolume(soundValue);
						new SoundData(SOUND_CLICK, 100, false);
						cout << "soundValue :" << soundValue << endl << endl;;
					}
				}
			},
			{"+", [&]() {
					if (soundValue + 10.0f <= masterValue && MoveIndicator("Sound Volume", 10.0f))
					{
						soundValue += 10.0f;
						SoundManager::GetInstance().AdjustAllVolume(soundValue);
						new SoundData(SOUND_CLICK, 100, false);
						cout << "soundValue :" << soundValue << endl << endl;;
					}
				}
			}),
			AudioButtonData("Music Volume",
			{"-", [&]() {
					if (MoveIndicator("Music Volume", -10.0f))
					{
						musicValue -= 10.0f;
						MusicManager::GetInstance().AdjustAllVolume(musicValue);
						new SoundData(SOUND_CLICK, 100, false);
						cout << "musicValue :" << musicValue << endl << endl;;
					}
				}
			},
			{"+", [&]() {
					if (musicValue + 10.0f <= masterValue && MoveIndicator("Music Volume", 10.0f))
					{
						musicValue += 10.0f;
						MusicManager::GetInstance().AdjustAllVolume(musicValue);
						new SoundData(SOUND_CLICK, 100, false);
						cout << "musicValue :" << musicValue << endl << endl;;
					}
				}
			}),
		}
	};

	const Vector2f& _buttonSize = Vector2f(600.0f, 70.0f);
	const float _gapY = _buttonSize.y * 20.0f / 100.0f;
	const float _gridPosY = _titleBarPosY + 100.0f;

	const int _dataCount = static_cast<int>(_audioButtonsData.size());

	for (int _i = 0; _i < _dataCount; _i++)
	{
		float _buttonPosY = _gridPosY + _buttonSize.y * _i + _gapY * _i;
		const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);
		const Vector2f& _buttonSize = Vector2f(25.0f, 25.0f);
		const Vector2f& _hoverSize = Vector2f(600.0f, 70.0f);

		Button* _button = new Button(ShapeData(_buttonPos, _hoverSize, ""));
		_button->GetDrawable()->setFillColor(Color::Transparent);
		_button->GetData().hoveredCallback = [&]()
		{
			if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
			{
				ShapeObject* _object = _hoveredButton->GetObject();
				const Vector2f& _position = _object->GetShapePosition();
				const float _halfSizeX = _object->GetShapeSize().x * 0.4f;
				const Vector2f& _offset = Vector2f(_halfSizeX, 0.0f);
				pointerLeft->SetShapePosition(_position - _offset);
				pointerRight->SetShapePosition(_position + _offset);
			}
		};
		buttons.push_back(_button);
		canvas->AddWidget(_button);

		Button* _buttonMinus = new Button(ShapeData(Vector2f(_buttonPos.x, _buttonPos.y), _buttonSize, PATH_MINUS));
		_buttonMinus->GetData().pressedCallback = _audioButtonsData[_i].minusButton.callback;
		canvas->AddWidget(_buttonMinus);

		Button* _buttonPlus = new Button(ShapeData(Vector2f(_buttonPos.x + 200.0f, _buttonPos.y), _buttonSize, PATH_PLUS));
		_buttonPlus->GetData().pressedCallback = _audioButtonsData[_i].plusButton.callback;
		canvas->AddWidget(_buttonPlus);

		Label* _title = new Label(TextData(_audioButtonsData[_i].title, Vector2f(_halfWindowX / 1.25f, _buttonPos.y - 10.0f), FONT, 20));
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
		indicators.insert(make_pair(_audioButtonsData[_i].title, _indicator));
		canvas->AddWidget(_indicator);
	}

	#pragma endregion

	#pragma region Back

	Vector2f _backSize = Vector2f(200.0f, 50.0f);
	const float _buttonPosY = _windowSize.y * 0.9f;
	const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);

	backButton = new Button(ShapeData(_buttonPos, _backSize, ""));
	backButton->GetData().hoveredCallback = [&]()
	{
		MovePointers(backButton);
	};
	backButton->GetData().pressedCallback = [&]() {
		owner->SetStatus(true);
		canvas->SetVisibilityStatus(false);
	};
	backButton->GetDrawable()->setFillColor(Color::Transparent);
	canvas->AddWidget(backButton);

	Label* _buttonText = new Label(TextData("BACK", Vector2f(_halfWindowX, _buttonPos.y), FONT, 20));

	backButton->SetForeground(_buttonText);
	canvas->AddWidget(_buttonText);

	#pragma endregion

	#pragma region Pointer

	Menu::Init();
	MovePointers(buttons.front());

	#pragma endregion
}

bool AudioMenu::MoveIndicator(const string _key, const float _percent)
{
	const float _value = _percent * factor / 100.0f;
	
	Shape* _shape = indicators[_key]->GetDrawable();
	const float _posX = _shape->getPosition().x;

	if (_posX + _value >= minValue && _posX + _value <= maxValue)
	{
		_shape->move(_value, 0.0f);
		return true;
	}

	return false;
}
