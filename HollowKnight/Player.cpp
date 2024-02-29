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

#define PATH_ITEM "UIs/Inventory/Item.png"
#define PATH_ITEM2 "test.png"

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	shape->setFillColor(Color::Red);

	stats = new PlayerStat();
	inventory = new Inventory();
	movement = new PlayerMovementComponent(this);
	components.push_back(movement);
	//TODO move
	//merchand = new Merchand();

	canvas = nullptr;
	healthBar = nullptr;
	manaBar = nullptr;
	geosCountText = nullptr;
	stats = new PlayerStat(10, 10, 20, 20, 0);

	bench = new Bench();
	charmsMenu = new CharmsMenu();

	isStanding = true;

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
	};

	new ActionMap("Movements", {
		ActionData("Right", [&]() { movement->SetDirectionX(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::D })),
		ActionData("StopRight", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::D })),
		ActionData("Left", [&]() { movement->SetDirectionX(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("StopLeft", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),
		ActionData("Jump", [&]() { movement->Jump(); }, InputData({ ActionType::KeyReleased, Keyboard::Space })),
		ActionData("Dash", [&]() { movement->Dash(); }, InputData({ ActionType::KeyReleased, Keyboard::LControl })),
		ActionData("Sit", [&]() {
			if (GetDrawable()->getGlobalBounds().contains(bench->GetShape()->getPosition()) && isStanding)
			{
				GetShape()->setPosition(GetShape()->getPosition().x, GetShape()->getPosition().y - 15.0f);
				isStanding = false;
			}
			else
			{
				cout << "impossible de s'assoire" << endl;
			}
		}, InputData({ActionType::KeyPressed, Keyboard::Up})) });
		ActionData("Stand", [&]() {
			if (!isStanding)
			{
				GetShape()->setPosition(GetShape()->getPosition().x, GetShape()->getPosition().y + 15.0f);
				isStanding = true;
			}
			else
			{
				cout << "impossible de ce levé" << endl;
			}
		}, InputData({ActionType::KeyPressed, Keyboard::Down}))
	});


	new ActionMap("Display", { ActionData("Shop", [&]() { merchand->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::Tab })) });

	new ActionMap("Open Menu", {
		ActionData("Menu", [&]() {
			if (!isStanding)
			{
				charmsMenu->Toggle();
			}
			else
			{
				cout << "impossible d'ouvrir l'inventaire des charms" << endl;
			}
		}, InputData({ActionType::KeyPressed, Keyboard::P}))
	});

}


void Player::Init()
{
	stats->Init();
	inventory->Init();
	charmsMenu->Init();
	SetupPlayerInput();
}