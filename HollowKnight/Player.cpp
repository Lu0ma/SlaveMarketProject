#include "Player.h"
<<<<<<< Updated upstream
#include "Macro.h"
#include "Kismet.h"
=======
//#include "TextureManager.h"
#include "ActionMap.h"
#include "Component.h"
#include "MovementComponent.h"
>>>>>>> Stashed changes

// Managers
#include "ActorManager.h"
#include "InputManager.h"
#include "Action.h"
#include "Timer.h"

// UIs
#include "Canvas.h"
#include "ProgressBar.h"

// GPEs
//#include "Resource.h"
//#include "Transporter.h"
//#include "Ladder.h"
//#include "ArrowTrap.h"
//#include "FlameThrower.h"

#pragma region Defines

#pragma region ProgressBar

#define PATH_HEALTH_BAR_EMPTY "UIs/Bars/Health/Empty.png"
#define PATH_HEALTH_BAR_FULL "UIs/Bars/Health/Full.png"

#define PATH_MANA_BAR_EMPTY "UIs/Bars/Mana/Empty.png"
#define PATH_MANA_BAR_FULL "UIs/Bars/Mana/Full.png"

#define PATH_THIRST_BAR_EMPTY "UIs/Bars/Thirst/Empty.png"
#define PATH_THIRST_BAR_FULL "UIs/Bars/Thirst/Full.png"

#define PATH_HUNGER_BAR_EMPTY "UIs/Bars/Hunger/Empty.png"
#define PATH_HUNGER_BAR_FULL "UIs/Bars/Hunger/Full.png"

#pragma endregion

#define PATH_WOOD "Wood.png"
#define PATH_ROCK "Rock.png"

#define PATH_LADDER "GPEs/Ladder.png"
#define PATH_ARROW_TRAP "GPEs/ArrowTrap.png"
#define PATH_FLAME_THROWER "GPEs/FlameThrower.png"

#pragma endregion

Player::Player(const string& _name, const ShapeData& _data)
			: Actor(_name, _data)//, IDamagable(GetDrawable())
{
<<<<<<< Updated upstream
	InitStats();

	/*inventory = new Inventory();
	craftBook = nullptr;
	skillTree = nullptr;

	overworldInputs = nullptr;
	donjonInputs = nullptr;

	movement = new PlayerMovementComponent(this);
	components.push_back(movement);

	interact = new InteractComponent(this);
	components.push_back(interact);
	
	gather = new GatherComponent(this);
	components.push_back(gather);
	
	fight = new FightComponent(this);
	components.push_back(fight);*/
}


void Player::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
=======
	data = ShapeData();
>>>>>>> Stashed changes
}

void Player::Init()
{
	SetupPlayerInput();
	InitHUD();

	//TODO remove
	#pragma region Environment

	new Actor("Floor", ShapeData(Vector2f(20.0f, 650.0f), Vector2f(1250.0f, 50.0f), ""));
	new Actor("Floor2", ShapeData(Vector2f(320.0f, 400.0f), Vector2f(650.0f, 50.0f), ""));

	#pragma endregion

	#pragma region Resources

	/*static Resource* _tree = new Resource("Tree", ShapeData(Vector2f(400.0f, 200.0f), Vector2f(50.0f, 50.0f), ""), [&]() {
			gather->Gather(_tree);
			}),
		ResourceData(PATH_WOOD, ITEM_RESOURCE, RARITY_COMMON, 3, 5.0f, 0.01f)
	);
<<<<<<< Updated upstream
	static Resource* _rock = new Resource(
		InteractableData("Rock", ShapeData(Vector2f(600.0f, 200.0f), Vector2f(50.0f, 50.0f), ""), [&]() {
			gather->Gather(_rock);
			}),
		ResourceData(PATH_ROCK, ITEM_RESOURCE, RARITY_COMMON, 1, 2.0f, 0.01f)
	);*/

	#pragma endregion

	#pragma region GPEs

	//static Transporter* _transporter = new Transporter(ShapeData(Vector2f(500.0f, 300.0f), Vector2f(30.0f, 30.0f), ""),
	//													[&]() { _transporter->Teleport(this); }, Vector2f(800.0f, 200.0f));

	//new Ladder("Ladder", ShapeData(Vector2f(500.0f, 360.0f), Vector2f(70.0f, 300.0f), PATH_LADDER));
	//new Ladder("Ladder2", ShapeData(Vector2f(800.0f, 110.0f), Vector2f(70.0f, 300.0f), PATH_LADDER));

	//new ArrowTrap(ShapeData(Vector2f(800.0f, 600.0f), Vector2f(20.0f, 100.0f), PATH_ARROW_TRAP), Vector2f(-1.0f, 0.0f));
	//new FlameThrower(ShapeData(Vector2f(800.0f, 300.0f), Vector2f(20.0f, 100.0f), PATH_FLAME_THROWER), Vector2f(-1.0f, 0.0f));

	#pragma endregion

	#pragma region Enemies

	//new Enemy("Enemy", ShapeData(Vector2f(450.0f, 610.0f), Vector2f(80.0f, 80.0f), ""));

	#pragma endregion
=======
>>>>>>> Stashed changes
}

