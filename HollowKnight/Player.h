#pragma once
#include "Actor.h"
#include "Canvas.h"
//#include "IDamagable.h"

#include "PlayerStats.h"
//#include "Inventory.h"
//#include "CraftBook.h"
//#include "SkillTree.h"
//#include "PlayerMovementComponent.h"
//#include "InteractComponent.h"
//#include "GatherComponent.h"
//#include "FightComponent.h"
#include "ActionMap.h"

using namespace std;

class Player : public Actor//, public IDamagable
{
<<<<<<< Updated upstream
	PlayerStats* stats;
	//Inventory* inventory;
	//CraftBook* craftBook;
	//SkillTree* skillTree;

	//PlayerMovementComponent* movement;
	//InteractComponent* interact;
	//GatherComponent* gather;
	//FightComponent* fight;

	ActionMap* overworldInputs;
	ActionMap* donjonInputs;

	//TODO remove
	Canvas* canvas;

public:
	PlayerStats* GetStats() const
	{
		return stats;
	}
	/*Inventory* GetInventory() const
	{
		return inventory;
	}*/

public:
	Player(const string& _name, const ShapeData& _data);

private:
	void SetupPlayerInput();
	void InitHUD();
	void InitStats();
	void InitSkillTree();

	//TODO move
	void SwapActionMap();

public:
	virtual void Update(const float _deltaTime) override;
=======
	ShapeData data;

public :
	Player();


public:
>>>>>>> Stashed changes
	void Init();
};