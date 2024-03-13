#include "DeathState.h"
#include "Brain.h"
#include "FileLoader.h"

DeathState::DeathState(Brain* _brain) : State(_brain)
{
	animation = nullptr;
	movement = nullptr;
	inspect = nullptr;
}

void DeathState::Start()
{
	Actor* _owner = brain->GetOwner();

	if (!inspect || !animation || !movement)
	{
		inspect = _owner->GetComponent<InspectComponent>();
		animation = _owner->GetComponent<AnimationComponent>();
		movement = _owner->GetComponent<MobMovementComponent>();
	}

	movement->SetCanMove(false);

	for (const string& _name : animation->GetAnimationNames())
	{
		if (ContainsText(_name, "Death")) //si il trouve "Death" au débuit du name alors il lance l'anim
		{
			animation->RunAnimation(_name, animation->GetCurrentAnimation()->GetDirectionX());
		}
	}

	cout << "Start Death" << endl;
}

void DeathState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);


}

void DeathState::Stop()
{
	cout << "Stop Death" << endl;
}
