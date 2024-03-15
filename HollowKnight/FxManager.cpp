#include "FxManager.h"
#include"Game.h"
#include"Fx.h"
#include"Macro.h"

#define PATH_FX "Animations/Fx.png"
#define PATH_FX2 "Animations/Fx2.png"
#define PATH_FX3 "Animations/Fx3.png"

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
			Fx* _fxdash1 = new Fx("fx" + to_string(index), ShapeData(_pos - Vector2f(200.0f, 0.0f), Vector2f(250.0f, 250.0f), PATH_FX));
			FxData* _fxdata = new FxData(_fxdash1, "");
			_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
			_fxdash1->Destroy(0.5f);
		}
		else if (_direction == 1)
		{
			Fx* _fxdash2 = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(200.0f, 0.0f), Vector2f(250.0f, 250.0f), PATH_FX));
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
	else if (_runningAnimation == "FxIsHitten")
	{
		if (_direction == 1)
		{
			Fx* _fx = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(-25.0f, 0.0f), Vector2f(250.0f, 250.0f), PATH_FX2));
			FxData* _fxdata = new FxData(_fx, "");
			_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
			_fx->Destroy(0.2f);
		}
		
		else if (_direction == -1)
		{
			Fx* _fx = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(25.0f, 0.0f), Vector2f(250.0f, 250.0f), PATH_FX2));
			FxData* _fxdata = new FxData(_fx, "");
			_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
			_fx->Destroy(0.2f);
		}
	}
	else if (_runningAnimation == "FxDarkHole")
	{

		Fx* _fx = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(-25.0f, 0.0f), Vector2f(250.0f, 250.0f), PATH_FX2));
		FxData* _fxdata = new FxData(_fx, "");
		_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
		_fx->Destroy(0.2f);
	}
	else if (_runningAnimation == "FxHighAttack")
	{

		Fx* _fx = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(0.0f, -150.0f), Vector2f(200.0f, 350.0f), PATH_FX2));
		FxData* _fxdata = new FxData(_fx, "");
		_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, _direction);
		_fx->Destroy(1.0f);
	}
	else if (_runningAnimation == "FxBroken")
	{

		Fx* _fx = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(0.0f, 0.0f), Vector2f(800.0f, 300.0f), PATH_FX3));
		FxData* _fxdata = new FxData(_fx, "");
		_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, _direction);
		_fx->Destroy(1.0f);
	}
	else
	{
		Fx* _fx = new Fx("fx" + to_string(index), ShapeData(_pos, Vector2f(250.0f, 250.0f), PATH_FX));
		FxData* _fxdata = new FxData(_fx, "");
		_fxdata->GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
		_fx->Destroy(0.5f);
	}
}
