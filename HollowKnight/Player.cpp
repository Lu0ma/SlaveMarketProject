#include "Player.h"
#include "Game.h"

// System
#include "Macro.h"
#include "Kismet.h"

// Managers
#include "ActorManager.h"
#include "InputManager.h"
#include "Action.h"
#include "ActionMap.h"
#include "Timer.h"
#include "InteractableActor.h"
#define PATH_ITEM "UIs/Inventory/Item.png"
#define PATH_ITEM2 "test.png"

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	shape->setFillColor(Color::Red);

	stats = new PlayerStat();
	inventory = new Inventory();
	movement = new PlayerMovementComponent(this);
	components.push_back(movement);
}


void Player::SetupPlayerInput()
{
	new ActionMap("Stats", {
		ActionData("AddMana", [&]() { stats->UseMana(10.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Space  })),
		ActionData("RemoveMana", [&]() { stats->UseMana(-10.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Escape })),
		ActionData("AddLife", [&]() { stats->UpdateLife(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num9 })),
		ActionData("RemoveLife", [&]() { stats->UpdateLife(-1); }, InputData({ ActionType::KeyPressed, Keyboard::Num0 })),
		ActionData("AddLifeSlot", [&]() { stats->AddLife(); }, InputData({ ActionType::KeyPressed, Keyboard::O })),
		ActionData("AddGeos", [&]() { stats->AddGeos(12); }, InputData({ ActionType::KeyPressed, Keyboard::Num8 })),
	});

	new ActionMap("Inventory", {
		ActionData("ToggleInventory", [&]() { 
			stats->Toggle();
			inventory->Toggle();
		}, InputData({ ActionType::KeyPressed, Keyboard::B })),
		ActionData("AddHealthMask", [&]() { inventory->UpdateMaskCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num1 })),
		ActionData("AddVessel", [&]() { inventory->UpdateVesselCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num2 })),
		ActionData("UpgradeMirror", [&]() { inventory->UpdateMirrorLevel(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num3 })),
		ActionData("ToggleVengeful", [&]() { inventory->SetVengefulStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num4 })),
		ActionData("ToggleSlam", [&]() { inventory->SetSlamStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num5 })),
		ActionData("ToggleShriek", [&]() { inventory->SetShriekStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num6 })),
		ActionData("UpgradeSword", [&]() { inventory->UpdateSwordLevel(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num7 })),
	});

	new ActionMap("Storages", {
		ActionData("AddItem", [&]() { inventory->AddItem(1, {
			PATH_ITEM, "Item",
			"Voici une description correcte\nMais je cherche surtout quoi dire..\n on va faire avec..\n\nnan ??"}); 
		}, InputData({ActionType::KeyPressed, Keyboard::Q})),
		ActionData("AddItem2", [&]() { inventory->AddItem(1, {
			PATH_ITEM2, "Object",
			"Ceci est un texte\nEt ça, c'est un saut de ligne"}); 
		}, InputData({ActionType::KeyPressed, Keyboard::W})),
		ActionData("AddHealthMask", [&]() { inventory->UpdateMaskCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num1 })),
		ActionData("AddHealthMash", [&]() { inventory->UpdateMaskCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::A })),
	});

	new ActionMap("Movements", {
		ActionData("Right", [&]() { movement->SetDirectionX(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::D })),
		ActionData("StopRight", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::D })),
		ActionData("Left", [&]() { movement->SetDirectionX(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("StopLeft", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),
		ActionData("Jump", [&]() { movement->Jump(); }, InputData({ ActionType::KeyReleased, Keyboard::Space })),
		ActionData("Dash", [&]() { movement->Dash(); }, InputData({ ActionType::KeyReleased, Keyboard::LControl })),
	});

	new ActionMap("Interact With a PNJ", {

		ActionData("Talk " , [&]() {Game::GetPnj()->Verify();}, InputData({ActionType::KeyPressed , Keyboard::E})),
		});
}


void Player::Init()
{
	stats->Init();
	inventory->Init();
	SetupPlayerInput();
}