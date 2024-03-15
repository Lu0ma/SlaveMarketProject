#include "CreditsMenu.h"
#include "Game.h"
#include "HUD.h"

CreditsMenu::CreditsMenu(Menu* _owner) : Menu("Credits", _owner)
{

}

void CreditsMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

#pragma region Background

	ShapeWidget* _background = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);

#pragma endregion

#pragma region Title

	const float _titlePosY = _windowSize.y * 0.1f;
	Label* _title = new Label(TextData("CREDITS", Vector2f(_halfWindowX, _titlePosY), FONT, 36));
	canvas->AddWidget(_title);

	const float _titleBarPosY = _titlePosY + 75.0f;
	const Vector2f& _titleBarSize = Vector2f(_windowSize.x * 0.4f, 50.0f);
	ShapeWidget* _titleBar = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _titleBarPosY), _titleBarSize, PATH_TITLE_ICON));
	canvas->AddWidget(_titleBar);

#pragma endregion

#pragma region Back

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _buttonPosY = _windowSize.y * 0.9f;
	const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);

	backButton = new Button(ShapeData(_buttonPos, _buttonSize, ""));
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

	Label* _buttonText = new Label(TextData("BACK", _buttonPos, FONT, 20));
	backButton->SetForeground(_buttonText);
	canvas->AddWidget(_buttonText);

	Menu::Init();

#pragma endregion

#pragma region CreditsText

	vector<string> _allData = {
		"Lead : Romain",
		"Directeur executif : Thomas",
		"Responsable Son et Camera : Josua",
		"Ingénieur Animation : Raphaël",
		"Map Constructeur : Julio",
		"Responsable IA (zarma) : Olivier",
		"Democrate des collisions : Nino celui qu'on apprécie pas trop",
		"Aide aux sons : Greg",
		"Gestionnaire des UIs : Nicolas",
		"Music : Christopher Larkin (pas les droits mais takpt)"
	};

	const Vector2f& _textSize = Vector2f(200.0f, 50.0f);
	const float _gapY = _textSize.y * 15.0f / 100.0f;
	const float _gridPosY = _titleBarPosY + 75.0f;

	const int _dataCount = (int)_allData.size();
	for (int _index = 0; _index < _dataCount; _index++)
	{
		float _textPosY = _gridPosY + _textSize.y * _index + _gapY * _index;
		_textPosY += _index == _dataCount - 1 ? _windowSize.y * 0.1f : 0.0f;
		const Vector2f& _textPos = Vector2f(_halfWindowX, _textPosY);
		

		Label* _title = new Label(TextData(_allData[_index], _textPos, FONT, 20));

		canvas->AddWidget(_title);
	}

#pragma endregion

}
