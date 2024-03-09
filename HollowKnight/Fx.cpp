#include "Fx.h"

Fx::Fx(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	GetDrawable()->setScale(0.0f, 0.0f);
}