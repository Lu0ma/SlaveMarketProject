#include "MainMenu.h"
#include "Game.h"
#include "ActionMap.h"
#include "MusicManager.h"

#define PATH_MAIN_MENU "UIs/Menus/MainMenu/Background.png"

MainMenu::MainMenu() : Menu("MainMenu")
{
	titleMenu = new TitleMenu(this);
}


void MainMenu::OpenTitleMenu()
{
	if (!canvas->GetVisibilityStatus()) return;

	canvas->SetVisibilityStatus(false);
	titleMenu->Init();
}


void MainMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	ShapeWidget* _image = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_MAIN_MENU));
	canvas->AddWidget(_image);

	const float _mainMenuTextPosX = _windowSize.x * 0.80f;
	const float _mainMenuTextPosY = _windowSize.y * 0.75f;
	Label* _mainMenuText = new Label(TextData("Press space key to continue..", Vector2f(_mainMenuTextPosX, _mainMenuTextPosY), FONT, 26), AT_RIGHT);

	canvas->AddWidget(_mainMenuText);
	new ActionMap("MenuInputs", {
		ActionData("OpenTitleMenu", [&]() { 
			OpenTitleMenu();
			music->Stop();
		}, InputData({ ActionType::KeyPressed, Keyboard::Space }))
	});

	music = new MusicData("CityofTears", 0.0f);
}