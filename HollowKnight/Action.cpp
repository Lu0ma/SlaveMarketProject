#include "Action.h"
#include "InputManager.h"

void Action::Register()
{
	if (ActionMap* _actionMap = InputManager::GetInstance().Get(actionMap))
	{
		_actionMap->Add(id, this);
		return;
	}

	ActionMap* _newMap = new ActionMap(actionMap);
	_newMap->Add(id, this);
}


void Action::Execute()
{
	if (data.callback)
	{
		data.callback();
	}
}