#include "State.h"
#include "Brain.h"
#include "MobLifeComponent.h"

State::State(Brain* _brain)
{
	brain = _brain;
	nextTransition = nullptr;

	animation = nullptr;
	movement = nullptr;
	inspect = nullptr;

	InitTimerInspect();
}

State::~State()
{
	for (Transition* _transition : transitions)
	{
		delete _transition;
	}
}

void State::Update(const float _deltaTime)
{
	for (Transition* _transition : transitions)
	{
		if (_transition->CanNext())
		{
			nextTransition = _transition;
			return;
		}
	}
	nextTransition = nullptr;
}

void State::InitTimerInspect()
{
	/*timerInspect = new Timer([&]()
		{
			cout << "Timer Inpsect" << endl;
			if (InspectComponent* _inspect = brain->GetOwner()->GetComponent<InspectComponent>())
			{
				brain->GetBlackBoard()->hasTarget = _inspect->HasTarget(brain->GetOwner()->GetShapePosition(), movement->GetDestination());
				brain->GetBlackBoard()->isInRange = _inspect->IsInRange();
			}
			if (brain->GetOwner()->GetComponent<MobLifeComponent>()->GetLife() <= 0)
			{
				brain->GetBlackBoard()->isDead = true;
			}
		}, seconds(0.5f), false, true);*/
}