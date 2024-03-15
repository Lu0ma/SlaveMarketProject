#include "Game.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "ActorManager.h"
#include "HUD.h"
#include "Widget.h"
#include "Spawner.h"

#define PATH_PLAYER "Animations/knighModif.png"

#include "HuskBully.h"
#include "Boofly.h"
#include "Belfly.h"
#include "FalseKnight.h"

RenderWindow Game::window;
Map* Game::map;
Player* Game::player;
Camera* Game::camera;
Brightness* Game::brightness;

#include "TriggerBox.h"

#define PATH_BOOFLY "Animations/Boofly.png"
#define PATH_BELFLY "Animations/BelflyModif.png"
#define PATH_HUSK_BULLY "Animations/HuskBully.png"
#define PATH_DEATHMOB "Animations/DeathMob.png"
#define PATH_FALSE_KNIGHT "Animations/FalseKnight.png"

Game::Game()
{
	menu = new MainMenu();
	player = new Player("Player", ShapeData(Vector2f(100.0f, -2000.0f), Vector2f(75.0f, 75.0f), PATH_PLAYER));
	map = new Map();
	camera = new Camera();
	brightness = new Brightness();
} 

Game::~Game()
{
	delete map;
	delete brightness;
}


void Game::Start()
{
	window.create(VideoMode(1920, 1080), "HollowKnight", Style::Fullscreen);

	TimerManager::GetInstance().SetRenderCallback(bind(&Game::UpdateWindow, this));
	new Timer([&]() { Init(); }, seconds(1.0f), true, false);
}

void Game::Init()
{
	menu->Init();
	map->Init();
	camera->Init();
	brightness->Init();

	/*TriggerBox* _box = new TriggerBox(ShapeData(Vector2f(100.0f, 0.0f), Vector2f(200.0f, 200.0f), ""), [&]() {
		cout << "coucou" << endl;
	});

	_box->GetComponent<CollisionComponent>()->GetBoxCollision()->GetDrawable()->setOutlineThickness(-5.0f);
	_box->GetComponent<CollisionComponent>()->GetBoxCollision()->GetDrawable()->setFillColor(Color::Red);*/

	Vector2f _sizeBoofly = Vector2f(150.0f, 180.0f);
	Vector2f _sizeBelfly = Vector2f(50.0f, 50.0f);
	Vector2f _sizeHuskBully = Vector2f(75.0f, 75.0f);
	Vector2f _sizeFalseKnight = Vector2f(700.0f, 500.0f);

	ShapeData _dataBoofly = ShapeData(Vector2f(200.0f, -350.0f), _sizeBoofly, PATH_BOOFLY, IntRect(0, 17, 315, 345));
	Boofly* _boofly = new Boofly(_dataBoofly);
	_boofly->Init();

	ShapeData _dataHuskBully = ShapeData(Vector2f(300.0f, -150.0f), _sizeHuskBully, PATH_HUSK_BULLY, IntRect(5, 21, 105, 135));
	HuskBully* _huskBully = new HuskBully(_dataHuskBully);
	_huskBully->Init();

	//ShapeData _data = ShapeData(_positionFalseKnight, _sizeFalseKnight, PATH_FALSE_KNIGHT);
	//FalseKnight* _falseKnight = new FalseKnight(_data);
	//_falseKnight->Init();
}

void Game::Update()
{
	while (window.isOpen())
	{
		TimerManager::GetInstance().Update();
		if (!InputManager::GetInstance().Update(window)) break;
		player->GetLight()->setPosition(player->GetShapePosition().x + 50.0f, player->GetShapePosition().y + 50.0f);
		ActorManager::GetInstance().Update();
	}
}

void Game::UpdateWindow()
{
	window.clear();

	const float _deltaTime = TimerManager::GetInstance().GetDeltaTime();
	camera->Update(_deltaTime);

	window.setView(camera->GetView());
	//DrawWorldUIs();

	DrawMap();
	DrawActors();
	//window.draw(*player->GetLight());

	DrawUIs();
	window.display();
}

#pragma region Draws

void Game::DrawWorldUIs()
{
	for (Canvas* _canvas : HUD::GetInstance().GetAllValues())
	{
		for (Widget* _widget : _canvas->GetWorldWidgets())
		{
			if (!_widget->IsVisible()) continue;
			const RenderStates& _render = _widget->CanApplyShader() ? brightness->shader : RenderStates::Default;
			window.draw(*_widget->GetDrawable(), _render);
		}
	}
}

void Game::DrawMap()
{
	for (ShapeObject* _drawable : map->GetAllDrawables())
	{
		window.draw(*_drawable->GetDrawable(), brightness->shader);
	}
}

void Game::DrawActors()
{
	for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
	{
		window.draw(*_actor->GetDrawable(), brightness->shader);
	}
}

void Game::DrawUIs()
{
	View _view = window.getDefaultView();
	for (Canvas* _canvas : HUD::GetInstance().GetAllValues())
	{
		if (!_canvas->IsVisible()) continue;
		_view.setViewport(_canvas->GetRect());
		window.setView(_view);

		for (Widget* _widget : _canvas->GetUiWidgets())
		{
			if (!_widget->IsVisible()) continue;
			const RenderStates& _render = _widget->CanApplyShader() ? brightness->shader : RenderStates::Default;
			window.draw(*_widget->GetDrawable(), _render);
		}
	}
}

#pragma endregion

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