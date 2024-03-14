#include "ActorManager.h"
#include "TimerManager.h"
#include "InputManager.h"

ActorManager::ActorManager()
{
	stop = false;
}


void ActorManager::Update()
{
	 const float _deltaTime = TimerManager::GetInstance().GetDeltaTime();

	// Mettre en pause seulement les actors
	for (Actor* _actor : GetAllValues())
	{

		_actor->Update(stop ? 0.0f : _deltaTime);
	}

	GarbageValues();
}