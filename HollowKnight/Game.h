#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayerInfo.h"
#include "Player.h"
#include "Camera.h"
using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
	RenderWindow window;
	PlayerInfo* playerInfo;

public:
	static Vector2f GetWindowSize()
	{
		return Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	Player* player;
	Camera* camera;

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
};