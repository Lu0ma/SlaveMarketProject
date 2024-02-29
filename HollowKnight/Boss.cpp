#include "Boss.h"
#include "Macro.h"
#include "MovementComponent.h"

Boss::Boss(const ShapeData& _data) : Actor("Boss" + to_string(GetUniqueID()), _data)
{
	startPosition = _data.position;

	MovementComponent* _movement = new MovementComponent(this);
	components.push_back(_movement);
}
