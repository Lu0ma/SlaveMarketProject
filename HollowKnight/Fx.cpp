#include "Fx.h"
#include"Macro.h"

Fx::Fx(const string& _name, const ShapeData& _data) : Actor(STRING_ID(_name), _data)
{
	GetDrawable()->setScale(0.0f, 0.0f);
}