#pragma once
#include "Actor.h"
#include "PlayerStat.h"
#include "Inventory.h"
#include "CharmsMenu.h"
#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"
#include "PlayerAnimationComponent.h"
#include "InteractionComponent.h"

using namespace std;

class Player : public Actor
{
	PlayerStat* stats;
	Inventory* inventory;
	CharmsMenu* charmsMenu;
	PlayerMovementComponent* movement;
	PlayerAttackComponent* attack;
	PlayerAnimationComponent* animation;
	InteractionComponent* interaction;
	CircleShape* light;

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
	CircleShape* GetLight()const
	{
		return light;
	}

public:
	Player(const string& _name, const ShapeData& _data);

private:
	void InitAnimations();
	void SetupPlayerInput();
	void TryToOpenCharmsMenu();

public:
	virtual void Init() override;
};