#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"

#include "Merchand.h"
#include "NPC.h"
#include "InteractableActor.h"

using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
	static RenderWindow window;
	Menu* menu;
	static Map* map;
	static Player* player;
	static Camera* camera;

	Merchand* merchand;
	InteractableActor* pnj;

public:
	static Vector2f GetWindowSize()
	{
		return Vector2f(window.getSize());
	}
	static Player* GetPlayer()
	{
		return player;
	}
	static Camera* GetCamera()
	{
		return camera;
	}

public:
	Game();
	~Game();

public:
	void Start();
	void Init();
	void Update();
	void UpdateWindow();
	void Stop();

public:
	void Launch();
	void CheckCameraState(View& _newView);
	static void Close();
};