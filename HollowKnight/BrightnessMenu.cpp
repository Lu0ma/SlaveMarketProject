#include "BrightnessMenu.h"
#include "Game.h"

#define PATH_IMAGE "UIs/Brightness/Image.jpg"
#define PATH_LINE "../Menu/Audio/music_line.png"
#define PATH_INDICATOR "../Menu/Audio/Indicator.png"
#define PATH_MINUS "../Menu/Audio/Minus.png"
#define PATH_PLUS "../Menu/Audio/Plus.png"

BrightnessMenu::BrightnessMenu(Menu* _owner) : Menu("Brightness", _owner)
{
	minValue = 0;
	maxValue = 0;
	factor = 5.0f;
	brightButton = nullptr;
	indicator = nullptr;
}


void BrightnessMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	#pragma region Background

	const Vector2f& _backgroundPos = _windowSize / 2.0f;
	ShapeWidget* _background = new ShapeWidget(ShapeData(_backgroundPos, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);

	#pragma endregion

	#pragma region Image

	const float _imagePosX = _windowSize.x * 0.5f;
	const float _imagePosY = _windowSize.x * 0.175f;
	const Vector2f& _imagePos = Vector2f(_imagePosX, _imagePosY);
	const Vector2f& _imageSize = Vector2f(_windowSize.x * 0.5f, _windowSize.y * 0.45f);
	ShapeWidget* _image = new ShapeWidget(ShapeData(_imagePos, _imageSize, PATH_IMAGE));
	_image->SetCanApplyShader(true);
	canvas->AddWidget(_image);

	#pragma endregion

	#pragma region Description

	const float _descriptionPosY = _imageSize.y * 0.5f + _imagePosY + 50.0f;
	Label* _description = new Label(TextData("Adjust brightness to your desired level.", Vector2f(_halfWindowX, _descriptionPosY), FONT, 15));
	canvas->AddWidget(_description);

	#pragma endregion

	#pragma region Button

	const Vector2f& _buttonSize = Vector2f(600.0f, 150.0f);
	const float _buttonPosY = _descriptionPosY + 100.0f;
	brightButton = new Button(ShapeData(Vector2f(_halfWindowX, _buttonPosY), _buttonSize, ""));
	brightButton->GetDrawable()->setFillColor(Color::Transparent);
	brightButton->GetData().hoveredCallback = [&]()
	{
		ShapeObject* _object = brightButton->GetObject();
		const Vector2f& _position = brightButton->GetShapePosition();
		const float _halfSizeX = _object->GetShapeSize().x * 0.4f;
		const Vector2f& _offset = Vector2f(_halfSizeX, 0.0f);
		pointerLeft->SetShapePosition(_position - _offset);
		pointerRight->SetShapePosition(_position + _offset);
	};
	canvas->AddWidget(brightButton);

	Label* _title = new Label(TextData("Brightness", Vector2f(_halfWindowX / 1.25f, _buttonPosY - 10.0f), FONT, 20));
	canvas->AddWidget(_title);

	const Vector2f& _littleButtonSize = Vector2f(25.0f, 25.0f);
	Button* _buttonMinus = new Button(ShapeData(Vector2f(_halfWindowX, _buttonPosY), _littleButtonSize, PATH_MINUS));
	_buttonMinus->GetData().pressedCallback = [&]()
	{
		if (MoveIndicator(-factor))
		{
			Game::GetBrightness()->UpdateBrightness(-factor);
		}
	};
	canvas->AddWidget(_buttonMinus);

	Button* _buttonPlus = new Button(ShapeData(Vector2f(_halfWindowX + 200.0f, _buttonPosY), _littleButtonSize, PATH_PLUS));
	_buttonPlus->GetData().pressedCallback = [&]()
	{
		if (MoveIndicator(factor))
		{
			Game::GetBrightness()->UpdateBrightness(factor);
		}
	};
	canvas->AddWidget(_buttonPlus);

	const float _volumeBarPosX = _halfWindowX + 100.0f;
	const float _volumeBarSizeX = 100.0f;
	ShapeWidget* _volumeBar = new ShapeWidget(ShapeData(Vector2f(_volumeBarPosX, _buttonPosY), Vector2f(_volumeBarSizeX, 2.0f), PATH_LINE));
	canvas->AddWidget(_volumeBar);

	minValue = _volumeBarPosX - _volumeBarSizeX / 2.0f;
	maxValue = _volumeBarPosX + _volumeBarSizeX / 2.0f;
	
	const Vector2f& _sizeIndicator = Vector2f(67.0f / 1.25f, 67.0f / 1.25f);
	const Vector2f& _positionIndicator = Vector2f(_volumeBarPosX, _buttonPosY - 25.0f);
	indicator = new ShapeWidget(ShapeData(_positionIndicator, _sizeIndicator, PATH_INDICATOR));
	canvas->AddWidget(indicator);

	#pragma endregion

	#pragma region Back

	const Vector2f& _backButtonSize = Vector2f(200.0f, 50.0f);
	const float _backButtonPosY = _windowSize.y * 0.9f;
	const Vector2f& _backButtonPos = Vector2f(_halfWindowX, _backButtonPosY);

	backButton = new Button(ShapeData(_backButtonPos, _backButtonSize, ""));
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

	Label* _buttonText = new Label(TextData("DONE", Vector2f(_halfWindowX, _backButtonPosY), FONT, 20));
	backButton->SetForeground(_buttonText);
	canvas->AddWidget(_buttonText);

	Menu::Init();
	MovePointers(backButton);

	#pragma endregion
}

bool BrightnessMenu::MoveIndicator(const float _percent)
{
	const float _value = _percent * (maxValue - minValue) / 100.0f;

	Shape* _shape = indicator->GetDrawable();
	const float _posX = _shape->getPosition().x;

	if (_posX + _value >= minValue && _posX + _value <= maxValue)
	{
		_shape->move(_value, 0.0f);
		return true;
	}

	return false;
}