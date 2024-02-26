#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
<<<<<<< Updated upstream
#include "PlayerInfo.h"

=======
#include "Camera.h"
>>>>>>> Stashed changes
using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
	RenderWindow window;
<<<<<<< Updated upstream
	PlayerInfo* playerInfo;

public:
	static Vector2f GetWindowSize()
	{
		return Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
=======
	Camera* camera;
>>>>>>> Stashed changes

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