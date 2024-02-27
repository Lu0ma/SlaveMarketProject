#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Player.h"
#include "Camera.h"

using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
	static RenderWindow window;
	Menu* menu;
	static Player* player;
	Camera* camera;

public:
	static Vector2f GetWindowSize()
	{
		return Vector2f(window.getSize());
	}
	static Player* GetPlayer()
	{
		return player;
	}

public:
	Game();
	~Game();

private:
	void Start();
	void Init();
	void Update();
	void UpdateWindow();
	void Stop();

public:
	void Launch();
	static void Close();
};