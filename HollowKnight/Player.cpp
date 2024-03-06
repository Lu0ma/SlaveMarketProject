#include "Player.h"
#include "Game.h"

// Mobs
#include "Mob.h"
#include "DeathMob.h"

// System
#include "Macro.h"
#include "Kismet.h"

// Managers
#include "ActorManager.h"
#include "InputManager.h"
#include "Timer.h"

#define PATH_ITEM "UIs/Inventory/Item.png"
#define PATH_ITEM2 "test.png"
#define PATH_DEATHMOB "Animations/DeathMob.png"

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	//shape->setFillColor(Color::Red);

	inventory = new Inventory();
	charmsMenu = new CharmsMenu();

	animation = new PlayerAnimationComponent(this);
	components.push_back(animation);

	movement = new PlayerMovementComponent(this);
	components.push_back(movement);

	attack = new PlayerAttackComponent(this, 1);
	components.push_back(attack);
	
	interaction = new InteractionComponent(this);
	components.push_back(interaction);

	stats = new PlayerStat(this);
	components.push_back(stats);

	light = new CircleShape(55.0f);
	light->setFillColor(Color(255, 255, 255, 20)); 
	light->setOrigin(100.0f, 100.0f);
}


void Player::InitAnimations()
{
	animation->Init();
}

void Player::SetupPlayerInput()
{
	new ActionMap("Stats", {
		ActionData("AddMana", [&]() { stats->UseMana(10.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Space  })),
		ActionData("RemoveMana", [&]() { 
			stats->UseMana(-10.0f); 
			stats->UpdateLife(1); 
		}, InputData({ActionType::KeyPressed, Keyboard::Escape})),
		ActionData("StopMana", [&]() { stats->StopUsingMana(); }, InputData({ ActionType::KeyReleased, Keyboard::Escape  })),
		//ActionData("StopRemoveMana",[&]() { animation->GetCurrentAnimation()->RunAnimation(animation->GetAnimPlayer()[0]); }, InputData({ ActionType::KeyReleased, Keyboard::Escape })),
		//ActionData("AddLife", [&]() { stats->UpdateLife(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num9 })),
		ActionData("RemoveLife", [&]() { stats->UpdateLife(-1); }, InputData({ ActionType::KeyPressed, Keyboard::Num0 })),
		ActionData("AddLifeSlot", [&]() { stats->AddLife(); }, InputData({ ActionType::KeyPressed, Keyboard::O })),
		ActionData("AddGeos", [&]() { stats->AddGeos(12); }, InputData({ ActionType::KeyPressed, Keyboard::Num8 })),
	});
	            
	new ActionMap("Movements", {
		ActionData("Right", [&]() { movement->SetDirectionX(1.0f, "Right"); }, InputData({ActionType::KeyPressed, Keyboard::D})),
		ActionData("StopRight", [&]() { movement->SetDirectionX(0.0f, "StopRight"); }, InputData({ ActionType::KeyReleased, Keyboard::D })),
		ActionData("Left", [&]() { movement->SetDirectionX(-1.0f, "Left"); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("StopLeft", [&]() { movement->SetDirectionX(0.0f, "StopLeft"); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),
		ActionData("Jump", [&]() { movement->Jump(); }, InputData({ ActionType::KeyPressed, Keyboard::Space })),
		ActionData("Dash", [&]() { movement->Dash(); }, InputData({ ActionType::KeyPressed, Keyboard::LControl })),
		ActionData("Sit", [&]() { movement->SitDown(); }, InputData({ActionType::KeyPressed, Keyboard::Up })),
		ActionData("Stand", [&]() { movement->StandUp(); }, InputData({ActionType::KeyPressed, Keyboard::Down}))
	});

	new ActionMap("Attack", {
		ActionData("Slash", [&]() { attack->SpecialAttack(); }, InputData({ActionType::KeyPressed, Keyboard::R})),
		ActionData("StopSlash", [&]() { movement->SetDirectionX(0.0f, "Right"); }, InputData({ActionType::KeyReleased, Keyboard::R})),
	});

	new ActionMap("Inventory", {
		ActionData("ToggleInventory", [&]() {
			stats->Toggle();
			inventory->Toggle();
			interaction->StopInteract();
		}, InputData({ ActionType::KeyPressed, Keyboard::B })),
	});

	new ActionMap("CharmsMenu", {
		ActionData("ToogleCharmsMenu", [&]() { TryToOpenCharmsMenu(); }, InputData({ActionType::KeyPressed, Keyboard::P}))
	});

	new ActionMap("Interaction", {
		ActionData("TryToInteract", [&]() { interaction->TryToInteract(); }, InputData({ ActionType::KeyPressed, Keyboard::E  })),
	});
}

void Player::TryToOpenCharmsMenu()
{
	if (movement->IsStanding())
	{
		cout << "Impossible d'ouvrir l'inventaire des charms !" << endl;
		return;
	}

	charmsMenu->Toggle();
}


void Player::Init()
{
	movement->SetCanMove(true);
	stats->Init();
	inventory->Init();
	charmsMenu->Init();

	InitAnimations();
	SetupPlayerInput();
}