#include "DeathState.h"
#include "Brain.h"
#include "FileLoader.h"

DeathState::DeathState(Brain* _brain) : State(_brain)
{
}

void DeathState::Start()
{
	cout << brain->GetOwner()->GetID() << "Start Death" << endl;

	//Actor* _owner = brain->GetOwner();

	//if (!inspect || !animation || !patrol)
	//{
	//	inspect = _owner->GetComponent<InspectComponent>();
	//	animation = _owner->GetComponent<AnimationComponent>();
	//	patrol = _owner->GetComponent<MobMovementComponent>();
	//}

	//patrol->SetCanMove(false);

	//for (const string& _name : animation->GetAnimationNames())
	//{
	//	if (ContainsText(_name, "Death")) //si il trouve "Death" au débuit du name alors il lance l'anim
	//	{
 //			animation->RunAnimation(_name, animation->GetCurrentAnimation()->GetDirectionX());
	//		return;
	//	}
	//}
}

void DeathState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);


}

void DeathState::Stop()
{
	cout << brain->GetOwner()->GetID() << "Stop Death" << endl;
}

void DeathState::Init() // besoin de garder vide
{
}
