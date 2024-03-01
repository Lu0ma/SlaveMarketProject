#include "InteractionComponent.h"
#include "ActorManager.h"
#include "InteractableActor.h"
#include "Merchand.h"
#include "Macro.h"

InteractionComponent::InteractionComponent(Actor* _owner) : Component(_owner)
{
	range = 50.0f;
}


void InteractionComponent::TryToInteract()
{
	for (InteractableActor* _interactable : ActorManager::GetInstance().GetInteractables())
	{
		const float _distance = Distance(owner->GetShapePosition(), _interactable->GetShapePosition());
		if (_distance > range) continue;

		if (Merchand* _merchand = dynamic_cast<Merchand*>(_interactable))
		{
			_merchand->OpenDiscussion();
		}

		else if (NPC* _npc = dynamic_cast<NPC*>(_interactable))
		{
			_npc->OpenDiscussion();
		}
	}
}