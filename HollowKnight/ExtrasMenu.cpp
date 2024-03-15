#include "ExtrasMenu.h"
#include "Game.h"

ExtrasMenu::ExtrasMenu(Menu* _owner) : Menu("Extras", _owner)
{
	buttons = vector<Button*>();
	credits = new CreditsMenu(this);
	style = nullptr;
	styleButton = nullptr;
	indexStyles = -1;
}

void ExtrasMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	#pragma region Background

	ShapeWidget* _background = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);

	#pragma endregion

	#pragma region Title

	const float _titlePosY = _windowSize.y * 0.1f;
	Label* _title = new Label(TextData("Extras", Vector2f(_halfWindowX, _titlePosY), FONT, 36));
	canvas->AddWidget(_title);

	const float _titleBarPosY = _titlePosY + 75.0f;
	const Vector2f& _titleBarSize = Vector2f(_windowSize.x * 0.4f, 50.0f);
	const float _halfTitleBarSizeX = _titleBarSize.x * 0.45f;
	ShapeWidget* _titleBar = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _titleBarPosY), _titleBarSize, PATH_TITLE_ICON));
	canvas->AddWidget(_titleBar);

	#pragma endregion

	#pragma region Style

	struct StyleButton
	{
		string title;
		Label*& valueText;
		function<void()> callback;
	};

	StyleButton* _styleData = new StyleButton({
		"Menu Style :",
		style,
		[&]() {IncreaseIndexStyles(); }
		});


	const Vector2f& _styleButtonSize = Vector2f(750.0f, 50.0f);
	const float _stylesButtonPosY = _windowSize.y * 0.28f;
	const Vector2f& _styleButtonPos = Vector2f(_halfWindowX - 0.0f, _stylesButtonPosY);

	styleButton = new Button(ShapeData(_styleButtonPos, _styleButtonSize, ""));
	styleButton->GetData().hoveredCallback = [&]()
	{
		MovePointers(styleButton);
		ShapeObject* _object = styleButton->GetObject();
		const Vector2f& _position = _object->GetShapePosition() + Vector2f(150.0f, 0.0f);
		const float _sizeX = _object->GetShapeSize().x;
		const Vector2f& _offsetX = Vector2f(_sizeX, 0.0f);
		const Vector2f& _offsetY = Vector2f(0.0f, 12.0f);
		pointerLeft->SetShapePosition(_position - (_offsetX * 0.76f) + _offsetY);
		pointerRight->SetShapePosition(_position + (_offsetX * 0.32f )+ _offsetY);
	};
	styleButton->GetData().pressedCallback = _styleData->callback;
	styleButton->GetDrawable()->setFillColor(Color::Transparent);
	canvas->AddWidget(styleButton);

	const Vector2f _stylePos = _styleButtonPos - Vector2f(180.0f, 0.0f);
	Label* _styleText = new Label(TextData(_styleData->title, _stylePos, FONT, 30), AT_RIGHT);
	styleButton->SetForeground(_styleText);
	canvas->AddWidget(_styleText);

	const float _valueTextPosX = _halfWindowX + _halfTitleBarSizeX;
	_styleData->valueText = new Label(TextData("", Vector2f(_valueTextPosX, _styleButtonPos.y), FONT, 30), AT_RIGHT);
	canvas->AddWidget(_styleData->valueText);

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
		ButtonData("Credits", [&]() {
			credits->SetStatus(true);
			canvas->SetVisibilityStatus(false);
		}),
		ButtonData("BACK", [&]() {
			owner->SetStatus(true);
			canvas->SetVisibilityStatus(false);
		})
	};

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _gapY = _buttonSize.y * 15.0f / 100.0f;
	const float _gridPosY = _titleBarPosY + 300.0f;

	const int _dataCount = (int)_allData.size();
	for (int _index = 0; _index < _dataCount; _index++)
	{
		float _buttonPosY = _gridPosY + _buttonSize.y * _index + _gapY * _index;
		_buttonPosY += _index == _dataCount - 1 ? _windowSize.y * 0.3f : 0.0f;
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

		//int _fontSize = _index == _dataCount - 1 ? 20 : 30;
		Label* _title = new Label(TextData(_allData[_index].text, Vector2f(_halfWindowX, _buttonPos.y), FONT, 30));
		_button->SetForeground(_title);
		canvas->AddWidget(_title);
	}

	Menu::Init();
	MovePointers(buttons.front());

	#pragma endregion

	/*#pragma region Credits

	const Vector2f& _creditsButtonSize = Vector2f(200.0f, 50.0f);
	const float _creditsButtonPosY = _windowSize.y * 0.3f;
	const Vector2f& _creditsButtonPos = Vector2f(_halfWindowX, _creditsButtonPosY);

	creditsButton = new Button(ShapeData(_creditsButtonPos, _creditsButtonSize, ""));
	creditsButton->GetData().pressedCallback = [&]() {
		owner->SetStatus(true);
		canvas->SetVisibilityStatus(true);
	};
	creditsButton->GetDrawable()->setFillColor(Color::Transparent);
	canvas->AddWidget(creditsButton);

	Label* _creditsText = new Label(TextData("CREDITS", _creditsButtonPos, FONT, 20));
	creditsButton->SetForeground(_creditsText);
	canvas->AddWidget(_creditsText);

	Menu::Init();
	MovePointers(creditsButton);

	#pragma endregion


	#pragma region Back

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

	Label* _buttonText = new Label(TextData("BACK", _buttonPos, FONT, 20));
	backButton->SetForeground(_buttonText);
	canvas->AddWidget(_buttonText);

	Menu::Init();
	MovePointers(backButton);

	#pragma endregion*/
	IncreaseIndexStyles();
}

void ExtrasMenu::IncreaseIndexStyles()
{
	vector<string> _styles = {
		"CLASSIC",
		"HIDDEN DREAM",
		"THE GRIMM TROUPE",
		"LIFE BLOOD",
		"GOD MASTER",
		"INFECTED",
		"VOID",
		"VOIDHEART"
	};

	indexStyles++;
	indexStyles %= 7;
	style->SetString(_styles[indexStyles]);

}