void Player::SetupPlayerInput()
{
	/*new ActionMap("PlayerStats", {
		ActionData("TakeDamages", [&]()
		{
			stats->TakeDamages(-30.0f);
			stats->StopHealthRegen();
		}, { ActionType::MouseButtonPressed, Mouse::Left }),
		ActionData("UseMana", [&]() { stats->UseMana(-50.0f); }, { ActionType::MouseButtonPressed, Mouse::Right }),
		ActionData("Drink", [&]() { stats->Drink(40.0f); }, { ActionType::KeyPressed, Keyboard::A }),
		ActionData("Eat", [&]() { stats->Eat(30.0f); }, { ActionType::KeyPressed, Keyboard::E }),
		});
	overworldInputs = new ActionMap("Overworld", {

		#pragma region Movement

		ActionData("Overworld_Forward", [&]() { movement->SetDirectionY(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Z })),
		ActionData("Overworld_StopForward", [&]() { movement->SetDirectionY(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Z })),

		ActionData("Overworld_Backward", [&]() { movement->SetDirectionY(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::S })),
		ActionData("Overworld_StopBackward", [&]() { movement->SetDirectionY(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::S })),

		ActionData("Overworld_Left", [&]() { movement->SetDirectionX(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("Overworld_StopLeft", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),

		ActionData("Overworld_Right", [&]() { movement->SetDirectionX(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::D })),
		ActionData("Overworld_StopRight", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::D })),

		ActionData("Sprint", [&]() { movement->SetSprint(true); }, InputData({ ActionType::KeyPressed, Keyboard::LControl })),
		ActionData("StopSprint", [&]() { movement->SetSprint(false); }, InputData({ ActionType::KeyReleased, Keyboard::LControl })),

		#pragma endregion

		#pragma region Interaction

		ActionData("Interact", [&]() { interact->Interact(); }, InputData({ ActionType::MouseButtonPressed, Mouse::Left })),

		#pragma endregion
	});
	donjonInputs = new ActionMap("Donjon", {

		#pragma region Movement

		ActionData("Donjon_Left", [&]() { movement->SetDirectionX(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("Donjon_StopLeft", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),

		ActionData("Donjon_Right", [&]() { movement->SetDirectionX(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::D })),
		ActionData("Donjon_StopRight", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::D })),

		ActionData("Donjon_Up", [&]() { movement->TryClimbLadder(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Z })),
		ActionData("Donjon_StopUp", [&]() { movement->TryClimbLadder(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Z })),

		ActionData("Donjon_Down", [&]() { movement->TryClimbLadder(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::S })),
		ActionData("Donjon_StopDown", [&]() { movement->TryClimbLadder(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::S })),

		ActionData("Jump", [&]() { movement->Jump(); }, InputData({ ActionType::KeyPressed, Keyboard::Space })),
		ActionData("Dash", [&]() { movement->Dash(); }, InputData({ ActionType::KeyPressed, Keyboard::LControl })),

		#pragma endregion

		#pragma region Fight

		ActionData("LightAttack", [&]() { fight->LightAttack(); }, InputData({ ActionType::MouseButtonPressed, Mouse::Left })),
		ActionData("HeavyAttack", [&]() { fight->HeavyAttack(); }, InputData({ ActionType::MouseButtonPressed, Mouse::Right })),

		#pragma endregion
	}, false);
	new ActionMap("Storages", {
		ActionData("Inventory", [&]() { inventory->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::B })),
	});

	//TODO remove
	new ActionMap("TEMP", {
		ActionData("SwapActionMap", [&]() { SwapActionMap(); }, InputData({ ActionType::KeyPressed, Keyboard::P })),
		ActionData("HideHUD", [&]() { canvas->SetVisibilityStatus(!canvas->IsVisible()); }, InputData({ ActionType::KeyPressed, Keyboard::M })),
	});*/
}

void Player::InitHUD()
{
	ProgressBar* _gatherBar = new ProgressBar(ShapeData(Vector2f(50.0f, 50.0f), Vector2f(200.0f, 150.0f), PATH_HUNGER_BAR_EMPTY),
											  canvas, PATH_HUNGER_BAR_FULL, ProgressType::PT_LEFT, 100.0f);
	canvas->AddWidget(_gatherBar);
	//gather->SetProgressBar(_gatherBar);

	InitSkillTree();
}

void Player::InitStats()
{
	canvas = new Canvas("PlayerStats", FloatRect(0, 0, 1, 1));

	float _sizeX = 200.0f, _sizeY = 150.0f;
	float _posX = _sizeX / 2.0f + 20.0f, _posY = 50.0f;

	ProgressBar* _healthBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY), Vector2f(_sizeX, _sizeY), PATH_HEALTH_BAR_EMPTY),
											  canvas, PATH_HEALTH_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	canvas->AddWidget(_healthBar);

	ProgressBar* _manaBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY + 50.0f), Vector2f(_sizeX, _sizeY), PATH_MANA_BAR_EMPTY),
											  canvas, PATH_MANA_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	canvas->AddWidget(_manaBar);

	ProgressBar* _thirstBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY + 100.0f), Vector2f(_sizeX, _sizeY), PATH_THIRST_BAR_EMPTY),
											  canvas, PATH_THIRST_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	canvas->AddWidget(_thirstBar);

	ProgressBar* _hungerBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY + 150.0f), Vector2f(_sizeX, _sizeY), PATH_HUNGER_BAR_EMPTY),
											  canvas, PATH_HUNGER_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	canvas->AddWidget(_hungerBar);

	stats = new PlayerStats(_healthBar, _manaBar, _thirstBar, _hungerBar);
	//SetStat(stats->health);
}

void Player::InitSkillTree()
{
	Canvas* _canvas = new Canvas("SkillTree", FloatRect(0, 0, 1, 1));
}

void Player::SwapActionMap()
{
	overworldInputs->isActive = !overworldInputs->isActive;
	donjonInputs->isActive = !donjonInputs->isActive;
	//movement->SetCanJumpAndDash(donjonInputs->isActive);
}