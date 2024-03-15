#include "VideoMenu.h"
#include "Game.h"
#include "TextureManager.h"

using namespace Style;

#define PATH_MINUS "UIs/Menus/Options/Audio/Minus.png"
#define PATH_PLUS "UIs/Menus/Options/Audio/Plus.png"
#define PATH_CHECKBOX_EMPTY "UIs/Menus/Options/Video/EmptyCheckbox.png"
#define PATH_CHECKBOX_FULL "UIs/Menus/Options/Video/FullCheckbox.png"

VideoMenu::VideoMenu(Menu* _owner) : Menu("VideoMenu", _owner)
{
	buttons = vector<Button*>();

	resolutionIndex = 0;
	resolutionText = nullptr;

	fullScreenActivated = false;
	fullscreenText = nullptr;

	particuleStateIndex = 0;
	particuleText = nullptr;

	canUpdateFrameRate = true;
	capFrameRate = false;
	frameRate = 60;
	maxFrameRate = 300;
	frameRateFactor = 5;
	frameRateButton = nullptr;
	frameRateText = nullptr;

	brightnessButton = nullptr;
	brightness = new BrightnessMenu(this);
}


void VideoMenu::ChangeResolution()
{
	const Vector2u _resolutions[] = {
		Vector2u(800, 600),
		Vector2u(1280, 720),
		Vector2u(1920, 1080),
		//Vector2u(3840, 2160),
	};

	resolutionIndex++;
	resolutionIndex %= 3;
	resolution = _resolutions[resolutionIndex];
	resolutionText->SetString(to_string(resolution.x) + "x" + to_string(resolution.y));

	if (!fullScreenActivated)
	{
		Game::GetWindow().setSize(resolution);
	}
}

void VideoMenu::ToggleFullScreen()
{
	fullScreenActivated = !fullScreenActivated;
	fullscreenText->SetString(fullScreenActivated ? "On" : "Off");

	Game::GetWindow().create(VideoMode(1920, 1080), "HollowKnight", fullScreenActivated ? Fullscreen : Default);
	resolution = Vector2u(1920, 1080);
}

void VideoMenu::ChangeParticule()
{
	const string _particulesState[] = {
		"Light",
		"Medium",
		"Hard"
	};

	particuleStateIndex++;
	particuleStateIndex %= 3;
	particuleText->SetString(_particulesState[particuleStateIndex]);
}

void VideoMenu::UpdateFrameRate(const int _factor)
{
	if (!canUpdateFrameRate) return;

	frameRate += _factor * frameRateFactor;
	frameRate = frameRate < 0 ? 0 : frameRate;
	frameRate = frameRate > maxFrameRate ? maxFrameRate : frameRate;
	frameRateText->SetString(to_string(frameRate));

	Game::GetWindow().setFramerateLimit(frameRate);
}

