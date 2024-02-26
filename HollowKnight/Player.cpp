#include "Player.h"

Player::Player()
{
	merchand = new Merchand();
	InitInputs();
}

void Player::InitInputs()
{
	new ActionMap("Diplay", { ActionData("Shop", [&]() { merchand->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::Tab })) });
}
