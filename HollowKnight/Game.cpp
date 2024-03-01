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
	player = new Player("Player", ShapeData(Vector2f(0.0f, 2.5f), Vector2f(100.0f, 100.0f), PATH_PLAYER));
	camera = new Camera(TARGET_WINDOW);
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
	map->Init();

	//TODO move
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
	//CheckCameraState(_defaultView);

	for (ShapeObject* _drawable : map->GetAllDrawables())
	{
		window.draw(*_drawable->GetDrawable());
	}

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
	cout << "A bientôt !" << endl;
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