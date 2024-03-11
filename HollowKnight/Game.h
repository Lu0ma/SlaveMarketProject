#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "MainMenu.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"

using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

struct Brightness
{
	Shader* shader;
	float gamma;

	Brightness()
	{
		shader = new Shader();
		gamma = 1.0f;
	}

	void Init()
	{
		if (!shader->loadFromFile("Assets/Shaders/shader.frag", Shader::Fragment))
		{
			cerr << "Error => The shader cannot be loaded !" << endl;
			return;
		}
	}

	void UpdateBrightness(const float _factor)
	{
		gamma += gamma * _factor / 100.0f;
		gamma = gamma < 0.0f ? 0.0f : gamma;
		shader->setUniform("gamma", gamma);
	}
};

class Game
{
	static RenderWindow window;
	MainMenu* menu;
	static Map* map;
private:
	static Player* player;
	static Camera* camera;
	static Brightness* brightness;

public:
	static RenderWindow& GetWindow()
	{
		return window;
	}
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
	static Map* GetMap() 
	{
		return map;
	}
	static Brightness* GetBrightness()
	{
		return brightness;
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
	static void Close();

};