#include "Mob.h"
#include "Macro.h"
#include "MovementComponent.h"
#include "TextureManager.h"

Mob::Mob(const ShapeData& _data) : Actor("Mob" + to_string(GetUniqueID()), _data)
{
	components.push_back(new MovementComponent(this));

}
