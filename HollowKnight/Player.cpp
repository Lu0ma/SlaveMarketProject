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
		ActionData("AddHealthMask", [&]() { inventory->UpdateMaskCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num1 })),
		ActionData("AddVessel", [&]() { inventory->UpdateVesselCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num2 })),
		ActionData("UpgradeMirror", [&]() { inventory->UpdateMirrorLevel(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num3 })),
		ActionData("ToggleVengeful", [&]() { inventory->SetVengefulStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num4 })),
		ActionData("ToggleSlam", [&]() { inventory->SetSlamStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num5 })),
		ActionData("ToggleShriek", [&]() { inventory->SetShriekStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num6 })),
		ActionData("UpgradeSword", [&]() { inventory->UpdateSwordLevel(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num7 })),
	});
	new ActionMap("Diplay", { ActionData("Shop", [&]() { merchand->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::Tab })) });
	new ActionMap("Movement", {
		/*ActionData("Right" , this , &Player::Right , {Event::KeyPressed , Keyboard::D} , {Event::KeyPressed , Keyboard::Right}),
		ActionData("Left" , this , &Player::Left , {Event::KeyPressed , Keyboard::Q} , {Event::KeyPressed , Keyboard::Left}),
		ActionData("Up" , this , &Player::Up , {Event::KeyPressed , Keyboard::Z} , {Event::KeyPressed , Keyboard::Up})*/
		}
	);
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