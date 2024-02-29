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

#include"DeathMob.h"

#define PATH_ITEM "UIs/Inventory/Item.png"
#define PATH_ITEM2 "test.png"
#define PATH_DEATHMOB "Animations/DeathMob.png"


Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	shape->setFillColor(Color::Magenta);

	stats = new PlayerStat();
	inventory = new Inventory();
	movement = new PlayerMovementComponent(this);
	components.push_back(movement);

	const Vector2f& _size = Vector2f(80.0f, 80.0f);
	const ReadDirection& _readDirection = READ_RIGHT;
	const bool _toRepeat = true;
	const int _count = 8;// a changer
	const int _countAttack = 7;
	const float _speed = 0.1f;

	animation = new AnimationComponent(this, {
	AnimationData("NONERIGHT",Vector2f(0.0f, 0.0f), _size, _readDirection,  _toRepeat, 1, _speed),
	AnimationData("Special",Vector2f(0.0f, 320.0f), _size, _readDirection , _toRepeat, _countAttack, _speed),
	AnimationData("Right",Vector2f(80.0f, 0.0f), _size, _readDirection,  _toRepeat, 3, _speed),
	AnimationData("Left",Vector2f(80.0f, 0.0f), _size, _readDirection,  _toRepeat, 3, _speed, false),
	AnimationData("NONELEFT",Vector2f(0.0f, 0.0f), _size, _readDirection,  _toRepeat, 1, _speed, false),
	AnimationData("Dash",Vector2f(0.0f, 560.0f), _size, _readDirection, _toRepeat,11,_speed),
	//AnimationData("DashLeft",Vector2f(0.0f, 720.0f), _size, _readDirection, _toRepeat,12,_speed, false),
	AnimationData("DarkSasuke",Vector2f(0.0f, 800.0f), _size, _readDirection, _toRepeat, 10, _speed),// 560    12
	AnimationData("Jump",Vector2f(0.0f, 720.0f), Vector2f(79.0f, 71.0f), _readDirection, _toRepeat, 9, _speed),// Change size
     });

	components.push_back(animation);

	animPlayer.resize(15);

	animPlayer = {
		"NONERIGHT",
		"Special",
		"Right",
		"Left",
		"Dash",
		"DarkSasuke",
		"Jump",
		//"DashLeft" 
		"NONELEFT"
	};
	
}


void Player::SetupPlayerInput()
{
	new ActionMap("Stats", {
		ActionData("AddMana", [&]() { stats->UseMana(10.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Space  })),
		ActionData("RemoveMana", [&]() { stats->UseMana(-10.0f);}, InputData({ActionType::KeyPressed, Keyboard::J})),
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
		ActionData("Right", [&]() { movement->SetDirectionX(1.0f); this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[2]); }, InputData({ActionType::KeyPressed, Keyboard::D})),
		ActionData("StopRight", [&]() { movement->SetDirectionX(0.0f); this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[0]); }, InputData({ ActionType::KeyReleased, Keyboard::D })),
		ActionData("Left", [&]() { movement->SetDirectionX(-1.0f); this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[3]); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("StopLeft", [&]() { movement->SetDirectionX(0.0f); this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[7]); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),
		//ActionData("DarkSasuke", [&]() {  this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[5]); }, InputData({ ActionType::KeyReleased, Keyboard::Space })),
		ActionData("Dash", [&]() { movement->Dash(); this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[4]); }, InputData({ ActionType::KeyReleased, Keyboard::LControl })),
		
		
		ActionData("Jump", [&]() { movement->Jump(); this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[6]); }, InputData({ ActionType::KeyReleased, Keyboard::RControl })),//
	});

	new ActionMap("Attack", {

		ActionData("Slash", [&]() {
			SpecialAttack();
			this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[1]);
			cout << "Slash" << endl;
			},
			InputData({ActionType::KeyPressed, Keyboard::R})),

		ActionData("StopSlash", [&]() {
			movement->SetDirectionX(0.0f);
			this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[0]);
			},
			InputData({ActionType::KeyReleased, Keyboard::R})),

		});

	
}


void Player::Init()
{
	stats->Init();
	inventory->Init();
	SetupPlayerInput();
}

void Player::SpecialAttack()
{
	//movement->SetDirectionX(10.0f);

	const vector<Mob*>& _mobs = RetrieveAllMobsAround<Mob>(GetShapePosition(), 15.0f);
	for (Mob* _mob : _mobs)
	{
		if (!_mob)continue;
		_mob->TakeDamages(stats->GetDamages());
	}
}

void Player::TakeDamages(const int _damages)
{
	int _newLife = stats->GetCurrentLife() - _damages;
	stats->SetCurrentLife(_newLife);
}

void Player::Update()// TODO
{
	if (stats->GetCurrentLife() != 0)
	{
		return;
	}

	else if (stats->GetCurrentLife() == 0)
	{
		cout << "Tu es mort" << endl;
		//creer un mob qui va etre a la position de la mort du joueur
		ShapeData _data = ShapeData(GetShapePosition(),Vector2f(100.0f, 100.0f), PATH_DEATHMOB, IntRect(0, 18, 316, 346));
		DeathMob* _death = new DeathMob(_data);

	//Changement de l'anim du joueur pdt 3sec avant de respawn
		/*function<void()> _callback = [&]() {

			this->GetComponent<AnimationComponent>()->RunAnimation(animPlayer[5]);
			};

		deathTimer = new Timer(_callback, seconds(3.0f), true, false);*/


		//set la position au debut du niveau
		//this->GetDrawable()->setPosition(//Checkpoint); 
		stats->SetCurrentLife(stats->GetMaxLife()); // Lui redonner full vie
	}
}


