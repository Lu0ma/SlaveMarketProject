#include "Lever.h"

Lever::Lever(const string& _name, const ShapeData& _data)
	: Actor(_name,_data)
{
	animation = new LeverAnimationComponent(this);
}
