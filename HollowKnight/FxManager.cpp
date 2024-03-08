#include "FxManager.h"
#include"Game.h"
#include"Fx.h"

#define PATH_FX "Animations/Fx.png"

FxManager::FxManager()
{
	index = 0;
}

void FxManager::Run(const string& _runningAnimation)
{
	index++;
	Vector2f _pos = Game::GetPlayer()->GetPosition();
	Fx* _fx = new Fx("fx" + to_string(index), ShapeData(_pos, Vector2f(250.0f, 250.0f), PATH_FX));
	FxData _fxdata = FxData(_fx, "");
	
	_fxdata.GetCurrentAnimation()->RunAnimation(_runningAnimation, 1);
}
