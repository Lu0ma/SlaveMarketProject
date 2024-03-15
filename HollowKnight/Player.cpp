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
#include"FxManager.h"
#include "Timer.h"

#define PATH_ITEM "UIs/Inventory/Item.png"
#define PATH_ITEM2 "test.png"
#define PATH_DEATHMOB "Animations/DeathMob.png"
#define DEAD_ZONE 75.f

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data, CT_BLOCK)
{
	animation = new PlayerAnimationComponent(this);
	components.push_back(animation);

	movement = new PlayerMovementComponent(this);
	components.push_back(movement);

	attack = new PlayerAttackComponent(this, 1);
	components.push_back(attack);

	inventory = new Inventory(); // before interaction

	interaction = new InteractionComponent(this);
	components.push_back(interaction);

	light = new CircleShape(55.0f);
	light->setFillColor(Color(255, 255, 255, 20));
	light->setOrigin(100.0f, 100.0f);

	stats = new PlayerStat(this);
	charmsMenu = new CharmsMenu();
	pauseMenu = new PauseMenu();
}


void Player::InitAnimations()
{
	animation->Init();
}

void Player::SetupPlayerInput()
{
	Event _event;
	new ActionMap("Stats", {
		ActionData("ConvertManaToLife", [&]() {
			stats->UseMana(-10.0f);
			stats->UpdateLife(1);
			FxManager::GetInstance().Run("FxMana");
			Game::GetCamera()->SetIsZoom(true);
		}, InputData({ActionType::KeyPressed, Keyboard::A})),
	ActionData("ManaToLife", [&]() {stats->UpdateLife(-1); FxManager::GetInstance().Run("FxIsHitten"); }, InputData({ActionType::KeyPressed, Keyboard::M})),
		ActionData("StopConvertManaToLife", [&]() {movement->SetDirectionX(0.0f, "StopRight"); }, InputData({ActionType::KeyReleased, Keyboard::A})),
		});

	new ActionMap("Movements", {
		ActionData("Right", [&]() { movement->SetDirectionX(1.0f, "Right"); }, InputData({ActionType::KeyPressed, Keyboard::D})),
		ActionData("ControllerMove", [&]() {
			 if ( Joystick::getAxisPosition(0, Joystick::X) > DEAD_ZONE)
			 {
				movement->SetDirectionX(1.0f, "Right");
			 } 
			 else if (Joystick::getAxisPosition(0, Joystick::X) < -DEAD_ZONE)
			 {
				movement->SetDirectionX(-1.0f, "Left");
			 }
			 else
			 {
				movement->SetDirectionX(0.0f, "StopLeft");
			 }
			 if (Joystick::getAxisPosition(0, Joystick::Y) > DEAD_ZONE)
			 {
				 Game::GetCamera()->SetIsDown(true);
				 animation->GetCurrentAnimation()->RunAnimation("HeadDown", movement->GetDashDirection());
			 }
			 else
			 {
				  Game::GetCamera()->SetIsDown(false);
             }
			 if (Joystick::getAxisPosition(0, Joystick::Y) < -DEAD_ZONE)
			 {
				 Game::GetCamera()->SetIsUp(true);
				 animation->GetCurrentAnimation()->RunAnimation("HeadUp", movement->GetDashDirection());
			 }
			 else
			 {
				  Game::GetCamera()->SetIsUp(false);
			 }
			 if (Joystick::getAxisPosition(0, Joystick::Y) < -20 && !charmsMenu->IsActive())
			 {
				 movement->SitDown();
				 attack->SetCanAttack(false);
			 }
			 else if (Joystick::getAxisPosition(0, Joystick::Y) > 20 && !charmsMenu->IsActive())
			 {
				 movement->StandUp();
				 attack->SetCanAttack(true);
			 }
			cout << Joystick::getAxisPosition(0, Joystick::X) << endl;
			cout << Joystick::getAxisPosition(0, Joystick::Y) << endl;
		}, InputData({ ActionType::JoystickMoved, Joystick::X})),


		ActionData("StopRight", [&]() { movement->SetDirectionX(0.0f, "StopRight"); }, InputData({ ActionType::KeyReleased, Keyboard::D })),
		ActionData("Left", [&]() { movement->SetDirectionX(-1.0f, "Left"); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("StopLeft", [&]() { movement->SetDirectionX(0.0f, "StopLeft"); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),
		ActionData("Jump", [&]() {
			movement->StartJump();
			/*FxManager::GetInstance().Run("FxDoubleJump");*/
		}, InputData({ActionType::KeyPressed, Keyboard::Space})),
		ActionData("ControllerJump", [&]() {
			if (Joystick::isButtonPressed(0, 1))
			{
				movement->StartJump();
			}
		}, InputData({ ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0, 1) })),
		ActionData("StopJump", [&]() { movement->StopJump(); }, InputData({ ActionType::KeyReleased, Keyboard::Space })),
		ActionData("Dash", [&]() { movement->Dash();  }, InputData({ActionType::KeyPressed,Keyboard::LControl})),

		ActionData("StopDash", [&]() { movement->SetDirectionX(0, "StopRight"); }, InputData({ActionType::KeyReleased,Keyboard::LControl})),

		ActionData("StopDash", [&]() { movement->SetDirectionX(movement->GetDashDirection(), "Right"); }, InputData({ActionType::KeyReleased,Keyboard::LControl})),
		ActionData("ControllerDash", [&]() {
			if (Joystick::isButtonPressed(0, 7))
			{
				movement->Dash();
			}
		}, InputData({ ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0, 7) })),
		ActionData("Sit", [&]() {
			if (!charmsMenu->IsActive())
			{
				movement->SitDown();
				attack->SetCanAttack(false);
			}

		}, InputData({ ActionType::KeyPressed, Keyboard::Z})),
		ActionData("Stand", [&]() {
			if (!charmsMenu->IsActive())
			{
				movement->StandUp();
				attack->SetCanAttack(true);
			}
		}, InputData({ ActionType::KeyPressed, Keyboard::S }))
		});


	new ActionMap("Camera", {
		ActionData("Shake" , [&]()
			{ Game::GetCamera()->Shake(0.7f , 5000000.0f);},InputData({ActionType::KeyPressed, Keyboard::C})),

		ActionData("Look Down" , [&]()
			{Game::GetCamera()->SetIsDown(true); animation->GetCurrentAnimation()->RunAnimation("HeadDown", movement->GetDashDirection()); } , InputData({ActionType::KeyPressed , Keyboard::Down})),

		/*ActionData("Conroller Look Down" , [&]() {
			if (Joystick::getAxisPosition(1, Joystick::Y) > DEAD_ZONE)
			{
				Game::GetCamera()->SetIsDown(true); 
				animation->GetCurrentAnimation()->RunAnimation("HeadDown", movement->GetDashDirection());
			}
				cout << Joystick::getAxisPosition(1, Joystick::Y) << endl;
			} , InputData({ActionType::JoystickMoved , Joystick::Y})),*/
		
		ActionData("Stop Look Down" , [&]()
			{Game::GetCamera()->SetIsDown(false); animation->GetCurrentAnimation()->RunAnimation("StopRight", movement->GetDashDirection()); } , InputData({ActionType:: KeyReleased , Keyboard::Down})),
		
		ActionData("Look Up", [&]()
		{Game::GetCamera()->SetIsUp(true); animation->GetCurrentAnimation()->RunAnimation("HeadUp", movement->GetDashDirection()); }, InputData({ ActionType::KeyPressed , Keyboard::Up })),


			ActionData("Stop Look Up", [&]()
				{
					Game::GetCamera()->SetIsUp(false); animation->GetCurrentAnimation()->RunAnimation("StopRight", movement->GetDashDirection()); }, InputData({ ActionType::KeyReleased , Keyboard::Up })) , });

	new ActionMap("Attack", {
		ActionData("Special", [&]() { attack->SpecialAttack(); FxManager::GetInstance().Run("FxSpecial"); }, InputData({ActionType::MouseButtonPressed, Mouse::Right})),
		ActionData("ControllerSpecial", [&]() {
			if (Joystick::isButtonPressed(0, 0))
			{
				attack->SpecialAttack();
				cout << "Attack" << endl;
			}
			else
			{
				 movement->SetDirectionX(0.0f, "StopRight");
			}
		}, InputData({ ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0,0) })),
		ActionData("StopSlash", [&]() { movement->SetDirectionX(0.0f, "StopRight"); }, InputData({ ActionType::MouseButtonReleased, Mouse::Right })),
		ActionData("UpAttack", [&]() { attack->UpAttack(); FxManager::GetInstance().Run("FxHighAttack"); }, InputData({ ActionType::KeyPressed, Keyboard::O }))

		});
	new ActionMap("Menu", {
		ActionData("Pause", [&]() {
			TryToOpen(pauseMenu);
			stats->SetStatus(false);
		}, InputData({ ActionType::KeyPressed, Keyboard::Escape })),
		ActionData("ControllerPause", [&]() {

			if (Joystick::isButtonPressed(0, 9))
			{
				TryToOpen(pauseMenu);
				stats->SetStatus(false);
			}
		}, InputData({ ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0,9) })),

		ActionData("Inventory", [&]() { TryToOpen(inventory); }, InputData({ ActionType::KeyPressed, Keyboard::B })),
		ActionData("ControllerInventory", [&]() {
			if (Joystick::isButtonPressed(0, 6))
			{
				TryToOpen(inventory);
			}
		}, InputData({ ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0,6) })),
		ActionData("CharmsMenu", [&]() {
			//TODO restore
			//if (!movement->IsStanding())
			{
				TryToOpen(charmsMenu);
			}
		}, InputData({ ActionType::KeyPressed, Keyboard::P })),
		ActionData("Interact", [&]() { interaction->TryToInteract(); }, InputData({ ActionType::KeyPressed, Keyboard::E })),

		ActionData("ControllerInteract", [&]() 
			{ 
			if (Joystick::isButtonPressed(0, 8)) //Change button to ps5 button
			{
				interaction->TryToInteract();
			}
			},InputData({ ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0,8) })),
		});
}

void Player::TryToOpen(Menu* _menu)
{
	const bool _isActive = _menu->IsActive();
	CloseAllMenus();

	if (!_isActive)
	{
		movement->SetCanMove(false);
		attack->SetCanAttack(false);
		_menu->SetStatus(true);
		stats->SetStatus(false);
	}
}

void Player::CloseAllMenus()
{
	charmsMenu->SetStatus(false);
	stats->SetStatus(true);
	inventory->SetStatus(false);
	interaction->StopInteract();

	movement->SetCanMove(true);
	attack->SetCanAttack(true);
}

void Player::Init()
{
	movement->SetCanMove(true);
	stats->SetStatus(true);
	inventory->Init();
	charmsMenu->Init();

	InitAnimations();
	SetupPlayerInput();
}

void Player::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	light->setPosition(GetShapePosition() + Vector2f(50.0f, 50.0f));
}