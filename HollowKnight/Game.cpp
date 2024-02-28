#include "Game.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "ActorManager.h"
#include "HUD.h"
#include "Widget.h"

#include "Spawner.h"

#define PATH_PLAYER "Player.png"
#define FONT "Assets/Fonts/Font.ttf"

RenderWindow Game::window;
Player* Game::player;
Camera* Game::camera;

Game::Game()
{
	menu = new Menu();
	player = new Player("Player", ShapeData(Vector2f(0.0f, 0.0f), Vector2f(100.0f, 100.0f), ""));
	camera = new Camera(TARGET_WINDOW);

	//TODO move
	merchand = new Merchand();
	//npc = new NPC();
	pnj = new InteractableActor("Villageois" , ShapeData(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2f(100.0f, 100.0f), " ") , Vector2f(1000.0f , 1000.0f));
} 

Game::~Game()
{
	delete menu;
	//delete camera;
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

	//TODO move
	merchand->Init();
	new ActionMap("Merchand", {
		ActionData("ToggleShop", [&]() { merchand->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::Equal  })),
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
	window.clear();
	View _defaultView;
	CheckCameraState(_defaultView);

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

void Game::CheckCameraState(View& _newView)
{

	if (camera->GetTargetStat() == TARGET_PLAYER)
	{
		_newView = camera->FollowPlayer();
		window.setView(_newView);
	}

	else if (camera->GetTargetStat() == TARGET_WINDOW)
	{
		_newView = window.getDefaultView();
		window.setView(_newView);
	}

}

void Game::Close()
{
	window.close();
}