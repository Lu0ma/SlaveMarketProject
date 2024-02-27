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

#include "Game.h"

#define PATH_ITEM "UIs/Inventory/Item.png"
#define PATH_ITEM2 "test.png"

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
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

	ActionData("AddHealthMask", [&]() { inventory->UpdateMaskCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num1 })),
		ActionData("AddVessel", [&]() { inventory->UpdateVesselCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num2 })),
		ActionData("UpgradeMirror", [&]() { inventory->UpdateMirrorLevel(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num3 })),
		ActionData("ToggleVengeful", [&]() { inventory->SetVengefulStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num4 })),
		ActionData("ToggleSlam", [&]() { inventory->SetSlamStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num5 })),
		ActionData("ToggleShriek", [&]() { inventory->SetShriekStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num6 })),
		ActionData("UpgradeSword", [&]() { inventory->UpdateSwordLevel(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num7 })),

	new ActionMap("Diplay", { ActionData("Shop", [&]() { merchand->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::Tab })) });
	
	new ActionMap("Movement", {
		ActionData("Left", [&]()
			{
			 	movement->SetDirectionX(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("StopLeft", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),

		ActionData("Right", [&]() { movement->SetDirectionX(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::D })),
		ActionData("StopRight", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::D })),

		ActionData("Jump", [&]() { movement->Jump(); }, InputData({ ActionType::KeyPressed, Keyboard::Space }))
	});
}

void Player::InitStats()
{
	// canvas = new Canvas("PlayerStats");
	// stats = new PlayerStats(_healthBar, _manaBar, _thirstBar, _hungerBar);

	canvas = new Canvas("PlayerInfo", FloatRect(0, 0, 1, 1));

	const Vector2f& _windowSize = Game::GetWindowSize();
	healthBar = new Label(TextData(to_string(stats->health) + "/" + to_string(stats->maxHealth), Vector2f(_windowSize.x / 100.0f * 10.0f, _windowSize.y / 100.0f * 1.0f), "TrajanProRegular.ttf"));
	manaBar = new Label(TextData(to_string(stats->mana) + "/" + to_string(stats->maxMana), Vector2f(_windowSize.x / 100.0f * 10.0f, _windowSize.y / 100.0f * 5.0f), "TrajanProRegular.ttf"));
	geosCountText = new Label(TextData(to_string(stats->geosCount), Vector2f(_windowSize.x / 100.0f * 10.0f, _windowSize.y / 100.0f * 10.0f), "TrajanProRegular.ttf"));

	canvas->AddWidget(healthBar);
	canvas->AddWidget(manaBar);
	canvas->AddWidget(geosCountText);


	//stats = new PlayerStats(stats->health, stats->health + 1, stats->mana, stats->maxMana + 1, stats->geosCount + 1);
	//SetStat(stats->health);
}


void Player::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	// PlayerMovementComponent::Update(_deltaTime);
	// movement->Update(_deltaTime);
	if (!healthBar ||!manaBar||!geosCountText)
	{
		return;
	}
	healthBar->SetString(to_string(stats->health) + "/" + to_string(stats->maxHealth));
	manaBar->SetString(to_string(stats->mana) + "/" + to_string(stats->maxMana));
	geosCountText->SetString(to_string(stats->geosCount));
	canvas->SetVisibilityStatus(stats->isVisible);

	stats->Healing();
}

void Player::Init()
{
	InitStats();
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
