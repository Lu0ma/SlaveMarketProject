#include "TitleMenu.h"
#include "Game.h"
#include "HUD.h"
#include "ActorManager.h"

#define PATH_TITLE_MENU "UIs/Menus/TitleMenu.png"
#define PATH_POINTER "UIs/Menus/TitleMenuPointer.png"
#define FONT "Font.ttf"

TitleMenu::TitleMenu()
{
	canvas = nullptr;
	pointer = nullptr;
	buttons = vector<Button*>();
}


void TitleMenu::Init()
{
	
	canvas = new Canvas("Title");

	#pragma region Title

	const Vector2f& _windowSize = Game::GetWindowSize();
	ShapeWidget* _image = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_TITLE_MENU));
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

	const vector<ButtonData>& _allData =
	{
		ButtonData(
			"START GAME",

			[&]() { 
				canvas->SetVisibilityStatus(false);
				Game::GetPlayer()->Init();
			}
			
			[&]() { canvas->SetVisibilityStatus(false);
					Game::GetPlayer()->SetVisibilityPlayerStats(true);
					Game::GetPlayer()->IsPlay(true);
					Game::GetCamera()->SetTarget(TARGET_PLAYER);
					 }

		),
		ButtonData(
			"   OPTIONS",
			[]() { cout << "OPTIONS" << endl; }
		),
		ButtonData(
			"ACHIVEMENTS",
			[]() { cout << "ACHIVEMENTS" << endl; }
		),
		ButtonData(
			"    EXTRAS",
			[]() { cout << "EXTRAS" << endl; }
		),
		ButtonData(
			" QUIT GAME",
			[]() { Game::Close(); }
		)
	};

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _gapY = _buttonSize.y * 5.0f / 100.0f;
	const float _gridPosX = _windowSize.x / 2.0f + _buttonSize.x * 5.0f / 100.0f;
	const float _gridPosY = _windowSize.y * 55.0f / 100.0f;

	for (int _index = 0; _index < 5; _index++)
	{
		const float _buttonPosY = _gridPosY + _buttonSize.y * _index + _gapY * _index;
		const Vector2f& _buttonPos = Vector2f(_gridPosX, _buttonPosY);
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

		const float _titlePosX = _buttonPos.x - _buttonSize.x * 40.0f / 100.0f;
		const float _titlePosY = _buttonPos.y - _buttonSize.y * 30.0f / 100.0f;
		Label* _title = new Label(TextData(_allData[_index].text, Vector2f(_titlePosX, _titlePosY), FONT, 24));
		_button->SetForeground(_title);
		canvas->AddWidget(_title);
	}

	pointer = new ShapeWidget(ShapeData(Vector2f(_gridPosX, _gridPosY), Vector2f(_buttonSize.x * 1.75f, _buttonSize.y * 2.0f), PATH_POINTER));
	canvas->AddWidget(pointer);
	
	#pragma endregion

	#pragma region Version

	const float _versionPosX = _windowSize.x * 90.0f / 100.0f;
	const float _versionPosY = _windowSize.y * 90.0f / 100.0f;
	Label* _version = new Label(TextData("v 1.0.0", Vector2f(_versionPosX, _versionPosY), FONT, 18));
	canvas->AddWidget(_version);

	#pragma endregion
}