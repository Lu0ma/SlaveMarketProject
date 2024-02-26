#include "Player.h"
#include "ActionMap.h"

Player::Player(const string& _name, const ShapeData& _data)
			 : Actor(_name, _data)
{
	inventory = new Inventory();
}

void Player::Init()
{
	inventory->Init();

	SetupPlayerInputs();
}

void Player::SetupPlayerInputs()
{
	new ActionMap("Storages", {
		ActionData("Inventory", [&]() { inventory->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::B })),
		ActionData("AddHealthMash", [&]() { inventory->UpdateMaskCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::A })),
	});
}