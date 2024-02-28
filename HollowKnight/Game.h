#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Player.h"
#include "Camera.h"
#include "Singleton.h"
#include "NPC.h"
using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
<<<<<<< HEAD
	static RenderWindow window;
	Menu* menu;
	static Player* player;
	Camera* camera;
	NPC* npc;
public:
	static Vector2f GetWindowSize()
	{
		return Vector2f(window.getSize());
	}
	static Player* GetPlayer()
	{
		return player;
	}
=======
	RenderWindow window;
	Spawner spawner;
>>>>>>> Olivier

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
	static void Close();
};