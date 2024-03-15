#include "ActorManager.h"
#include "TimerManager.h"
#include "InputManager.h"

ActorManager::ActorManager()
{
	stop = false;
}


void ActorManager::Init()
{
	for (Actor* _actor : GetAllValues())
	{
		_actor->Init();
	}
}

void ActorManager::Update()
{
	 const float _deltaTime = TimerManager::GetInstance().GetDeltaTime();

	for (Actor* _actor : GetAllValues())
	{
		_actor->Update(stop ? 0.0f : _deltaTime);
	}

	GarbageValues();
}