void VideoMenu::ToggleCapFrameRate()
{
	capFrameRate = !capFrameRate;

	const string& _path = capFrameRate ? PATH_CHECKBOX_FULL : PATH_CHECKBOX_EMPTY;
	TextureManager::GetInstance().Load(checkBox->GetObject(), _path);

	const Color& _color = capFrameRate ? Color(127, 127, 127, 255) : Color::White;
	frameRateText->GetDrawable()->setFillColor(_color);

	canUpdateFrameRate = !capFrameRate;
	Game::GetWindow().setFramerateLimit(capFrameRate ? 0 : frameRate);
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
		Label*& valueText;
		function<void()> callback;
		string description;
	};

	vector<VideoButtonData*> _buttons = {
		new VideoButtonData({
			"Resolution:",
			resolutionText,
			[&]() { ChangeResolution(); },
			""
		}),
		new VideoButtonData({
			"Full Screen:",
			fullscreenText,
			[&]() { ToggleFullScreen(); },
			""
		}),
		new VideoButtonData({
			"Particule Effects:",
			particuleText,
			[&]() { ChangeParticule(); },
			"Reduce to improve performance on lower end machines."
		}),
	};

	const Vector2f& _buttonSize = Vector2f(_titleBarSize.x * 1.2f, 80.0f);
	const float _gapY = 15.0f;
	float _buttonPosY = _titleBarPosY + 50.0f;

	const int _dataCount = (int)_buttons.size();
	for (int _index = 0; _index < _dataCount; _index++)
	{
		VideoButtonData* _buttonData = _buttons[_index];

		_buttonPosY += _buttonSize.y / 2.0f + _gapY;
		const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);
		Button* _button = new Button(ShapeData(_buttonPos, _buttonSize, ""));
		_button->GetDrawable()->setFillColor(Color::Transparent);
		_button->GetData().hoveredCallback = [&]()
		{
			if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
			{
				ShapeObject* _object = _hoveredButton->GetObject();
				const Vector2f& _position = _object->GetShapePosition();
				const float _halfSizeX = _object->GetShapeSize().x * 0.45f;
				const Vector2f& _offsetX = Vector2f(_halfSizeX, 0.0f);
				const Vector2f& _offsetY = Vector2f(0.0f, 10.0f);
				pointerLeft->SetShapePosition(_position - _offsetX + _offsetY);
				pointerRight->SetShapePosition(_position + _offsetX + _offsetY);
			}
		};
		_button->GetData().pressedCallback = _buttonData->callback;
		buttons.push_back(_button);
		canvas->AddWidget(_button);

		const float _buttonTitlePosX = _halfWindowX - _halfTitleBarSizeX;
		Label* _title = new Label(TextData(_buttonData->title, Vector2f(_buttonTitlePosX, _buttonPos.y), FONT, 22), AT_LEFT);
		canvas->AddWidget(_title);

		const float _valueTextPosX = _halfWindowX + _halfTitleBarSizeX;
		_buttonData->valueText = new Label(TextData("", Vector2f(_valueTextPosX, _buttonPos.y), FONT, 16), AT_RIGHT);
		_buttonData->callback();
		canvas->AddWidget(_buttonData->valueText);

		Label* _description = new Label(TextData(_buttonData->description, Vector2f(_halfWindowX, _buttonPos.y + 25.0f), FONT, 12));
		canvas->AddWidget(_description);
	}

	#pragma endregion

	#pragma region FrameRate

	const float _frameRateButtonPosY = buttons.back()->GetShapePosition().y + _buttonSize.y / 2.0f + 15.0f;
	frameRateButton = new Button(ShapeData(Vector2f(_halfWindowX, _frameRateButtonPosY), _buttonSize, ""));
	frameRateButton->GetDrawable()->setFillColor(Color::Transparent);
	frameRateButton->GetData().hoveredCallback = [&]()
	{
		ShapeObject* _object = frameRateButton->GetObject();
		const Vector2f& _position = _object->GetShapePosition();
		const float _halfSizeX = _object->GetShapeSize().x * 0.45f;
		const Vector2f& _offsetX = Vector2f(_halfSizeX, 0.0f);
		const Vector2f& _offsetY = Vector2f(0.0f, 10.0f);
		pointerLeft->SetShapePosition(_position - _offsetX + _offsetY);
		pointerRight->SetShapePosition(_position + _offsetX + _offsetY);
	};
	canvas->AddWidget(frameRateButton);

	const float _buttonTitlePosX = _halfWindowX - _halfTitleBarSizeX;
	Label* _frameRateTitle = new Label(TextData("Frame Rate", Vector2f(_buttonTitlePosX, _frameRateButtonPosY), FONT, 20), AT_LEFT);
	canvas->AddWidget(_frameRateTitle);

	const Vector2f& _littleButtonSize = Vector2f(25.0f, 25.0f);
	Button* _buttonMinus = new Button(ShapeData(Vector2f(_halfWindowX + 50.0f, _frameRateButtonPosY + 10.0f), _littleButtonSize, PATH_MINUS));
	_buttonMinus->GetData().pressedCallback = [&]() { UpdateFrameRate(-1); };
	canvas->AddWidget(_buttonMinus);

	frameRateText = new Label(TextData("60", Vector2f(_halfWindowX + 100.0f, _frameRateButtonPosY), FONT, 20), AT_CENTER);
	canvas->AddWidget(frameRateText);

	Button* _buttonPlus = new Button(ShapeData(Vector2f(_halfWindowX + 150.0f, _frameRateButtonPosY + 10.0f), _littleButtonSize, PATH_PLUS));
	_buttonPlus->GetData().pressedCallback = [&]() { UpdateFrameRate(1); };
	canvas->AddWidget(_buttonPlus);

	checkBox = new Button(ShapeData(Vector2f(_halfWindowX + 200.0f, _frameRateButtonPosY + 10.0f), _littleButtonSize * 2.0f, PATH_CHECKBOX_EMPTY));
	checkBox->GetData().pressedCallback = [&]() { ToggleCapFrameRate(); };
	canvas->AddWidget(checkBox);

	#pragma endregion

	#pragma region Back

	const float _backButtonPosY = _windowSize.y * 0.9f;
	const Vector2f& _backButtonPos = Vector2f(_halfWindowX, _backButtonPosY);

	backButton = new Button(ShapeData(_backButtonPos, _buttonSize, ""));
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

	Label* _buttonText = new Label(TextData("Back", Vector2f(_halfWindowX, _backButtonPosY), FONT, 20));
	backButton->SetForeground(_buttonText);
	canvas->AddWidget(_buttonText);

	#pragma endregion

	#pragma region Brightness

	const float _brightnessButtonPosY = _backButtonPosY - 50.0f;
	const Vector2f& _brightnessButtonPos = Vector2f(_halfWindowX, _brightnessButtonPosY);

	brightnessButton = new Button(ShapeData(_brightnessButtonPos, _buttonSize, ""));
	brightnessButton->GetData().hoveredCallback = [&]()
	{
		MovePointers(brightnessButton);
	};
	brightnessButton->GetData().pressedCallback = [&]() {
		canvas->SetVisibilityStatus(false);
		brightness->SetStatus(true);
	};
	brightnessButton->GetDrawable()->setFillColor(Color::Transparent);
	canvas->AddWidget(brightnessButton);

	Label* _brightnessButtonText = new Label(TextData("Brightness", Vector2f(_halfWindowX, _brightnessButtonPosY), FONT, 20));
	brightnessButton->SetForeground(_brightnessButtonText);
	canvas->AddWidget(_brightnessButtonText);

	#pragma endregion

	#pragma region Pointer

	Menu::Init();
	MovePointers(buttons.front());

	#pragma endregion
}