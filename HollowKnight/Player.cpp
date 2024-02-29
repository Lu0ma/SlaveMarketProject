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
#include "InteractableActor.h"

#define PATH_ITEM "UIs/Inventory/Item.png"
#define PATH_ITEM2 "test.png"
#define PATH_DEATHMOB "Animations/DeathMob.png"

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	shape->setFillColor(Color::Red);

	stats = new PlayerStat();
	attack = new PlayerAttackComponent(this,1);
	animation = new PlayerAnimationComponent(this);
	inventory = new Inventory();
	charmsMenu = new CharmsMenu();
	movement = new PlayerMovementComponent(this);

	components.push_back(movement);
	components.push_back(animation);

	bench = new Bench();
	bench->Init();
	isStanding = true;
}


void Player::InitAnimations()
{
	animation->Init();
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
		}, InputData({ActionType::KeyPressed, Keyboard::A })),
		ActionData("AddItem2", [&]() { inventory->AddItem(1, {
			PATH_ITEM2, "Object",
			"Ceci est un texte\nEt ça, c'est un saut de ligne"}); 
		}, InputData({ActionType::KeyPressed, Keyboard::W })),
		ActionData("AddHealthMask", [&]() { inventory->UpdateMaskCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num1 })),
		ActionData("AddVessel", [&]() { inventory->UpdateVesselCount(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num2 })),
		ActionData("UpgradeMirror", [&]() { inventory->UpdateMirrorLevel(1); }, InputData({ ActionType::KeyPressed, Keyboard::Num3 })),
		ActionData("ToggleVengeful", [&]() { inventory->SetVengefulStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num4 })),
		ActionData("ToggleSlam", [&]() { inventory->SetSlamStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num5 })),
		ActionData("ToggleShriek", [&]() { inventory->SetShriekStatus(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num6 })),
		ActionData("UpgradeSword", [&]() { inventory->UpdateSwordLevel(true); }, InputData({ ActionType::KeyPressed, Keyboard::Num7 })),
	});

	new ActionMap("Movements", {
		ActionData("Right", [&]() { 
			movement->SetDirectionX(1.0f);
			animation->GetAnimation()->RunAnimation(animation->GetAnimPlayer()[2]);
		}, InputData({ ActionType::KeyPressed, Keyboard::D })),
		ActionData("StopRight", [&]() {
			movement->SetDirectionX(0.0f);
			animation->GetAnimation()->RunAnimation(animation->GetAnimPlayer()[0]);
		}, InputData({ ActionType::KeyReleased, Keyboard::D })),
		ActionData("Left", [&]() {
			movement->SetDirectionX(-1.0f);
			animation->GetAnimation()->RunAnimation(animation->GetAnimPlayer()[3]);
		}, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("StopLeft", [&]() {
			movement->SetDirectionX(0.0f);
			animation->GetAnimation()->RunAnimation(animation->GetAnimPlayer()[7]);
		}, InputData({ ActionType::KeyReleased, Keyboard::Q })),
		ActionData("Jump", [&]() {
			movement->Jump();
			animation->GetAnimation()->RunAnimation(animation->GetAnimPlayer()[6]);
		}, InputData({ ActionType::KeyReleased, Keyboard::Space })),
		ActionData("Dash", [&]() {
			movement->Dash();
			animation->GetAnimation()->RunAnimation(animation->GetAnimPlayer()[4]);
			}, InputData({ ActionType::KeyReleased, Keyboard::LControl })),
		ActionData("Sit", [&]() {
			if (GetDrawable()->getGlobalBounds().contains(bench->GetShapePosition()) && isStanding)
			{
				GetDrawable()->setPosition(GetShapePosition().x, GetShapePosition().y - 15.0f);
				isStanding = false;
			}
			else
			{
				cout << "impossible de s'assoire" << endl;
			}
		}, InputData({ActionType::KeyPressed, Keyboard::Up })),
		ActionData("Stand", [&]() {
			if (!isStanding)
			{
				GetDrawable()->setPosition(GetShapePosition().x, GetShapePosition().y + 15.0f);
				isStanding = true;
			}
			else
			{
				cout << "impossible de ce levé" << endl;
			}
		}, InputData({ActionType::KeyPressed, Keyboard::Down}))
	});

	new ActionMap("Attack", {
		ActionData("Slash", [&]() {
			attack->SpecialAttack();
			animation->GetAnimation()->RunAnimation(animation->GetAnimPlayer()[1]);
			cout << "Slash" << endl;
		}, InputData({ActionType::KeyPressed, Keyboard::R})),
		ActionData("StopSlash", [&]() {
			movement->SetDirectionX(0.0f);
			animation->GetAnimation()->RunAnimation(animation->GetAnimPlayer()[0]);
		}, InputData({ActionType::KeyReleased, Keyboard::R})),
	});

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

	InitAnimations();
	SetupPlayerInput();
}


void Player::Update()// TODO
{
	//else if (stats->GetCurrentLife() == 0)
	//{
	//	cout << "Tu es mort" << endl;
	//	//creer un mob qui va etre a la position de la mort du joueur
	//	ShapeData _data = ShapeData(GetShapePosition(), Vector2f(100.0f, 100.0f), PATH_DEATHMOB, IntRect(0, 18, 316, 346));
	//	DeathMob* _death = new DeathMob(_data);

	//	//Changement de l'anim du joueur pdt 3sec avant de respawn
	//	function<void()> _callback = [&]() {

	//		this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[5]);
	//	};

	//	deathTimer = new Timer(_callback, seconds(3.0f), true, false);

	//	//set la position au debut du niveau
	//	//this->GetDrawable()->setPosition(//Checkpoint); 
	//	stats->SetCurrentLife(stats->GetMaxLife()); // Lui redonner full vie
	//}
}