#pragma once
#include "Actor.h"
#include "PauseMenu.h"
#include "PlayerStat.h"
#include "Inventory.h"
#include "CharmsMenu.h"
#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"
#include "PlayerAnimationComponent.h"
#include "InteractionComponent.h"
#include "CollisionComponent.h"

using namespace std;

class Player : public Actor
{
	PauseMenu* pauseMenu;
	PlayerStat* stats;
	Inventory* inventory;
	CharmsMenu* charmsMenu;
	PlayerMovementComponent* movement;
	PlayerAttackComponent* attack;
	PlayerAnimationComponent* animation;
	InteractionComponent* interaction;
	CollisionComponent* collision;
public:
	void SetStatus(const bool _status)
	{
		movement->SetCanMove(_status);
	}
	PlayerStat* GetStats() const
	{
		return stats;
	}
	Inventory* GetInventory() const
	{
		return inventory;
	}

public:
	Player(const string& _name, const ShapeData& _data);

private:
	void InitAnimations();
	void SetupPlayerInput();
	void TryToOpen(Menu* _menu);
	void CloseAllMenus();

public:
	virtual void Init() override;
};