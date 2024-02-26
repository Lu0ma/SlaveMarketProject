#include "Player.h"

// System
#include "Macro.h"
#include "Kismet.h"

#include "Component.h"
#include "MovementComponent.h"

// Managers
#include "ActorManager.h"
#include "InputManager.h"
#include "Action.h"
#include "ActionMap.h"
#include "Timer.h"

// UIs
#include "Canvas.h"

#define PATH_ITEM "UIs/Item.png"

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	inventory = new Inventory();
	//new Canvas("PlayerStats", FloatRect());

	//TODO move
	//merchand = new Merchand();
}


void Player::SetupPlayerInput()
{
	new ActionMap("Storages", {
		ActionData("Inventory", [&]() { inventory->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::B })),
		ActionData("AddItem", [&]() { inventory->AddItem(1, PATH_ITEM); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("AddHealthMash", [&]() { inventory->UpdateMaskCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::A })),
	});
	new ActionMap("Diplay", { ActionData("Shop", [&]() { merchand->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::Tab })) });
	new ActionMap("Movement", {
		/*ActionData("Right" , this , &Player::Right , {Event::KeyPressed , Keyboard::D} , {Event::KeyPressed , Keyboard::Right}),
		ActionData("Left" , this , &Player::Left , {Event::KeyPressed , Keyboard::Q} , {Event::KeyPressed , Keyboard::Left}),
		ActionData("Up" , this , &Player::Up , {Event::KeyPressed , Keyboard::Z} , {Event::KeyPressed , Keyboard::Up})*/
	});
}

void Player::InitStats()
{
	//canvas = new Canvas("PlayerStats");
	//stats = new PlayerStats(_healthBar, _manaBar, _thirstBar, _hungerBar);
}


void Player::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);

}

void Player::Init()
{
	//InitStats();
	inventory->Init();
	SetupPlayerInput();
}