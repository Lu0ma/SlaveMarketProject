#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Actor.h"
#include "InteractableActor.h"

class ActorManager : public Singleton<ActorManager>, public IManager<string, Actor>
{
	vector<InteractableActor*> interactables;

	bool stop;
public:
	void AddInteractable(InteractableActor* _interactable)
	{
		interactables.push_back(_interactable);
	}
	vector<InteractableActor*> GetInteractables() const
	{
		return interactables;
	}

	void SetStop(const bool _stop)
	{
		stop = _stop;
	}
public:
	ActorManager();

public:
	void Init();
	void Update();
};