#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "Player.h"
#include "Camera.h"

using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game : public Singleton<Game>
{
	RenderWindow window;
	Player* player;
	Camera* camera;

public:
	Vector2f GetWindowSize() const
	{
		return Vector2f(window.getSize());
	}
	Player* GetPlayer() const
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
};