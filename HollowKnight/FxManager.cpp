#include "FxManager.h"
#include"Game.h"
#include"Fx.h"
#include"Macro.h"

#define PATH_FX "Animations/Fx.png"

FxManager::FxManager()
{
	index = 0;
}

void FxManager::Run(const string& _runningAnimation)
{
	index++;
	Vector2f _pos = Game::GetPlayer()->GetShapePosition();
	float _direction = Game::GetPlayer()->GetPlayerMovement()->GetDashDirection();

	if (_runningAnimation == "FxDash")
	{
		if (_direction == -1)
		{
			Fx* _fxdash1 = new Fx("fx" + to_string(index), ShapeData(_pos - Vector2f(300.0f, 0.0f), Vector2f(250.0f, 250.0f), PATH_FX));
			FxData* _fxdata = new FxData(_fxdash1, "");
			_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
			_fxdash1->Destroy(0.5f);
		}
		else if (_direction == 1)
		{
			Fx* _fxdash2 = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(300.0f, 0.0f), Vector2f(250.0f, 250.0f), PATH_FX));
			FxData* _fxdata = new FxData(_fxdash2, "");
			_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
			_fxdash2->Destroy(0.5f);
		}
	}

	else if (_runningAnimation == "FxDoubleJump")
	{
		Fx* _fxJump = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(0.0f, -100.0f), Vector2f(250.0f, 250.0f), PATH_FX));
		FxData* _fxdata = new FxData(_fxJump, "");
		_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
		_fxJump->Destroy(0.5f);
	}

	else if (_runningAnimation == "FxMana")
	{
		Fx* _fx = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(-10.0f, -40.0f), Vector2f(250.0f, 250.0f), PATH_FX));
		FxData* _fxdata = new FxData(_fx, "");
		_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
		_fx->Destroy(0.5f);
	}

	else if (_runningAnimation == "FxChargingMana")
	{
		Fx* _fx = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(5.0f, -50.0f), Vector2f(175.0f, 175.0f), PATH_FX));
		FxData* _fxdata = new FxData(_fx, "");
		_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
		_fx->Destroy(0.2f);
	}
}