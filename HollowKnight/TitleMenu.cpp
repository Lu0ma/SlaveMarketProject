#include "TitleMenu.h"
#include "Game.h"
#include "HUD.h"
#include "ActorManager.h"
#define SOUND_CONFIRM "Ui/ui_button_confirm"
#define PATH_TITLE_MENU "UIs/Menus/TitleMenu/Background.png"

TitleMenu::TitleMenu(Menu* _owner) : Menu("TitleMenu", _owner)
{
	canvas = new Canvas("Title");
	buttons = vector<Button*>();
	options = new OptionsMenu(this);
	achievement = new AchievementsMenu(this);
	quitGame = new QuitGameMenu(this);
}


void TitleMenu::Init()
{
	Menu::Init();

	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	#pragma region Title

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

	const vector<ButtonData>& _allData = {
		ButtonData("Start Game", [&]() { 
			Game::GetPlayer()->Init();
			SetStatus(false);
			new SoundData(SOUND_CONFIRM, 100, false);
		}),
		ButtonData("Options", [&]() {
			options->SetStatus(true);
			SetStatus(false);
			new SoundData(SOUND_CONFIRM, 100, false);
		}),
		ButtonData("Achievements", [&]() {
			achievement->SetStatus(true);
			SetStatus(false);
			new SoundData(SOUND_CONFIRM, 100, false);
		}),
		ButtonData("Extras", [&]() {
			cout << "EXTRAS" << endl;
			new SoundData(SOUND_CONFIRM, 100, false);
			//TODO easter
		}),
		ButtonData("Quit Game", [&]() {
			quitGame->SetStatus(true);
			SetStatus(false);
		})
	};

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _gapY = _buttonSize.y * 5.0f / 100.0f;
	const float _gridPosX = _halfWindowX + _buttonSize.x * 5.0f / 100.0f;
	const float _gridPosY = _windowSize.y * 55.0f / 100.0f;

	const int _buttonsCount = (int)_allData.size();
	for (int _index = 0; _index < 5; _index++)
	{
		const float _buttonPosY = _gridPosY + _buttonSize.y * _index + _gapY * _index;
		const Vector2f& _buttonPos = Vector2f(_gridPosX, _buttonPosY);
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

		Label* _title = new Label(TextData(_allData[_index].text, Vector2f(_halfWindowX, _buttonPos.y), FONT, 24));
		_button->SetForeground(_title);
		canvas->AddWidget(_title);
	}

	Menu::Init();
	MovePointers(buttons.front());
	
	#pragma endregion

	#pragma region Version

	const float _versionPosX = _windowSize.x * 90.0f / 100.0f;
	const float _versionPosY = _windowSize.y * 90.0f / 100.0f;
	Label* _version = new Label(TextData("v 1.2.0", Vector2f(_versionPosX, _versionPosY), FONT, 18));
	canvas->AddWidget(_version);

	#pragma endregion
}