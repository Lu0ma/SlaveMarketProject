#include "Game.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "ActorManager.h"
#include "HUD.h"
#include "Widget.h"

#include "Spawner.h"

//#define PATH_PLAYER "Player.png"
#define FONT "Assets/Fonts/Font.ttf"
#define PATH_PLAYER "Animations/knighModif.png"

RenderWindow Game::window;
Map* Game::map;
Player* Game::player;
Camera* Game::camera;

Game::Game()
{
	menu = new Menu();
	map = new Map();
	player = new Player("Player", ShapeData(Vector2f(0.0f, 0.0f), Vector2f(100.0f, 100.0f), PATH_PLAYER));
	camera = new Camera(TARGET_WINDOW);
	const vector<string>& _merchandTexts = { "Bonjour je suis un marchand" };
	merchand = new Merchand(_merchandTexts);
	pnj = new InteractableActor("Villageois", ShapeData(Vector2f(100.0f, 0.0f), Vector2f(100.0f, 100.0f), " "));
} 

Game::~Game()
{
	delete menu;
	delete camera;
}


void Game::Start()
{
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "HollowKnight");
	TimerManager::GetInstance().SetRenderCallback(bind(&Game::UpdateWindow, this));
	new Timer(this, &Game::Init, seconds(1.0f), true, false);
	
}

void Game::Init()
{
	menu->Init();
	//map->Init();
	//TODO move
	merchand->Init();

	pnj->Init();

	new ActionMap("Merchand", {
		ActionData("ToggleShop", [&]() { merchand->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::Equal  })),
	});

	new ActionMap("Interact With a PNJ", {
		ActionData("Talk ", [&]() {
			pnj->SetIsPlay(true);
			cout << "Welcome to shrek City " << endl;
		}, InputData({ActionType::KeyPressed , Keyboard::E})),
	});

	Spawner* _spawner = new Spawner();
	_spawner->Spawn();

}

void Game::Update()
{
	while (window.isOpen())
	{
		TimerManager::GetInstance().Update();
		if (!InputManager::GetInstance().Update(window)) break;
		ActorManager::GetInstance().Update();
	}
}

void Game::UpdateWindow()
{
	window.clear(); // Color(127, 127, 127, 0) gris
	View _defaultView;
	camera->CheckCameraState(_defaultView);

	for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
	{
		window.draw(*_actor->GetDrawable());
	}
	
	// UI
	View _view = window.getDefaultView();
	for (Canvas* _canvas : HUD::GetInstance().GetAllValues())
	{
  		if (!_canvas->IsVisible()) continue;
		_view.setViewport(_canvas->GetRect());
		window.setView(_view);

		for (Widget* _widget : _canvas->GetWidgets()) 
		{
			if (!_widget->IsVisible()) continue;
			window.draw(*_widget->GetDrawable());
		}
	}
	window.display();
}

void Game::Stop()
{
	cout << "A bient�t !" << endl;
}


void Game::Launch()
{
	Start();
	Update();
	Stop();
}

void Game::Close()
{
	window.close();
}