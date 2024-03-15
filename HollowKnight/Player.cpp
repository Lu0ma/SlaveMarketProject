#include "Player.h"
#include "Game.h"

// Sound
#include "SoundData.h"
// Mobs
#include "Mob.h"
#include "SoundData.h"
#include "SoundData.h"
#include "DeathMob.h"

// System
#include "Macro.h"
#include "Kismet.h"
#include "Camera.h"
// Managers
#include "ActorManager.h"
#include "InputManager.h"
#include"FxManager.h"
#include "Timer.h"
#include "TimerManager.h"
#include "PlayerSound.h"
#include "MusicData.h"
#define PATH_ITEM "UIs/Inventory/Item.png"
#define PATH_DEATHMOB "Animations/DeathMob.png"
#define DEAD_ZONE 50.0f



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

	light = new CircleShape(150.0f);
	light->setFillColor(Color(255, 255, 255, 50));
	light->setOrigin(150.0f, 150.0f);

	stats = new PlayerStat(this);
	charmsMenu = new CharmsMenu();
	pauseMenu = new PauseMenu();

	sound = new SoundData(SOUND_CHARGE_COMPLETE, 40.0f, false);

	data = PlayerSoundData();
}


void Player::InitAnimations()
{
	animation->Init();
}

void Player::SetupPlayerInput()
{
	new ActionMap("Stats", {
		ActionData("ConvertManaToLife", [&]() {
			if (movement->IsOnGround())
			{
				stats->UseMana(0.6f);
				Game::GetCamera()->SetIsZoom(true);

				movement->SetCanMove(false);
				attack->SetCanAttack(false);
			}
		}, InputData({ ActionType::KeyPressed, Keyboard::A })),
		ActionData("StopConvertManaToLife", [&]() {

			movement->SetCanMove(true);
			attack->SetCanAttack(true);

			movement->SetDirectionX(0.0f, "StopRight");
			Game::GetCamera()->SetIsZoom(false);

		}, InputData({ActionType::KeyReleased, Keyboard::A})),
	});

	new ActionMap("Camera " , {
		ActionData("StopConvertManaToLife", [&]() {
			movement->SetDirectionX(0.0f, "StopRight");
			Game::GetCamera()->SetIsZoom(false);
		}, InputData({ActionType::KeyReleased, Keyboard::A})),
	});

	new ActionMap("Camera", {
		ActionData("Shake", [&]() {
			Game::GetCamera()->GetShake()->Shake(0.7f , 1000.0f);
		}, InputData({ ActionType::KeyPressed, Keyboard::C })),
		ActionData("Look Down", [&]() {
			Game::GetCamera()->SetIsDown(true);
			animation->GetCurrentAnimation()->RunAnimation("HeadDown", movement->GetDashDirection());
		}, InputData({ ActionType::KeyPressed, Keyboard::Down })),
		ActionData("Stop Look Down", [&]() {
			Game::GetCamera()->SetIsDown(false);
			animation->GetCurrentAnimation()->RunAnimation("StopRight", movement->GetDashDirection());
		}, InputData({ ActionType::KeyReleased, Keyboard::Down })),
		ActionData("Look Up", [&]() {
			Game::GetCamera()->SetIsUp(true);
			animation->GetCurrentAnimation()->RunAnimation("HeadUp", movement->GetDashDirection());
		}, InputData({ ActionType::KeyPressed, Keyboard::Up })),
		ActionData("Stop Look Up", [&]() {
			Game::GetCamera()->SetIsUp(false);
			animation->GetCurrentAnimation()->RunAnimation("StopRight", movement->GetDashDirection());
		}, InputData({ ActionType::KeyReleased, Keyboard::Up })),
		ActionData("ShakePlayer", [&]() { Game::GetCamera()->SetCanShake(true); }, InputData({ActionType::KeyPressed, Keyboard::K })),
		ActionData("StopShakePlayer", [&]() {
			new Timer([&]() { Game::GetCamera()->SetCanShake(false); }, milliseconds((Int32)5.0f));
		}, InputData({ ActionType::KeyReleased, Keyboard::K })),
	});

	new ActionMap("Movements", {
		ActionData("Right", [&]() {
			if (!movement->GetIsDashing())
			{
				movement->SetDirectionX(1.0f, "Right");
			}
		}, InputData({ActionType::KeyPressed, Keyboard::D})),
		ActionData("StopRight", [&]() { movement->SetDirectionX(0.0f, "StopRight"); }, InputData({ ActionType::KeyReleased, Keyboard::D })),
		ActionData("Left", [&]() {
			if (!movement->GetIsDashing())
			{
				movement->SetDirectionX(-1.0f, "Left");
			}
		}, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("Right", [&]() { movement->SetDirectionX(1.0f, "Right");}, InputData({ActionType::KeyPressed, Keyboard::D})),
		ActionData("StopRight", [&]() { movement->SetDirectionX(0.0f, "StopRight");  }, InputData({ ActionType::KeyReleased, Keyboard::D })),
		ActionData("Left", [&]() { movement->SetDirectionX(-1.0f, "Left");  }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("StopLeft", [&]() { movement->SetDirectionX(0.0f, "StopLeft"); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),
		ActionData("Jump", [&]() { movement->Jump();  }, InputData({ActionType::KeyPressed, Keyboard::Space})),
		ActionData("ControllerJump", [&]() {
			if (Joystick::isButtonPressed(0, 1))
			{
				movement->Jump();
			}
		}, InputData({ ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0, 1) })),
		ActionData("Dash", [&]() { movement->Dash(); }, InputData({ActionType::KeyPressed,Keyboard::LControl})),
		ActionData("StopDash", [&]() { movement->SetDirectionX(0, "Right"); }, InputData({ ActionType::KeyReleased, Keyboard::LControl })),
		ActionData("StopDash", [&]() { movement->SetDirectionX(0, "StopDash"); }, InputData({ ActionType::KeyReleased, Keyboard::LControl })),
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

	new ActionMap("Attack", {
		ActionData("Special", [&]() { attack->SpecialAttack(); FxManager::GetInstance().Run("FxSpecial"); Game::GetCamera()->GetShake()->Shake(2.0f, 800.0f); ActorManager::GetInstance().SetStop(true); new Timer([&]() {ActorManager::GetInstance().SetStop(false); }  , milliseconds(500)); }, InputData({ActionType::MouseButtonPressed, Mouse::Right})),
		ActionData("StopSpecial", [&]() {}, InputData({ActionType::MouseButtonReleased, Mouse::Right})),
		ActionData("Special", [&]() { attack->SpecialAttack(); FxManager::GetInstance().Run("FxSpecial");/* Game::GetCamera()->GetShake()->Shake(2.0f, 2800.0f); ActorManager::GetInstance().SetStop(true);*/
		new Timer([&]() {ActorManager::GetInstance().SetStop(false); }  , milliseconds(500)); new SoundData(SOUND_DAMAGE_LESS_HARSH_V2, 100.0f, false); } , InputData({ActionType::MouseButtonPressed, Mouse::Right})),
		ActionData("StopSpecial", [&]() { }, InputData({ActionType::MouseButtonReleased, Mouse::Right})),
		ActionData("ControllerSpecial", [&]() {
			if (Joystick::isButtonPressed(0, 0))
			{
				attack->SpecialAttack();
			}
			else
			{
				 movement->SetDirectionX(0.0f, "Right");
			}
		}, InputData({ ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0, 0) })),
		ActionData("StopSlash", [&]() { movement->SetDirectionX(0.0f, "StopRight"); }, InputData({ ActionType::MouseButtonReleased, Mouse::Left })),
	});

	new ActionMap("Menu", {
		ActionData("Pause", [&]() {
			TryToOpen(pauseMenu);
			stats->SetStatus(false);
		}, InputData({ ActionType::KeyPressed, Keyboard::Escape })),
		ActionData("Inventory", [&]() { TryToOpen(inventory); }, InputData({ ActionType::KeyPressed, Keyboard::B })),
		ActionData("ControllerInventory", [&]() {
			if (Joystick::isButtonPressed(0, 6))
			{
				TryToOpen(inventory);
			}
		}, InputData({ ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0,6) })),
		ActionData("CharmsMenu", [&]() {
			if (!movement->IsStanding())
			{
				TryToOpen(charmsMenu, false);
			}
		}, InputData({ ActionType::KeyPressed, Keyboard::P })),
		ActionData("Interact", [&]() { interaction->TryToInteract(); }, InputData({ ActionType::KeyPressed, Keyboard::E })),
	});
}

void Player::TryToOpen(Menu* _menu, const bool _restoreActions)
{
	const bool _isActive = _menu->IsActive();
	CloseAllMenus(_restoreActions);

	if (!_isActive)
	{
		SoundManager::GetInstance().Stop("bench rest");
		new SoundData("bossgushing", 50.0f, false);

		movement->SetCanMove(false);
		attack->SetCanAttack(false);
		_menu->SetStatus(true);
		stats->SetStatus(false);
	}

	else
	{
		SoundManager::GetInstance().Stop("bossgushing");
		new SoundData("bench rest", 50.0f, false);
	}
}

void Player::CloseAllMenus(const bool _restoreActions)
{
	charmsMenu->SetStatus(false);
	stats->SetStatus(true);
	inventory->SetStatus(false);
	interaction->StopInteract();

	if (_restoreActions)
	{
		movement->SetCanMove(true);
		attack->SetCanAttack(true);
	}
}


void Player::Init()
{
	movement->SetCanMove(true);
	stats->SetStatus(true);
	inventory->SetStatus(false);
	charmsMenu->SetStatus(false);

	InitAnimations();
	SetupPlayerInput();
}

void Player::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	light->setPosition(GetShapePosition());
}