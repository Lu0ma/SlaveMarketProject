#pragma once
#include "NPC.h"
#include "Canvas.h"
#include "Button.h"

class Merchand : public NPC
{
	//vector<Charms*> charms;
	Canvas* canvas;
	Vector2f cellSize;

public:
	Merchand();

public:
	void Toggle();
	void OpenShop();
	void BuyItem();
};

