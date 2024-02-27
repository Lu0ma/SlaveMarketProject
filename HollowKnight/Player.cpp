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

#define PATH_ITEM "UIs/Inventory/Item.png"
#define PATH_ITEM2 "test.png"

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	inventory = new Inventory();
	movement = new PlayerMovementComponent(this);
	components.push_back(movement);
	//TODO move
	//merchand = new Merchand();
}


void Player::SetupPlayerInput()
{
	new ActionMap("Storages", {
		ActionData("Inventory", [&]() { inventory->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::B })),
		ActionData("AddItem", [&]() { inventory->AddItem(1, {
			PATH_ITEM, "Item",
			"Voici une description correcte\nMais je cherche surtout quoi dire..\n on va faire avec..\n\nnan ??"});
		}, InputData({ActionType::KeyPressed, Keyboard::Q})),
		ActionData("AddItem2", [&]() { inventory->AddItem(1, {
			PATH_ITEM2, "Object",
			"Ceci est un texte\nEt ça, c'est un saut de ligne"});
		}, InputData({ActionType::KeyPressed, Keyboard::W})),
		ActionData("AddHealthMash", [&]() { inventory->UpdateMaskCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::A })),
		});
	new ActionMap("Diplay", { ActionData("Shop", [&]() { merchand->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::Tab }))});

	new ActionMap("Movement", {
		ActionData("Right" ,[this]() {movement->SetDirectionX(1.0f); cout << "droite" << endl;},InputData({Event::KeyPressed , Keyboard::D})),
		ActionData("Left" , [this]() {movement->SetDirectionX(-1.0f); cout << "gauche" << endl;},InputData({Event::KeyPressed , Keyboard::Left})),
		ActionData("Up" , [this]() {movement->Jump(); cout << "saut" << endl; },InputData({Event::KeyPressed , Keyboard::Up}))
		}
	);
	/*new ActionMap("Movement", {
		ActionData("Overworld_Left", [&]()
			{
				movement->SetDirectionX(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("Overworld_StopLeft", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),

		ActionData("Overworld_Right", [&]() { movement->SetDirectionX(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::D })),
		ActionData("Overworld_StopRight", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::D })),

		ActionData("Jump", [&]() { movement->Jump(); }, InputData({ ActionType::KeyPressed, Keyboard::Space }))
	});*/
}

void Player::InitStats()
{
	// canvas = new Canvas("PlayerStats");
	// stats = new PlayerStats(_healthBar, _manaBar, _thirstBar, _hungerBar);
}


void Player::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	// PlayerMovementComponent::Update(_deltaTime);
	// movement->Update(_deltaTime);

}

void Player::Init()
{
	//InitStats();
	inventory->Init();
	SetupPlayerInput();
}

void Player::Right()
{
 	movement->SetDirectionX(1.0f);
	cout << "Je vais a droite " << endl;
}

void Player::Left()
{
	movement->SetDirectionX(-1.0f);
	cout << "Je vais a gauche " << endl;
}

void Player::Up()
{
	movement->Jump();
	cout << "Je saute " << endl;
}
