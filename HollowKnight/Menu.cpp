#include "Menu.h"
#include "ShapeWidget.h"
#include "Game.h"
#include "ActionMap.h"
#include "MusicManager.h"

#define PATH_MAIN_MENU "UIs/Menus/MainMenu.png"
#define FONT "Font.ttf"
#define MUSIC "CityofTears.mp3"

Menu::Menu()
{
	mainMenu = nullptr;
	titleMenu = new TitleMenu();
}

void Menu::OpenTitleMenu()
{
	if (!mainMenu->GetVisibilityStatus()) return;
	mainMenu->SetVisibilityStatus(false);
	titleMenu->Init();
}


void Menu::Init()
{
	mainMenu = new Canvas("MainMenu");

	const Vector2f& _windowSize = Game::GetWindowSize();
	ShapeWidget* _image = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_MAIN_MENU));
	// Camera::GetTargetStat()
	mainMenu->AddWidget(_image);

	const float _mainMenuTextPosX = _windowSize.x / 2.0f;
	const float _mainMenuTextPosY = _windowSize.y * 70.0f / 100.0f;
	Label* _mainMenuText = new Label(TextData("Press space key to continue..",
									Vector2f(_mainMenuTextPosX, _mainMenuTextPosY),
									FONT, 26));
	mainMenu->AddWidget(_mainMenuText);
	new ActionMap("MenuInputs", { 
		ActionData("OpenTitleMenu", [&]() { OpenTitleMenu(); }, InputData({ ActionType::KeyPressed, Keyboard::Space }))
	});

	MusicManager::GetInstance().Play(MUSIC);
}